/*******************************************************************
 * JobFactoryGET.cpp
 *
 *  @date: 12-7-2014
 *  @author: DB
 ******************************************************************/

#include <jobs/JobFactoryGET.h>
#include "executor/IJob.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
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
   class JobRequestGET: public IJob
   {
      public:
         std::string execute()
         {
            TRC_INFO(0, "GET request for the path: %s", mPath.c_str());

            PageBuilder builder;

            std::string rootDir = Configuration::getInstance().getValueStr(Configuration::CONFIG_ROOT_DIR);

            return builder.build(rootDir + mPath);
         }

         JobRequestGET(const std::string& path)
         {
            mPath = path;
         }

      private:
         std::string mPath;
   };

   return new JobRequestGET(request.header(Message::PATH));
}

