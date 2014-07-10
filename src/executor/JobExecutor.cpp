/*******************************************************************
 * JobExecutor.cpp
 *
 *  @date: 28 June 2014
 *  @author: DB
 ******************************************************************/

#include "JobExecutor.h"
#include "common/Config.h"
#include "common/traceout.h"

const int JobExecutor::THREAD_NUM_UPPER_BOUND = 1024;

JobExecutor::JobExecutor()
:mbStarted(false)
{
    unsigned long portNumber;
    Config::getValue(Config::CONFIG_MAX_THREAD_NUMBER, portNumber);
    mMaxThreadNum = portNumber;
}

JobExecutor::~JobExecutor()
{
    // TODO Auto-generated destructor stub
}

void JobExecutor::start()
{
    if(!mbStarted)
    {
        // we must guarantee that at least one thread will be started!
        int maxNumThread = std::max(1, mMaxThreadNum);

        // we must ensure that the app will not exhaust system resources
        maxNumThread = std::min(THREAD_NUM_UPPER_BOUND, maxNumThread);

        for(int i=0; i<maxNumThread; ++i)
        {
            mThreadPool.push_back(new std::thread(&JobExecutor::run, this));
        }

        mbStarted = true;
    }
}

void JobExecutor::submitJob(IJob* job)
{
    mJobQueue.push(job);
}

void JobExecutor::run()
{
    while(IJob* pJob = mJobQueue.pop())
    {
        TRC_INFO(0U, "New job started: pJob=0x%x", (pJob));

        pJob->start();
    }
}

void JobExecutor::setMaxThreadNum(int maxThreadNum)
{
    mMaxThreadNum = maxThreadNum;
}
