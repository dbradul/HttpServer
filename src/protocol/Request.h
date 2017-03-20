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

      enum Type
      {
          GET,
          HEAD,
          POST,
          PUT,
          DELETE,
          CONNECT,
          OPTIONS,
          TRACE,
      };

      Request();
      explicit Request(const std::string& rawMessage);
      virtual ~Request();

      void                  setSessionId(int sessionId);
      const int             getSessionId() const;
      Type                  getType() const;
      const std::string&    getUrl() const;
      const std::string&    getProtoVer() const;

      std::string getStartLine() const override;

   protected:
      void parseStartLine (const std::string& rawMessage) override;

   private:
      int mSessionId;
      Type mType;
      std::string mURL;
      std::string mProtoVer;
      DISALLOW_COPY_AND_ASSIGN(Request);
};

#endif /* REQUEST_H_ */
