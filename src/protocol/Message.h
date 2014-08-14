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

   protected:
      class Header
      {
         public:
            Header()
            {
            }

            const std::string& toString(const std::vector<std::string>& preambleFields) const
            {
               if( mHeaderStr.empty() )
               {
                  std::stringstream result;

                  result << operator[](preambleFields[0]);
                  result << " " << operator[](preambleFields[1]);
                  result << " " << operator[](preambleFields[2]);

                  ////result << HEADER_FIELD_DELIMITER;

                  auto f = [&](const std::pair<std::string, std::string>& entry)
                  {
                     return ( std::find(preambleFields.begin(),
                              preambleFields.end(),
                              entry.first) == preambleFields.end() );
                  };

//                  result << Utils::join( mHeaderFields,
//                                             HEADER_FIELD_NAME_DELIMITER,
//                                             HEADER_FIELD_DELIMITER,
//                                             f);

                  //TODO: enhance joiner with predicate
                  std::for_each( mHeaderFields.cbegin(),
                                 mHeaderFields.cend(),
                                 [&](const std::pair<std::string, std::string>& entry)
                                 {
                                    if( std::find(preambleFields.begin(),
                                                  preambleFields.end(),
                                                  entry.first) == preambleFields.end() )
                                    {
                                        result <<
                                              entry.first <<
                                              HEADER_FIELD_NAME_DELIM <<
                                              entry.second <<
                                              HEADER_FIELD_DELIM;
                                    }
                                 }
                               );

                  mHeaderStr = result.str();
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

         private:
            mutable std::string mHeaderStr;
            std::map<std::string, std::string> mHeaderFields; //std::list<std::string>
      };

   public:
      Message();
      Message(const std::string& message);
      virtual ~Message();

      void                 setHeader(const std::string& header);
      void                 setBody(const std::string& body);
      std::string&         setHeaderField(const std::string& headerFieldName);

      const std::string&   getRawMessage() const;
      const Header&        getHeader() const;
      const std::string&   getHeaderField(const std::string& fieldName) const;
      const std::string&   getBody() const;
      Header&              getHeader();
      std::string          getHeaderStr();
      virtual const std::vector<std::string>& getHeaderPreambleFields() const=0;

      static Message*      parse(const std::string& rawMessage);

      bool                 isValid() const;
      void                 setValid(bool valid);

      virtual std::string  toString() const = 0;

      static const std::string PROTOCOL;
      static const std::string RET_CODE;
      static const std::string RET_CODE_DESC;
      static const std::string CONTENT_LENGTH;
      static const std::string CONTENT_TYPE;
      //other header fields

   protected:
      mutable std::string  mRawMessage;
      mutable Header       mHeader;
      std::string          mBody;
      bool                 mbValid;

      void parseHeader (const std::string& rawMessage);
      void parseBody   (const std::string& rawMessage);
};

#endif /* MESSAGE_H_ */
