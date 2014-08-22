/*******************************************************************
 * Server.h
 *
 *  @date: 18 лип. 2014
 *  @author: DB
 ******************************************************************/

#ifndef SERVER_H_
#define SERVER_H_

#include "core/Connection.h"
#include "common/Config.h"
#include "executor/JobExecutor.h"

namespace HTTP
{

class Dispatcher
{
   public:
      Dispatcher();
      virtual ~Dispatcher();

      void setConnection(const Connection& connector);

      void start();
      void stop();

   private:
      Connection mConnection;
      JobExecutor mJobExecutor;
};

}
#endif /* SERVER_H_ */
