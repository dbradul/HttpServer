/*******************************************************************
 * JobFactoryPOST.cpp
 *
 *  @date: 12 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <jobs/JobFactoryPOST.h>
#include <common/traceout.h>
#include <common/Utils.h>

//---------------------------------------------------------------------------------------
JobFactoryPOST::JobFactoryPOST()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
JobFactoryPOST::~JobFactoryPOST()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
IJob* JobFactoryPOST::createJob(const Request& request)
//---------------------------------------------------------------------------------------
{
   class JobNOP: public IJob
   {
      public:
         std::string execute()
         {
            return "";
         }
   };

   return new JobNOP;
}

//---------------------------------------------------------------------------------------
Callback JobFactoryPOST::createJobCallback(const Connector& dispatcher, const int sessionId)
//---------------------------------------------------------------------------------------
{
   return [&] (const std::string& result)
   {
      Response response;
      response.setHeader (Response::RESPONSE_FAIL_BAD_REQUEST);

      //TODO: error template??
      response.setBody (
                           "<html>\n\
                               <body>\n\
                                  <h1>Bad Request</h1>\n\
                                  <p>This server did not understand your request.</p>\n\
                               </body>\n\
                            </html>\n"
                       );

      if( !dispatcher.writeResponse(response, sessionId) )
      {
         TRC_ERROR(0U, "Failed responding");
      }
   };
}
