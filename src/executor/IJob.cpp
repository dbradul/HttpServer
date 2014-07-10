/*******************************************************************
 * IJob.cpp
 *
 *  @date: 28 ���. 2014
 *  @author: DB
 ******************************************************************/

#include "IJob.h"
#include "common/traceout.h"

IJob::IJob()
{
    // TODO Auto-generated constructor stub
}

IJob::~IJob()
{
    // TODO Auto-generated destructor stub
}

void IJob::start()
{
	TRC_INFO(0, ("Starting job execution"), NULL);
    std::string result = doJob();

	TRC_INFO(0, ("The following result is received: '%s'", result.c_str()), NULL);
	TRC_INFO(0, ("Calling callback"), NULL);
	mCallback(result);
}

void IJob::setOnFinishCallback(Callback callback)
{
    mCallback = callback;
}
