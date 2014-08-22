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

//---------------------------------------------------------------------------------------
JobExecutor::JobExecutor() :
      mbStarted(false),
      mMaxThreadNum(Config::getValueInt(Config::MAX_THREAD_NUMBER))
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
      // we must guarantee that at least one thread will be started!
      int maxNumThread = std::max(1, mMaxThreadNum);

      // we must ensure that the app will not exhaust system resources
      maxNumThread = std::min(THREAD_NUM_UPPER_BOUND, maxNumThread);

      for (int i = 0; i < maxNumThread; ++i)
      {
         mThreadPool.push_back(std::thread(&JobExecutor::processingLoop, this));
      }

      mbStarted = true;
   }

   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void JobExecutor::submitJob(IJobPtr job)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");

   mJobQueue.push(std::move(job));

   TRC_DEBUG_FUNC_EXIT(0U);
}

//TODO: watchdog thread
//---------------------------------------------------------------------------------------
void JobExecutor::processingLoop()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");

   while (IJobPtr pJob = mJobQueue.pop())
   {
      TRC_INFO(0U, "New job started: pJob=0x%p", (pJob.get()));

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
   for(int i=0; i < mMaxThreadNum; ++i)
   {
      class JobStop: public IJob
      {
         public:
            using IJob::IJob;

            std::string execute()
            {return "";}
      };

      IJobPtr pJob(new JobStop(IJob::DUMMY_TERMINATE));

      mJobQueue.push(std::move(pJob));
   }

   mbStarted = false;
}
