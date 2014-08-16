/*******************************************************************
 *  IJob.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef IJOB_H_
#define IJOB_H_

#include <functional>
#include <string>
#include <bits/unique_ptr.h>

typedef std::function<void(const std::string&)> Callback;

class IJob
{
   public:
      IJob();
      virtual ~IJob();

      //TODO: templatize!
      virtual std::string execute() = 0;

      void setOnFinishCallback(const Callback& callback);
      void setOnErrorCallback(const Callback& callback);

      Callback onFinishCallback;
      Callback onErrorCallback;
};

typedef std::unique_ptr<IJob> IJobPtr;

#endif /* IJOB_H_ */
