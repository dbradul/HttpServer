#include "stdio.h"
#include <exception>

#include "Dispatcher.h"
#include "jobs/IJobFactory.h"
#include "executor/JobExecutor.h"
#include "protocol/Request.h"
#include "builder/Templater.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
////#include <execinfo.h>
#include <string.h>
#include "TestHarness.h"

bool parseOptions(int argc, char *argv[]);
void printUsage();
void daemonize();
static void signal_error(int sig, siginfo_t *si, void *ptr);
void hook_signals();

bool checkEnv()
{
   bool bResult = true;

   bResult &= File(Templater::TEMPLATE_ROOT_LAYOUT)        .exists();
   bResult &= File(Templater::TEMPLATE_PAGE_TABLE)         .exists();
   bResult &= File(Templater::TEMPLATE_PAGE_TABLE_LINE)    .exists();
   bResult &= File(Templater::TEMPLATE_FILE_CONTENT)       .exists();
   bResult &= File(Templater::TEMPLATE_FILE_CONTENT_LINE)  .exists();

   return bResult;
}

//---------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   TRC_DEBUG_FUNC_ENTER(0U, "Application started");

//   test::unit::Runner::run(false);
//   return 0;

   if (!parseOptions(argc, argv))
   {
      printUsage();
      exit(EXIT_FAILURE);
   }

   if (!checkEnv())
   {
      printUsage();
      exit(EXIT_FAILURE);
   }

   TRC_INFO(0U, "Application started and is about to be daemonized");
   daemonize();

   /* Open the log file */
   TRC_INIT(LOG_PID, LOG_DAEMON);

   try
   {
      Dispatcher dispatcher;
      dispatcher.start();

      JobExecutor jobExecutor;
      jobExecutor.start();

      // infinite message loop
      while (Request request = dispatcher.readRequest())
      {
         TRC_INFO(0U, "The new request is received: request='%s'", request.getHeader().toString().c_str());

         IJobFactory* jobFactory = IJobFactory::createInstance(request.getMethodType());

         IJob*    pJob              = jobFactory->createJob             (request);
         Callback jobCallback       = jobFactory->createJobCallback     (dispatcher, request.getSessionId());
         Callback jobErrorCallback  = jobFactory->createJobErrorCallback(dispatcher, request.getSessionId());

         pJob->setOnFinishCallback(jobCallback);
         pJob->setOnErrorCallback(jobErrorCallback);

         jobExecutor.submitJob(pJob);

         TRC_INFO(0U, "The corresponding job is queued: pJob=0x%x, sessionId=%d", pJob, request.getSessionId());
      }
   }

   catch (const std::exception& e)
   {
      TRC_ERROR(0U, "Application terminated");
   }

   TRC_DEINIT();

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
   Config::getValue(Config::CONFIG_WORKING_DIR, workDir);
////   chdir("/");
   chdir(workDir.c_str());

   /* Close all open file descriptors */
   int x;
   for (x = sysconf(_SC_OPEN_MAX); x > 0; x--)
   {
      close(x);
   }

   hook_signals();
}

//---------------------------------------------------------------------------------------
bool parseOptions(int argc, char *argv[])
{
   bool bResult = true;
   int c;

   opterr = 0;

   while ((c = getopt(argc, argv, "p:d:t:r:")) != -1)
   {
      switch (c)
      {
      case 'p':
         Config::setValue(Config::CONFIG_PORT, Utils::atoi(optarg));
         break;

      case 'd':
         Config::setValue(Config::CONFIG_WORKING_DIR, std::string(optarg));
         break;

      case 'r':
         Config::setValue(Config::CONFIG_ROOT_DIR, std::string(optarg));
         break;

      case 't':
         Config::setValue(Config::CONFIG_MAX_THREAD_NUMBER, Utils::atoi(optarg));
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

//---------------------------------------------------------------------------------------
void hook_signals()
{
   struct sigaction sigact;
   sigset_t sigset;
   int signo;
   int status;

   // ������� �� ������� � ��������� ����� ������������ ����� ���������
   // ��������� ��� ����� �������� ����������� ���������� �� �������
   sigact.sa_flags = SA_SIGINFO;
   // ������ ������� ���������� ��������
   sigact.sa_sigaction = signal_error;

   sigemptyset(&sigact.sa_mask);

   // ��������� ��� ���������� �� �������

   sigaction(SIGFPE, &sigact, 0); // ������ FPU
   sigaction(SIGILL, &sigact, 0); // ��������� ����������
   sigaction(SIGSEGV, &sigact, 0); // ������ ������� � ������
   sigaction(SIGBUS, &sigact, 0); // ������ ����, ��� ��������� � ���������� ������
   sigaction(SIGQUIT, &sigact, 0); // ������ ����, ��� ��������� � ���������� ������
   sigaction(SIGINT, &sigact, 0); // ������ ����, ��� ��������� � ���������� ������
   sigaction(SIGTERM, &sigact, 0); // ������ ����, ��� ��������� � ���������� ������
}

//---------------------------------------------------------------------------------------
static void signal_error(int sig, siginfo_t *si, void *ptr)
{
//    void* ErrorAddr;
//    void* Trace[16];
//    int    x;
//    int    TraceSize;
//    char** Messages;
//
//    // ddfdf
//    TRC_DEBUG(0U, ("Signal: %s, Addr: 0x%0.16X"), strsignal(sig), si->si_addr);
//
//    #if __WORDSIZE == 64 // ���� ���� ����� � 64 ������ ��
//        // ������� ����� ���������� ������� ������� ������
//        ErrorAddr = (void*)((ucontext_t*)ptr)->uc_mcontext.gregs[REG_RIP];
//    #else
//        // ������� ����� ���������� ������� ������� ������
//        ErrorAddr = (void*)((ucontext_t*)ptr)->uc_mcontext.gregs[REG_EIP];
//    #endif
//
//    // ���������� backtrace ����� �������� ���� ���� �������
//    TraceSize = backtrace(Trace, 16);
//    Trace[1] = ErrorAddr;
//
//    // ������� ����������� ����������
//    Messages = backtrace_symbols(Trace, TraceSize);
//    if (Messages)
//    {
//        TRC_DEBUG(0U, ("== Backtrace =="), NULL);
//
//        // ������� � ���
//        for (x = 1; x < TraceSize; x++)
//        {
//            TRC_DEBUG(0U, ("%s"), Messages[x]);
//        }
//
//        TRC_DEBUG(0U, ("== End Backtrace =="), NULL);
//        free(Messages);
//    }
//
//    TRC_DEBUG(0U, ("Stopped"), NULL);
//
//
//    // �������� ������� � ����� ��������� �����������
//    exit(CHILD_NEED_WORK);

}
