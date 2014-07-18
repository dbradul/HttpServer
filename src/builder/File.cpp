/*******************************************************************
 * File.cpp
 *
 *  @date: 5 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <builder/File.h>
#include "common/traceout.h"
#include "common/Config.h"
#include <unistd.h>

File::File()
: size(0),
  mIsDir(false)
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

File::File(const std::string& name)
: size(0),
  mIsDir(false),
  mName(name)
{
}

File::~File()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

bool File::exists()
{
   std::string workDir;
   Config::getValue(Config::CONFIG_WORKING_DIR, workDir);

   bool bResult = false;
   if(!mName.empty() && access( (workDir + mName).c_str(), F_OK ) != -1)
   {
      bResult = true;
   }

   return bResult;
}
