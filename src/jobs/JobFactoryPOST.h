/*******************************************************************
 * JobFactoryPOST.h
 *
 *  @date: 12 трав. 2014
 *  @author: DB
 ******************************************************************/

#ifndef JOBFACTORYPOST_H_
#define JOBFACTORYPOST_H_

#include "jobs/IJobFactory.h"

namespace HTTP
{

class JobFactoryPOST: public IJobFactory
{
   public:
      JobFactoryPOST();
      virtual ~JobFactoryPOST();

      virtual IJob* createJob(const Request& request);
      ////virtual Callback createJobCallback(const Connector& dispatcher, const int sessionId);
};

}
#endif /* JOBFACTORYPOST_H_ */
