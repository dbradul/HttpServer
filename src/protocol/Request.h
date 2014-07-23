/*******************************************************************
 * Request.h
 *
 *  @date: 28-04-2014
 *  @author: DB
 ******************************************************************/

#ifndef REQUEST_H_
#define REQUEST_H_

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "protocol/Message.h"

//typedef std::map<std::string, std::string> tHeader;

class Request : public Message
{
    public:
        Request();
        Request(const std::string& rawMessage);
        Request(const Message& message);
        virtual ~Request();

        operator bool();

        void setSessionId(int sessionId);
        const int getSessionId() const;

    private:
        int         mSessionId;
};

#endif /* REQUEST_H_ */
