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
        static const std::string METHOD;
        static const std::string PATH;
        static const std::string REQUEST_HOST;

        Request();
        explicit Request(const std::string& rawMessage);
        virtual ~Request();

        void setSessionId(int sessionId);
        const int getSessionId() const;

    protected:
        const std::vector<std::string>& getHeaderPreambleFields() const;

    private:
        int mSessionId;
        static const std::vector<std::string> mHeaderPreambleFields;
        DISALLOW_COPY_AND_ASSIGN(Request);
};

#endif /* REQUEST_H_ */
