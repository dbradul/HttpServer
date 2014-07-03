/*******************************************************************
 * JobFactory.cpp
 *
 *  @date: 2 трав. 2014
 *  @author: DB
 ******************************************************************/

#include <jobs/IJobFactory.h>
#include <jobs/JobFactoryGET.h>
#include <jobs/JobFactoryPOST.h>
#include <common/traceout.h>
#include "common/Utils.h"

//---------------------------------------------------------------------------------------
IJobFactory::IJobFactory()
{
    // TODO Auto-generated constructor stub
}

//---------------------------------------------------------------------------------------
IJobFactory::~IJobFactory()
{
    // TODO Auto-generated destructor stub
}

//---------------------------------------------------------------------------------------
// TODO: put into map to avoid recreation?
IJobFactory* IJobFactory::create(const std::string& request)
{
    IJobFactory* pJobFactory = NULL;

    if(request == "GET")
    {
        pJobFactory = new JobFactoryGET;
    }

    else if(request == "POST")
    {
        pJobFactory = new JobFactoryPOST;
    }

    return pJobFactory;
}

