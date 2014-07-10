/*******************************************************************
 * JobFactory.cpp
 *
 *  @date: 2 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <jobs/IJobFactory.h>
#include <jobs/JobFactoryGET.h>
#include <jobs/JobFactoryPOST.h>
#include <common/traceout.h>
#include "common/Utils.h"

//---------------------------------------------------------------------------------------
IJobFactory::IJobFactory()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
IJobFactory::~IJobFactory()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
// TODO: put into map to avoid recreation?
IJobFactory* IJobFactory::create(const std::string& request)
{
   TRC_DEBUG_FUNC_ENTER (0U, "");

   IJobFactory* pJobFactory = NULL;

   if (request == "GET")
   {
      pJobFactory = new JobFactoryGET;
   }

   else if (request == "POST")
   {
      pJobFactory = new JobFactoryPOST;
   }

   TRC_DEBUG_FUNC_EXIT (0U);

   return pJobFactory;
}

//---------------------------------------------------------------------------------------
Callback IJobFactory::createJobErrorCallback(const Dispatcher& dispatcher, const int sessionId)
{
   return [&dispatcher, sessionId] (const std::string& result)
   {
      Response response;
      response.setHeader (Response::RESPONSE_FAIL_INTERNAL_SERVER_ERROR);
      response.setBody (result);

      TRC_INFO(0U, "Response will be sent to a caller: %s", response.getHeader().toString().c_str());

      if( !dispatcher.writeResponse(response, sessionId) )
      {
         TRC_ERROR(0U, "Failed responding");
      }
   };
}

