/*******************************************************************
 * Response.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include <iostream>
#include <string>
#include <map>
#include <list>

#include "Message.h"

class Response: public Message
{
public:
    enum ResultCode
    {
        OK = 200,
        CREATED = 201,
        //...
        INTERNAL_SERVER_ERROR = 500,
        //...
    };

    static const std::string SUPPORTED_VERSION;
    static const std::string HEADER_RET_CODE;
    static const std::string HEADER_RET_CODE_DESC;
    static const std::string HEADER_CONTENT_LENGTH;
    static const std::string HEADER_CONTENT_TYPE;
    static const std::string TEXT_HTML;

    Response();
    explicit Response(const std::string& rawMessage);
    virtual ~Response();

    void setResultCode(ResultCode resultCode);
    void setProtoVer(const std::string& version);
    void setBody(const std::string& body);

    std::string getStartLine() const override;

protected:
    void parseStartLine(const std::string &rawMessage) override;

private:
    static const std::map<ResultCode, std::string> mResultCodeDescriptions;

    std::string mProtoVer     = SUPPORTED_VERSION;
    ResultCode  mResultCode   = ResultCode::OK;
    std::string mErrStatus    = "";

    DISALLOW_COPY_AND_ASSIGN(Response);
};

#endif /* RESPONSE_H_ */
