/*******************************************************************
 * Message.h
 *
 *  @date: 07/2014
 *  @author: DB
 ******************************************************************/

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <functional>
#include <exception>

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

      static const std::string METHOD_GET;
      static const std::string METHOD_POST;

      Message();
      virtual ~Message();

      void               parse(const std::string& rawMessage);
      virtual void       setBody(const std::string& body);
      void               setHeaderField(const std::string& fieldName, const std::string& fieldValue);
      const std::string& getHeaderField(const std::string& fieldName) const;
      const std::string& getBody() const;
      virtual std::string getStartLine() const;
      const std::string& getRawMessage() const;

   protected:
      class Header
      {
         public:
            const std::string&  toString(/*const std::vector<std::string>& preambleFields*/) const;
            std::string&        operator[](const std::string& key);
            const std::string&  operator[](const std::string& key) const;

         private:
            mutable std::string mHeaderStr;
            std::map<std::string, std::string> mHeaderFields;
      };

      virtual void parseStartLine   (const std::string& rawMessage){}
      void parseHeader      (const std::string& rawMessage);
      void parseBody        (const std::string& rawMessage);

      mutable std::string  mRawMessage;
      mutable Header       mHeader;
      std::string          mBody;

   private:
      DISALLOW_COPY_AND_ASSIGN(Message);
};

class ParseException : public std::runtime_error
{
public:
    ParseException(const std::string descr)
        : std::runtime_error(descr)
    {}
};

#endif /* MESSAGE_H_ */
