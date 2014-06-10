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

bool parseOptions(int argc, char *argv[]);
void printUsage();

//---------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    if (!parseOptions(argc, argv))
    {
        exit(EXIT_FAILURE);
    }

    try
    {
        Dispatcher dispatcher;
        dispatcher.start();

        JobExecutor jobExecutor;
        jobExecutor.start();

        // infinite message loop
        while (true)
        {
            Request request = dispatcher.readRequest();

            IJobFactory* jobFactory = IJobFactory::create(request.getMethodType());

            IJob*            pJob = jobFactory->createJob(request);
            tCallback jobCallback = jobFactory->createJobCallback( dispatcher, request.getSessionId() );

            pJob->setOnFinishCallback(jobCallback);

            jobExecutor.submitJob(pJob);
        }
    }

    catch(const std::exception& e)
    {
        TRC_ERROR(0U, ( "Application start failed" ), NULL);
    }

    return 0;
}

//---------------------------------------------------------------------------------------
bool parseOptions(int argc, char *argv[])
{
    bool isWorkingDirConfigured = false;
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
                isWorkingDirConfigured = true;
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

    if(bResult && !isWorkingDirConfigured)
    {
        char workingDir[FILENAME_MAX];
        Config::setValue(Config::CONFIG_WORKING_DIR, std::string(getcwd(workingDir, sizeof(workingDir))));
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
