/*******************************************************************
 * Message.h
 *
 *  @date: 30 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <functional>

#include "common/Utils.h"

class Message
{
   public:
      static const std::string HEADER_BODY_DELIM;
      static const std::string HEADER_FIELD_DELIM;
      static const std::string HEADER_FIELD_NAME_DELIM;

      static const std::string HEADER_PROTOCOL_VERSION;
      static const std::string HEADER_CONTENT_LENGTH;
      static const std::string HEADER_CONTENT_TYPE;
      //other header fields

      Message();
      virtual ~Message();

      void parse(const std::string& rawMessage);

      virtual void setBody(const std::string& body);
      void setHeaderField(const std::string& fieldName, const std::string& fieldValue);
      void setValid(bool valid);

      const std::string& getHeaderField(const std::string& fieldName) const;
      const std::string& getBody() const;
      std::string getHeaderStr();

      const std::string& toString() const;

   protected:
      class Header
      {
         public:
            const std::string& toString(const std::vector<std::string>& preambleFields) const;
            std::string& operator[](const std::string& key);
            const std::string& operator[](const std::string& key) const;

         private:
            mutable std::string mHeaderStr;
            std::map<std::string, std::string> mHeaderFields;
      };

      virtual const std::vector<std::string>& getHeaderPreambleFields() const=0;
      void parseHeader (const std::string& rawMessage);
      void parseBody   (const std::string& rawMessage);

      mutable std::string  mRawMessage;
      mutable Header       mHeader;
      std::string          mBody;

   private:
      DISALLOW_COPY_AND_ASSIGN(Message);
};

#endif /* MESSAGE_H_ */
