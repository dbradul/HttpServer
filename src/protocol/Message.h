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
   protected:
      class Header
      {
         typedef std::map<std::string, std::list<std::string> > tHeader;

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
            };

            std::string mHeaderStr;
            tHeader mHeaderFields;
      };

   public:
      Message();
      virtual ~Message();

      void setHeader(const std::string& header);
      void setBody(const std::string& body);

      const std::string& getRawMessage() const;
      const Header& getHeader() const;
      const std::string& getBody() const;
      std::string toString() const;

      static const std::string MESSAGE_HEADER_BODY_DELIMITER;
      static const std::string MESSAGE_HEADER_FIRST_FIELD_ENTRIES_DELIMITER;
      static const std::string MESSAGE_HEADER_FIELD_DELIMITER;
      static const std::string MESSAGE_HEADER_FIELD_NAME_DELIMITER;

   protected:
      mutable std::string mRawMessage;
      Header mHeader;
      std::string mBody;
};

#endif /* MESSAGE_H_ */
