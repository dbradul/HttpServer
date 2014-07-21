#include "stdio.h"
#include <exception>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string>

#include <sys/types.h>
#include <sys/stat.h>

#include "core/Server.h"
#include "core/Connector.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"


//---------------------------------------------------------------------------------------
// FORWARD DECLARATIONS
//---------------------------------------------------------------------------------------
bool parseOptions(int argc, char *argv[], Configuration& configuration);
void printUsage();
void daemonize();

//---------------------------------------------------------------------------------------
int main(int argc, char *argv[])
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "Application started");

   Configuration configuration;
                        
   if (!parseOptions(argc, argv, configuration))
   {
      printUsage();
      exit(EXIT_FAILURE);
   }

   if (!configuration.isValid())
   {
      printUsage();
      exit(EXIT_FAILURE);
   }

   TRC_INFO(0U, "Deamonization");
   daemonize();

   /* Open the log file */
   TRC_INIT(LOG_PID, LOG_DAEMON);

   try
   {
      Server server;
      Connector connector;

      // initialize
      server.setConfiguration(configuration);
      server.setConnector(connector);

      TRC_INFO(0U, "Server is being started...");

      // blocking call: starts infinite message loop
      server.start();
   }

   catch (const std::exception& e)
   {
      TRC_FATAL(0U, "Fatal error occured: '%s'", e.what());
      TRC_FATAL(0U, "Application terminated!");
   }

   TRC_DEINIT();

   return 0;
}

//---------------------------------------------------------------------------------------
void daemonize()
//---------------------------------------------------------------------------------------
{
   pid_t pid;

   /* Fork off the parent process */
   pid = fork();

   /* An error occurred */
   if (pid < 0)
      exit(EXIT_FAILURE);

   /* Success: Let the parent terminate */
   if (pid > 0)
      exit(EXIT_SUCCESS);

   /* On success: The child process becomes session leader */
   if (setsid() < 0)
      exit(EXIT_FAILURE);

   /* Catch, ignore and handle signals */
   //TODO: Implement a working signal handler */
   signal(SIGCHLD, SIG_IGN );
   signal(SIGHUP, SIG_IGN );

   /* Fork off for the second time*/
   pid = fork();

   /* An error occurred */
   if (pid < 0)
      exit(EXIT_FAILURE);

   /* Success: Let the parent terminate */
   if (pid > 0)
      exit(EXIT_SUCCESS);

   /* Set new file permissions */
   umask(0);

   /* Change the working directory to the root directory */
   /* or another appropriated directory */
   std::string workDir;
   Configuration::getValue(Configuration::CONFIG_WORKING_DIR, workDir);
   chdir(workDir.c_str());

   /* Close all open file descriptors */
   int fileDescrs;
   for (fileDescrs = sysconf(_SC_OPEN_MAX); fileDescrs > 0; fileDescrs--)
   {
      close(fileDescrs);
   }
}

//---------------------------------------------------------------------------------------
bool parseOptions(int argc, char *argv[], Configuration& configuration)
//---------------------------------------------------------------------------------------
{
   bool bResult = true;
   int c;

   opterr = 0;

   while ((c = getopt(argc, argv, "p:d:t:r:")) != -1)
   {
      switch (c)
      {
      case 'p':
         Configuration::setValue(Configuration::CONFIG_PORT, Utils::atoi(optarg));
         break;

      case 'd':
         Configuration::setValue(Configuration::CONFIG_WORKING_DIR, std::string(optarg));
         break;

      case 'r':
         Configuration::setValue(Configuration::CONFIG_ROOT_DIR, std::string(optarg));
         break;

      case 't':
         Configuration::setValue(Configuration::CONFIG_MAX_THREAD_NUMBER, Utils::atoi(optarg));
         break;

      case '?':
         fprintf(stdout, "Unknown/invalid arguments.\n\n");
         bResult = false;
         break;

      default:
         fprintf(stdout, "Unknown/invalid arguments.\n\n");
         bResult = false;
      }
   }

   return bResult;
}

//---------------------------------------------------------------------------------------
void printUsage()
//---------------------------------------------------------------------------------------
{
   fprintf(stdout,
         "Usage: HttpServer [-p <port>] [-d <work_dir>] [-r <root_dir>] [-t <max_num_of_threads>] \n\
\n\
port               - port number to listen for client connection. By default: 8080\n\
work_dir           - working server directory. MUST contain 'templates' folder. By default: current dir.\n\
root_dir           - root directory to start the server in. By default: current dir.\n\
max_num_of_threads - maximum number of threads. By default: 4\n\
\n\
WARNING: If working directory ('work dir' param) doesn't contain 'templates' folder, the program will terminate! \n");
}
