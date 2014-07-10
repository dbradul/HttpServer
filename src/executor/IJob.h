/*******************************************************************
 * IJob.h
 *
 *  @date: 28 ���. 2014
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

        void start();
        void setOnFinishCallback(Callback callback);

    protected:
        virtual std::string doJob() = 0;

    private:
        Callback mCallback;
};

#endif /* IJOB_H_ */
