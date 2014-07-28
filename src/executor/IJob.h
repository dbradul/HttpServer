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

        //TODO: templatize!
        virtual std::string execute() = 0;

        void setOnFinishCallback(const Callback& callback);
        void setOnErrorCallback(const Callback& callback);
        const Callback& getOnFinishCallback() const;
        const Callback& getOnErrorCallback() const;

        Callback onFinishCallback;
        Callback onErrorCallback;
};

#endif /* IJOB_H_ */
