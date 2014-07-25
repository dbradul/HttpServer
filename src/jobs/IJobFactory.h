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
#include "core/Connector.h"

class IJobFactory
{
    public:
        IJobFactory();
        virtual ~IJobFactory();

        static IJobFactory* createInstance(const std::string& request);

        //TODO: make it templated
        virtual IJob* createJob(const Request& request)=0;
        virtual Callback createJobCallback(const Connector& dispatcher, const int sessionId)=0;
        virtual Callback createJobErrorCallback(const Connector& dispatcher, const int sessionId);


};

#endif /* JOBFACTORY_H_ */
