/*******************************************************************
 * Request.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef REQUEST_H_
#define REQUEST_H_

#include <string>
#include <map>

#include "protocol/Message.h"

class Request: public Message
{
   public:
      static const std::string HEADER_METHOD;
      static const std::string HEADER_PATH;

      Request();
      explicit Request(const std::string& rawMessage);
      virtual ~Request();

      void setSessionId(int sessionId);
      const int getSessionId() const;

   protected:
      const std::vector<std::string>& getHeaderPreambleFields() const;

   private:
      int mSessionId;
      static const std::vector<std::string> mHeaderPreambleFields;
      DISALLOW_COPY_AND_ASSIGN(Request);
};

#endif /* REQUEST_H_ */
