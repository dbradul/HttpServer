#include "stdio.h"
#include <exception>

#include "Dispatcher.h"
#include "jobs/IJobFactory.h"
#include "executor/JobExecutor.h"
#include "protocol/Request.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

bool parseOptions(int argc, char *argv[]);
void printUsage();
void daemonize();

//---------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (!parseOptions(argc, argv))
    {
        exit(EXIT_FAILURE);
    }

    daemonize();

    /* Open the log file */
    openlog ("HTTPServerDaemon", LOG_PID, LOG_DAEMON);

    try
    {
        Dispatcher dispatcher;
        dispatcher.start();

        JobExecutor jobExecutor;
        jobExecutor.start();

        Request request;

        // infinite message loop
        while ((request = dispatcher.readRequest()))
        {
            IJobFactory* jobFactory = IJobFactory::create(request.getMethodType());

            IJob*            pJob = jobFactory->createJob(request);
            Callback jobCallback  = jobFactory->createJobCallback( dispatcher, request.getSessionId() );

            pJob->setOnFinishCallback(jobCallback);

            jobExecutor.submitJob(pJob);
        }
    }

    catch(const std::exception& e)
    {
        TRC_ERROR(0U, ( "Application terminated" ), NULL);
    }

    closelog();

    return 0;
}

//---------------------------------------------------------------------------------------
void daemonize()
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
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

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
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close (x);
    }
}

//---------------------------------------------------------------------------------------
bool parseOptions(int argc, char *argv[])
{
    bool bResult = true;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "p:d:t:")) != -1)
    {
        switch (c)
        {
            case 'p':
                Config::setValue(Config::CONFIG_PORT, Utils::atoi(optarg));
                break;

            case 'd':
                Config::setValue(Config::CONFIG_WORKING_DIR, std::string(optarg));
                break;

            case 't':
                Config::setValue(Config::CONFIG_MAX_THREAD_NUMBER, Utils::atoi(optarg));
                break;

            case '?':
                fprintf (stdout, "Unknown/invalid arguments.\n\n");
                printUsage();
                bResult = false;
                break;

            default:
                fprintf (stdout, "Unknown/invalid arguments.\n\n");
                printUsage();
                bResult = false;
        }
    }

    return bResult;
}

//---------------------------------------------------------------------------------------
void printUsage()
{
    fprintf (stdout, "Usage: HttpServer [-p <port>] [-d <work_dir>] [-t <max_num_of_threads>] \n\
\n\
port               - port number to listen for client connection. By default: 8080\n\
work_dir           - working directory to start the server. By default: current dir.\n\
max_num_of_threads - maximum number of threads. By default: 4\n");

}
