/*******************************************************************
 * IJob.h
 *
 *  @date: 28 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef IJOB_H_
#define IJOB_H_

#include <functional>
#include <string>
#include "executor/ICallback.h"

class IJob
{
    public:
        IJob();
        virtual ~IJob();

        void start()
        {
            std::string result = doJob();
            mCallback(result);
        }

        void setOnFinishCallback(tCallback callback)
        {
            mCallback = callback;
        }

    protected:
        virtual std::string doJob() = 0;

    private:
        tCallback mCallback;
};

#endif /* IJOB_H_ */
