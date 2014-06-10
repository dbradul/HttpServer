/*******************************************************************
 * JobFactory.h
 *
 *  @date: 2 ����. 2014
 *  @author: DB
 ******************************************************************/

#ifndef JOBFACTORY_H_
#define JOBFACTORY_H_

#include "executor/IJob.h"
#include "protocol/Request.h"
#include "Dispatcher.h"

class IJobFactory
{
    public:
        IJobFactory();
        virtual ~IJobFactory();

        static IJobFactory* create(const std::string& request);

        virtual IJob* createJob(const Request& request)=0;
        virtual tCallback createJobCallback(const Dispatcher& dispatcher, const int sessionId)=0;
};

#endif /* JOBFACTORY_H_ */
