/*******************************************************************
 * JobFactoryGET.h
 *
 *  @date: 12 трав. 2014
 *  @author: DB
 ******************************************************************/

#ifndef JOBFACTORYGET_H_
#define JOBFACTORYGET_H_

#include "jobs/IJobFactory.h"

class JobFactoryGET: public IJobFactory
{
   public:
      JobFactoryGET();
      virtual ~JobFactoryGET();

      virtual IJob* createJob(const Request& request);
      virtual Callback createJobCallback(const Connector& dispatcher, const int sessionId);
};

#endif /* JOBFACTORYGET_H_ */
