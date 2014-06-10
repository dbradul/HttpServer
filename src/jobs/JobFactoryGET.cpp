/*******************************************************************
 * JobFactoryGET.cpp
 *
 *  @date: 12 трав. 2014
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
    class JobDirReader : public IJob
    {
        public:
            std::string doJob()
            {
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
tCallback JobFactoryGET::createJobCallback(const Dispatcher& dispatcher, const int sessionId)
{
    return [&dispatcher, sessionId] (const std::string& result)
    {
        Response response;
        response.setHeader  (Response::RESPONSE_OK);
        response.setBody    (result);

        if( !dispatcher.writeResponse(response, sessionId) )
        {
            TRC_ERROR(0U, ( "Failed responding" ), NULL);
        }
    };
}
