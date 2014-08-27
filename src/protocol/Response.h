/*******************************************************************
 * Response.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <iostream>
#include <string>
#include <map>
#include <list>

#include "Message.h"

class Response: public Message
{
   public:
      enum ResultCode
      {
         OK = 200,
         CREATED = 201,
         //...
         INTERNAL_SERVER_ERROR = 500,
         //...
      };

      static const std::string VERSION;
      static const std::string HEADER_RET_CODE;
      static const std::string HEADER_RET_CODE_DESC;
      static const std::string HEADER_CONTENT_LENGTH;
      static const std::string HEADER_CONTENT_TYPE;
      static const std::string TEXT_HTML;

      Response();
      explicit Response(const std::string& rawMessage);
      virtual ~Response();

      void setResultCode(ResultCode resultCode);
      void setVersion(const std::string& version);
      void setBody(const std::string& body);

   protected:
      const std::vector<std::string>& getHeaderPreambleFields() const;

   private:
      static const std::map<ResultCode, std::string> mResultCodeDescriptions;
      static const std::vector<std::string> mHeaderPreambleFields;

      DISALLOW_COPY_AND_ASSIGN(Response);
};

#endif /* RESPONSE_H_ */
