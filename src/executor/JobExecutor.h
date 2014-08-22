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
#include <vector>
#include <thread>

//TODO: watchdog thread
class JobExecutor
{
   public:
      JobExecutor();
      virtual ~JobExecutor();

      void start();
      void stop();

      void submitJob(IJobPtr job);
      void setMaxThreadNum(int maxThreadNum);
      BlockingQueue<IJobPtr> mJobQueue;
      static const int THREAD_NUM_UPPER_BOUND;

   private:
      void processingLoop();
      std::vector<std::thread> mThreadPool;
      bool mbStarted;
      int mMaxThreadNum;

};

#endif /* JOBEXECUTOR_H_ */
