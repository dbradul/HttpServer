/*******************************************************************
 * Server.cpp
 *
 *  @date: 18 лип. 2014
 *  @author: DB
 ******************************************************************/

#include <core/Server.h>
#include "jobs/IJobFactory.h"
#include "executor/JobExecutor.h"
#include "protocol/Request.h"
#include "common/traceout.h"

//---------------------------------------------------------------------------------------
Server::Server()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Server::~Server()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Server::setConnector(const Connector& connector)
//---------------------------------------------------------------------------------------
{
   mConnector = connector;
}

//---------------------------------------------------------------------------------------
void Server::start()
//---------------------------------------------------------------------------------------
{
   JobExecutor jobExecutor;
   jobExecutor.start();

   mConnector.connect();

   // read and process requests until connection is closed
   //TODO: have special signal for the server to restart?
   while (Request request = mConnector.readRequest())
   {
      TRC_INFO(0U, "The new request is received: request='%s'", request.getHeader().toString().c_str());

      IJobFactory* jobFactory = IJobFactory::createInstance(request.header(Message::METHOD));

      IJob*    pJob             = jobFactory->createJob             (request);
      Callback jobCallback      = jobFactory->createJobCallback     (mConnector, request.getSessionId());
      Callback jobErrorCallback = jobFactory->createJobErrorCallback(mConnector, request.getSessionId());

      pJob->setOnFinishCallback(jobCallback);
      pJob->setOnErrorCallback(jobErrorCallback);

      jobExecutor.submitJob(pJob);

      TRC_INFO(0U, "The corresponding job is queued: pJob=0x%p, sessionId=%d", pJob, request.getSessionId());
   }
}
