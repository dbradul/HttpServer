/*******************************************************************
 * JobExecutor.h
 *
 *  @date: 28 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef JOBEXECUTOR_H_
#define JOBEXECUTOR_H_

#include "executor/IJob.h"
#include "common/BlockingQueue.h"
#include <vector>
#include <thread>

class JobExecutor
{
    public:
        JobExecutor();
        virtual ~JobExecutor();

        void start();
        void submitJob( IJob* job );
        void setMaxThreadNum(int maxThreadNum);
        BlockingQueue<IJob*> mJobQueue;
        static const int THREAD_NUM_UPPER_BOUND;

    private:
        void run();
        std::vector<std::thread> mThreadPool;
        bool mbStarted = false;
        int mMaxThreadNum;

};

#endif /* JOBEXECUTOR_H_ */
