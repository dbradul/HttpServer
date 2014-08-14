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
        Response(const std::string& preamble);
        virtual ~Response();

        static const std::string RESULT_OK;
        static const std::string RESULT_CREATED;
        static const std::string RESULT_ACCEPTED;
        static const std::string RESULT_NO_CONTENT;
        static const std::string RESULT_multiple_choices;
        static const std::string RESULT_moved_permanently;
        static const std::string RESULT_moved_temporarily;
        static const std::string RESULT_not_modified;
        static const std::string RESULT_bad_request;
        static const std::string RESULT_unauthorized;
        static const std::string RESULT_forbidden;
        static const std::string RESULT_not_found;
        static const std::string RESULT_INTERNAL_SERVER_ERROR;
        static const std::string RESULT_not_implemented;
        static const std::string RESULT_bad_gateway;
        static const std::string RESULT_service_unavailable;

        const std::vector<std::string>& getHeaderPreambleFields() const;

        std::string toString() const;

    private:
};

#endif /* RESPONSE_H_ */
