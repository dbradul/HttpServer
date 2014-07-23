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
  mName(name),
  mIsDir(false)
{
}

File::~File()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

bool File::exists()
{
   return (!mName.empty() && access( mName.c_str(), F_OK ) != -1);
}
