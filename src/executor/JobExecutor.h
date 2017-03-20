/*******************************************************************
 * JobExecutor.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef JOBEXECUTOR_H_
#define JOBEXECUTOR_H_

#include "executor/IJob.h"
#include "common/BlockingQueue.h"
#include "common/Utils.h"
#include <vector>
#include <thread>


//TODO: watchdog thread
class JobExecutor
{
   public:
      static const int THREAD_NUM_UPPER_BOUND;
      static const int THREAD_NUM_LOWER_BOUND;

      JobExecutor();
      virtual ~JobExecutor();

      void start();
      void stop();

      void submitJob(IJob::Ptr job);
      void setMaxThreadNum(int maxThreadNum);
      BlockingQueuePtr<IJob> mJobQueue;

   private:
      void processingLoop();
      std::vector<std::thread> mThreadPool;
      bool mbStarted;
      int mMaxThreadNum;

      DISALLOW_COPY_AND_ASSIGN(JobExecutor);
};

#endif /* JOBEXECUTOR_H_ */
