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
#include "common/Utils.h"
////#include "bits/shared_ptr.h"


class Message
{
   public:
      static const std::string HEADER_BODY_DELIMITER;
      static const std::string HEADER_FIELD_DELIMITER;
      static const std::string HEADER_FIELD_NAME_DELIMITER;

   protected:
      class Header
      {
         public:
            Header()
            {
            }

            Header(const std::string& preamble)
            {
               mPreamble = preamble;
            }

            const std::string& toString() const
            {
               if( mHeaderStr.empty() )
               {
                  mHeaderStr = mPreamble + HEADER_FIELD_DELIMITER;

                  mHeaderStr += Utils::join( mHeaderFields,
                                             HEADER_FIELD_NAME_DELIMITER,
                                             HEADER_FIELD_DELIMITER);
               }
               return mHeaderStr;
            }

            std::string& operator[](const std::string& key)
            {
               mHeaderStr.resize(0);
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

            //FIXME!
            std::string mPreamble;

         private:
            mutable std::string mHeaderStr;
            std::map<std::string, std::string> mHeaderFields; //std::list<std::string>
      };

   public:
      Message();
      Message(const std::string& preamble);
      virtual ~Message();

      static Message* parse(const std::string& rawMessage);

      void setHeader(const std::string& header);
      void setBody(const std::string& body);

      bool isValid() const;
      void setValid(bool valid);

      const std::string&   getRawMessage() const;
      const Header&        getHeader() const;
      const std::string&   getBody() const;
      const std::string&   header(const std::string& fieldName) const;
      Header&              header();
      std::string&         header(const std::string& headerFieldName);

      virtual std::string toString() const = 0;
      ////std::string generate() const;

      static const std::string METHOD;
      static const std::string PATH;
      static const std::string HOST;
      //other header fields

   protected:
      mutable std::string mRawMessage;
      Header mHeader;
      std::string mBody;
      bool mbValid;

};

#endif /* MESSAGE_H_ */
