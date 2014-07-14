/*******************************************************************
 * IJob.cpp
 *
 *  @date: 28 ���. 2014
 *  @author: DB
 ******************************************************************/

#include "IJob.h"
#include "common/traceout.h"

IJob::IJob()
{
   // TODO Auto-generated constructor stub
}

IJob::~IJob()
{
   // TODO Auto-generated destructor stub
}

void IJob::start()
{
   try
   {
      TRC_INFO(0, "Starting job execution");
      std::string result = doJob();

      TRC_INFO(0, "The following result is received: '%s'", result.c_str());

      TRC_INFO(0, "Calling callback");
      mCallback(result);
   }

   catch(const std::exception& e)
   {
      TRC_ERROR(0, "Failed to execute job: %s", e.what());
      mErrorCallback(e.what());
   }
}

void IJob::setOnFinishCallback(Callback callback)
{
   mCallback = callback;
}

void IJob::setOnErrorCallback(Callback callback)
{
   mErrorCallback = callback;
}
