/*******************************************************************
 * Server.cpp
 *
 *  @date: 18 лип. 2014
 *  @author: DB
 ******************************************************************/

#include <core/Dispatcher.h>
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
   JobExecutor jobExecutor;
   jobExecutor.start();

   mConnection.startListening();

   // read and process requests until the connection is closed
   while (Request request = mConnection.readRequest())
   {
      TRC_INFO(0U, "The new request is received: request='%s'", request.getHeaderStr().c_str());

//      IJobFactory* jobFactory = IJobFactory::createInstance(request.getHeaderField(Request::METHOD));
//
//      IJobPtr pJob(jobFactory->createJob(request));

      IJobPtr pJob(JobFactory::createJob(request));
      Callback onFinishCallback  = JobFactory::createJobOnFinishCallback   (mConnection, request.getSessionId());
      Callback onErrorCallback   = JobFactory::createJobOnErrorCallback    (mConnection, request.getSessionId());

      pJob->setOnFinishCallback  (onFinishCallback);
      pJob->setOnErrorCallback   (onErrorCallback);

      jobExecutor.submitJob(std::move(pJob));

      TRC_INFO(0U, "The corresponding job is queued: pJob=0x%p, sessionId=%d", pJob.get(), request.getSessionId());
   }
}

}

