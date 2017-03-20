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
#include "core/Connection.h"

namespace HTTP
{

class JobFactory
{
   public:
      JobFactory();
      virtual ~JobFactory();

      //TODO: make it templateds
      static IJob::Ptr createJob(Request::Type requestType, const std::string& url);

      static Callback createOnFinishCallback(const Connection& dispatcher, const int sessionId);
      static Callback createOnErrorCallback(const Connection& dispatcher, const int sessionId);
};

}
#endif /* JOBFACTORY_H_ */
