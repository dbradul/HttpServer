/*******************************************************************
 * JobExecutor.cpp
 *
 *  @date: 28 June 2014
 *  @author: DB
 ******************************************************************/

#include <memory>

#include "JobExecutor.h"
#include "common/Config.h"
#include "common/traceout.h"

const int JobExecutor::THREAD_NUM_LOWER_BOUND = 1;
const int JobExecutor::THREAD_NUM_UPPER_BOUND = 64;

using namespace std;

//---------------------------------------------------------------------------------------
JobExecutor::JobExecutor()
    : mJobQueue()
    , mbStarted(false)
    , mMaxThreadNum(Config::getValueInt(Config::MAX_THREAD_NUMBER))
    , mThreadPool()
    //---------------------------------------------------------------------------------------
{
}

//---------------------------------------------------------------------------------------
JobExecutor::~JobExecutor()
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");
    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void JobExecutor::start()
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");

    if (!mbStarted)
    {
        // we must ensure that thread number is within limits!
        int maxNumThread = std::max(THREAD_NUM_LOWER_BOUND, mMaxThreadNum);
        maxNumThread     = std::min(THREAD_NUM_UPPER_BOUND, maxNumThread);

        for (int i = 0; i < maxNumThread; ++i)
        {
            mThreadPool.push_back(std::thread(&JobExecutor::processingLoop, this));
        }

        mbStarted = true;
    }

    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void JobExecutor::submitJob(IJob::Ptr pJob)
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");

    mJobQueue.push(std::move(pJob));

    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void JobExecutor::processingLoop()
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");

    while (IJob::Ptr pJob = ::move(mJobQueue.peek()))
    {
        TRC_INFO(0U, "New job started: pJob=0x%p", (pJob.get()));
        mJobQueue.pop();

        if(IJob::DUMMY_TERMINATE == pJob->getType())
        {
            // stop message loop to terminate the corresponding thread
            break;
        }

        try
        {
            TRC_INFO(0, "Starting job execution");
            std::string result = pJob->execute();

            TRC_INFO(0, "The following result is being returned via callback: '%s'", result.c_str());
            pJob->onFinishCallback(result);
        }

        catch (const std::exception& e)
        {
            try
            {
                TRC_ERROR(0, "Job execution failed: '%s'", e.what());
                pJob->onErrorCallback(e.what());
            }
            catch(...)
            {
                TRC_ERROR(0, "Calling error callback failed!!");
            }
        }
    }

    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void JobExecutor::setMaxThreadNum(int maxThreadNum)
//---------------------------------------------------------------------------------------
{
    mMaxThreadNum = maxThreadNum;
}

//---------------------------------------------------------------------------------------
void JobExecutor::stop()
//---------------------------------------------------------------------------------------
{
    class JobStop: public IJob
    {
    public:
        using IJob::IJob;

        std::string execute()
        {return "";}
    };

    for(int i=0; i < mMaxThreadNum; ++i)
    {
        mJobQueue.push (make_unique<JobStop> (IJob::DUMMY_TERMINATE));
    }

    for_each(mThreadPool.begin(), mThreadPool.end(), [](thread& e)
    {
        e.join();
    });

    mbStarted = false;
}
