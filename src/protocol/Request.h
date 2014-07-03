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

typedef std::map<std::string, std::string> tHeader;

class Request : public Message
{
    public:
        Request();
        Request(const std::string& rawMessage);
        virtual ~Request();

        static Request parse(const std::string& rawMessage);
        bool isValid();
        void setValid(bool valid);
        void setSessionId(int sessionId);

        const std::string& getHost() const;
        const std::string& getPath() const;
        const std::string& getMethodType() const;
        const int getSessionId() const;

    private:
        std::string mMethod;
        std::string mPath;
        tHeader     mHeaderFields;
        std::string mBody;
        bool        mbValid;
        int         mSessionId;
};

#endif /* REQUEST_H_ */
