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

        static const std::string RESPONSE_ok;
        static const std::string RESPONSE_created;
        static const std::string RESPONSE_accepted;
        static const std::string RESPONSE_no_content;
        static const std::string RESPONSE_multiple_choices;
        static const std::string RESPONSE_moved_permanently;
        static const std::string RESPONSE_moved_temporarily;
        static const std::string RESPONSE_not_modified;
        static const std::string RESPONSE_bad_request;
        static const std::string RESPONSE_unauthorized;
        static const std::string RESPONSE_forbidden;
        static const std::string RESPONSE_not_found;
        static const std::string RESPONSE_internal_server_error;
        static const std::string RESPONSE_not_implemented;
        static const std::string RESPONSE_bad_gateway;
        static const std::string RESPONSE_service_unavailable;

        const std::vector<std::string>& getHeaderPreambleFields() const;

        std::string toString() const;

    private:
};

#endif /* RESPONSE_H_ */
