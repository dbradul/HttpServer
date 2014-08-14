/*******************************************************************
 * PageBuilder2.cpp
 *
 *  @date: 28 лип. 2014
 *  @author: DB
 ******************************************************************/

#include <builder/PageBuilder.h>
#include <jobs/JobFactoryGET.h>
#include "executor/IJob.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include "builder/Templater.h"
#include <algorithm>


//---------------------------------------------------------------------------------------
PageBuilder::PageBuilder()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
PageBuilder::~PageBuilder()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

