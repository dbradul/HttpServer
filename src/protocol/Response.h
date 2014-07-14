/*******************************************************************
 * Response.h
 *
 *  @date: 28 ���. 2014
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


    public:
        Response();
        virtual ~Response();

        static Response parse(std::string& rawMessage);

        std::string assembleResponse(const std::string& body);

        static const std::string RESPONSE_OK;
        static const std::string RESPONSE_FAIL_BAD_REQUEST;
        static const std::string RESPONSE_FAIL_NOT_FOUND;
        static const std::string RESPONSE_FAIL_INTERNAL_SERVER_ERROR;

    private:


};

#endif /* RESPONSE_H_ */
