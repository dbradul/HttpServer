/*******************************************************************
 * JobFactoryPOST.cpp
 *
 *  @date: 12 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <jobs/JobFactoryPOST.h>
#include <common/traceout.h>
#include <common/Utils.h>
#include <stdexcept>

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
            throw(std::logic_error(std::string("Not implemented")));;
         }
   };

   return new JobNOP;
}

