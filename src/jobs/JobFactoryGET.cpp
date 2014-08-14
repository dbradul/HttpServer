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

namespace HTTP
{

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

            std::string result;
            std::string URL = Configuration::getInstance().getValueStr(Configuration::CONFIG_ROOT_DIR) + mPath;

            if (Utils::endsWith(URL, "/"))
            {
               std::vector<File> content = Utils::getDirContent(URL);
               HTMLDecorator<File> decorator;

               result = builder.build(URL, content, decorator);
            }

            else
            {
               std::vector<std::string> content = Utils::getFileContent(URL);
               HTMLDecorator<std::string> decorator;

               result = builder.build(URL, content, decorator);
            }

            return result;
         }

         JobRequestGET(const std::string& path)
         {
            mPath = path;
         }

      private:
         std::string mPath;
   };

   return new JobRequestGET(request.getHeaderField(Request::PATH));
}

}
