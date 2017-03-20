/*******************************************************************
 * Server.cpp
 *
 *  @date: 18-7-2014
 *  @author: DB
 ******************************************************************/

#include "core/Dispatcher.h"
#include "executor/JobFactory.h"
#include "executor/JobExecutor.h"
#include "protocol/Request.h"
#include "common/traceout.h"

namespace HTTP
{
//---------------------------------------------------------------------------------------
Dispatcher::Dispatcher()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Dispatcher::~Dispatcher()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Dispatcher::setConnection(const Connection& connector)
//---------------------------------------------------------------------------------------
{
   mConnection = connector;
}

//---------------------------------------------------------------------------------------
void Dispatcher::start()
//---------------------------------------------------------------------------------------
{
   mJobExecutor.start();
   mConnection.connect();

   // read and process requests until the connection is closed
   while (true)
   {
       Request request;

       try
       {
           mConnection.readRequest(request);

           TRC_INFO(0U, "The new request is received: request='%s'", request.getStartLine().c_str());

           auto pJob = JobFactory::createJob(request.getType(), request.getUrl());
           Callback onFinishCallback  = JobFactory::createOnFinishCallback   (mConnection, request.getSessionId());
           Callback onErrorCallback   = JobFactory::createOnErrorCallback    (mConnection, request.getSessionId());

           pJob->setOnFinishCallback  (onFinishCallback);
           pJob->setOnErrorCallback   (onErrorCallback);

           mJobExecutor.submitJob(std::move(pJob));

           TRC_INFO(0U, "The corresponding job is queued: pJob=0x%p, sessionId=%d", pJob.get(), request.getSessionId());
       }

       catch(ParseException& ex)
       {
           TRC_ERROR(0U,
                     "Exception while parsing request '%s': %s",
                     request.getRawMessage().c_str(),
                     ex.what());
       }

       catch (const std::exception& e)
       {
           stop();
           throw;
       }

   }
}

//---------------------------------------------------------------------------------------
void Dispatcher::stop()
//---------------------------------------------------------------------------------------
{
   mConnection.disconnect();
   mJobExecutor.stop();
}

}
