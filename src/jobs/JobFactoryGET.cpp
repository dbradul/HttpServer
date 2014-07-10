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
{
    // TODO Auto-generated constructor stub
}

//---------------------------------------------------------------------------------------
JobFactoryGET::~JobFactoryGET()
{
    // TODO Auto-generated destructor stub
}

//---------------------------------------------------------------------------------------
IJob* JobFactoryGET::createJob(const Request& request)
{
   class JobDirReader: public IJob
   {
      public:
         std::string doJob()
         {
            TRC_INFO(0, ("Building root layout for the path: %s", mPath.c_str()), NULL);

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

   return new JobDirReader(request.getPath());
}

//---------------------------------------------------------------------------------------
Callback JobFactoryGET::createJobCallback(const Dispatcher& dispatcher, const int sessionId)
{
    return [&dispatcher, sessionId] (const std::string& result)
    {
        Response response;
        response.setHeader  (Response::RESPONSE_OK);
        response.setBody    (result);

        TRC_INFO(0, ("Response constructed: %s", response.getHeader().toString().c_str()), NULL);
        TRC_INFO(0, ("Sending the response back to caller"), NULL);
        if( !dispatcher.writeResponse(response, sessionId) )
        {
            TRC_ERROR(0U, ( "Failed responding" ), NULL);
        }
    };
}
