/*******************************************************************
 * File.cpp
 *
 *  @date: 5 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <builder/File.h>
#include "common/traceout.h"

File::File()
: size(0),
  isDir(false)
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

File::~File()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

