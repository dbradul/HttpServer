/*******************************************************************
 * JobFactory.cpp
 *
 *  @date: 2 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <jobs/IJobFactory.h>
#include <jobs/JobFactoryGET.h>
#include <jobs/JobFactoryPOST.h>
#include "common/traceout.h"
#include "common/Utils.h"
#include "builder/Templater.h"

namespace HTTP
{

static const std::string METHOD_GET = "GET";
static const std::string METHOD_POST = "POST";

//---------------------------------------------------------------------------------------
IJobFactory::IJobFactory()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
IJobFactory::~IJobFactory()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
// TODO: put into map to avoid recreation?
IJobFactory* IJobFactory::createInstance(const std::string& request)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER (0U, "");

   IJobFactory* pJobFactory = NULL;

   if (request == METHOD_GET)
   {
      pJobFactory = new JobFactoryGET();
   }

   else if (request == METHOD_POST)
   {
      pJobFactory = new JobFactoryPOST();
   }

   TRC_DEBUG_FUNC_EXIT (0U);

   return pJobFactory;
}

//---------------------------------------------------------------------------------------
Callback IJobFactory::createJobOnFinishCallback(const Connection& connection, const int sessionId)
//---------------------------------------------------------------------------------------
{
   return [&connection, sessionId] (const std::string& result)
   {
      Response response(Response::RESULT_OK);
      response.setBody (result);

      TRC_INFO(0, "Response constructed: %s", response.getHeaderStr().c_str());

      if( !connection.writeResponse(response, sessionId) )
      {
         TRC_ERROR(0U, "Failed sending response");
      }
   };
}

//---------------------------------------------------------------------------------------
Callback IJobFactory::createJobOnErrorCallback(const Connection& connection, const int sessionId)
//---------------------------------------------------------------------------------------
{
   return [&connection, sessionId] (const std::string& result)
   {
      Templater templater(Templater::TEMPLATE_PATH_ERROR);
      templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT, result);

      Response response(Response::RESULT_INTERNAL_SERVER_ERROR);
      response.setBody (templater.generate());

      TRC_INFO(0U, "Response will be sent to a caller: %s", response.getHeaderStr().c_str());

      if( !connection.writeResponse(response, sessionId) )
      {
         TRC_ERROR(0U, "Failed responding");
      }
   };
}

}
