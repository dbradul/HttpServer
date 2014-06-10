/*******************************************************************
 * Response.h
 *
 *  @date: 28 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "Message.h"

class Response : public Message
{
        class Header
        {
            typedef std::map<std::string, std::list<std::string> > tHeader;

            public:
                Header() {}
                Header(std::string header) {mHeaderStr = header;}
                std::string toString() {return mHeaderStr;};
                std::string mHeaderStr;
        };

    public:
        Response();
        virtual ~Response();

        static Response parse(std::string& rawMessage);

        void setHeader(const std::string& header);
        void setBody(const std::string& body);
        std::string assembleResponse(const std::string& body);
        std::string toString();

        static const std::string RESPONSE_OK;
        static const std::string RESPONSE_FAIL_BAD_REQUEST;
        static const std::string RESPONSE_FAIL_NOT_FOUND;

    private:
        Header mHeader;
        std::string mBody;
};

#endif /* RESPONSE_H_ */
