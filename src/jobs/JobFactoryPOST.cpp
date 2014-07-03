/*******************************************************************
 * JobFactoryPOST.cpp
 *
 *  @date: 12 трав. 2014
 *  @author: DB
 ******************************************************************/

#include <jobs/JobFactoryPOST.h>
#include <common/traceout.h>
#include <common/Utils.h>

//---------------------------------------------------------------------------------------
JobFactoryPOST::JobFactoryPOST()
{
    // TODO Auto-generated constructor stub

}

//---------------------------------------------------------------------------------------
JobFactoryPOST::~JobFactoryPOST()
{
    // TODO Auto-generated destructor stub
}

//---------------------------------------------------------------------------------------
IJob* JobFactoryPOST::createJob(const Request& request)
{
    class JobNOP : public IJob
    {
        public:
            std::string doJob()
            {
                return "";
            }
    };

    return new JobNOP;
}

//---------------------------------------------------------------------------------------
Callback JobFactoryPOST::createJobCallback(const Dispatcher& dispatcher, const int sessionId)
{
    return [&] (const std::string& result)
    {
        Response response;
        response.setHeader  (Response::RESPONSE_FAIL_BAD_REQUEST);
        response.setBody    ("Not supported");

        if( !dispatcher.writeResponse(response, sessionId) )
        {
            TRC_ERROR(0U, ( "Failed responding" ), NULL);
        }
    };
}
