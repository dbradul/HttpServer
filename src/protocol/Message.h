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
#include <list>
#include <sstream>
#include <algorithm>
//#include <cctype>
#include <functional>
#include "common/Utils.h"
////#include "bits/shared_ptr.h"

class Message
{
   public:
      static const std::string HEADER_BODY_DELIM;
      static const std::string HEADER_FIELD_DELIM;
      static const std::string HEADER_FIELD_NAME_DELIM;

      Message();
      virtual ~Message();

      void setBody(const std::string& body);
      void setHeaderField(const std::string& fieldName, const std::string& fieldValue);

      const std::string& getRawMessage() const;
      const std::string& getHeaderField(const std::string& fieldName) const;
      const std::string& getBody() const;
      std::string getHeaderStr();
      virtual const std::vector<std::string>& getHeaderPreambleFields() const=0;

      bool isValid() const;
      void setValid(bool valid);

      virtual std::string toString() const = 0;
      void parse(const std::string& rawMessage);

      static const std::string PROTOCOL_VERSION;
      static const std::string RET_CODE;
      static const std::string RET_CODE_DESC;
      static const std::string CONTENT_LENGTH;
      static const std::string CONTENT_TYPE;
      //other header fields

   protected:
      class Header
      {
         public:
            Header();

            const std::string& toString(const std::vector<std::string>& preambleFields) const;
            std::string& operator[](const std::string& key);
            const std::string& operator[](const std::string& key) const;

         private:
            mutable std::string mHeaderStr;
            std::map<std::string, std::string> mHeaderFields;
      };

      mutable std::string  mRawMessage;
      mutable Header       mHeader;
      std::string          mBody;
      bool                 mbValid;

      void parseHeader (const std::string& rawMessage);
      void parseBody   (const std::string& rawMessage);

   private:
      DISALLOW_COPY_AND_ASSIGN(Message);
};

#endif /* MESSAGE_H_ */
