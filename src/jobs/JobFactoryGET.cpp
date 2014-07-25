/*******************************************************************
 * JobFactoryGET.cpp
 *
 *  @date: 12 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <jobs/JobFactoryGET.h>
#include "executor/IJob.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "builder/Templater.h"
#include "builder/PageBuilder.h"
#include <algorithm>

//---------------------------------------------------------------------------------------
JobFactoryGET::JobFactoryGET()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
JobFactoryGET::~JobFactoryGET()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
IJob* JobFactoryGET::createJob(const Request& request)
//---------------------------------------------------------------------------------------
{
   class JobDirReader: public IJob
   {
      public:
         std::string execute()
         {
            TRC_INFO(0, "Building root layout for the path: %s", mPath.c_str());

            PageBuilder builder;
            return builder.buildRootLayout(mPath);
         }

         JobDirReader(const std::string& path)
         {
            mPath = path;
         }

      private:
         std::string mPath;
   };

   return new JobDirReader(request.header(Message::PATH));
}

//---------------------------------------------------------------------------------------
Callback JobFactoryGET::createJobCallback(const Connector& dispatcher, const int sessionId)
//---------------------------------------------------------------------------------------
{
    return [&dispatcher, sessionId] (const std::string& result)
    {
        Response response;
        response.setHeader  (Response::RESPONSE_OK);
        response.setBody    (result);

        TRC_INFO(0, "Response constructed: %s", response.getHeader().toString().c_str());
        TRC_INFO(0, "Sending the response back to caller");

        if( !dispatcher.writeResponse(response, sessionId) )
        {
            TRC_ERROR(0U, "Failed sending response");
        }
    };
}
