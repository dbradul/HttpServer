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

class Message
{
   public:
      static const std::string HEADER_BODY_DELIMITER;
      static const std::string HEADER_FIRST_FIELD_ENTRIES_DELIMITER;
      static const std::string HEADER_FIELD_DELIMITER;
      static const std::string HEADER_FIELD_NAME_DELIMITER;

   protected:
      class Header
      {
         public:
            Header()
            {
            }

            Header(std::string header)
            {
               mHeaderStr = header;
            }

            const std::string& toString() const
            {
               return mHeaderStr;
            }

            std::string& operator[](const std::string& key)
            {
               return mHeaderFields[key];
            }

            const std::string& operator[](const std::string& key) const
            {
               return mHeaderFields.at(key);
            }

            operator const std::string&()
            {
               return toString();
            }

            operator const char*()
            {
               return toString().c_str();
            }

         private:
            std::string mHeaderStr;
            std::map<std::string, std::string> mHeaderFields; //std::list<std::string>
      };

   public:
      Message();
      virtual ~Message();

      static Message parse(const std::string& rawMessage);

      void setHeader(const std::string& header);
      void setBody(const std::string& body);

      bool isValid() const;
      void setValid(bool valid);

      const std::string&   getRawMessage() const;
      const Header&        getHeader() const;
      const std::string&   getBody() const;
      const std::string&   header(const std::string& fieldName) const;
      std::string toString() const;

      static const std::string METHOD;
      static const std::string PATH;
      static const std::string HOST;
      static const std::string CLIENT;
      //other header fields

   protected:
      mutable std::string mRawMessage;
      Header mHeader;
      std::string mBody;
      bool mbValid;

};

#endif /* MESSAGE_H_ */
