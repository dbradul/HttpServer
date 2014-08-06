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

class Request : public Message
{
    public:

        Request();
        Request(const std::string& preamble);
        virtual ~Request();

        const std::vector<std::string>& getHeaderPreambleFields() const;

        void setSessionId(int sessionId);
        const int getSessionId() const;

        operator bool();
        std::string toString() const;

    private:
        int mSessionId;
};

#endif /* REQUEST_H_ */
