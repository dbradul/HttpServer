/*******************************************************************
 * Response.cpp
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#include "common/traceout.h"
#include "Response.h"

using namespace std;

//---------------------------------------------------------------------------------------
Response::Response()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");

   setHeaderField (HEADER_CONTENT_TYPE,       TEXT_HTML);
   setHeaderField (HEADER_PROTOCOL_VERSION,   SUPPORTED_VERSION);
   setResultCode  (Response::OK);

   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Response::Response(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "rawMessage='%s'", rawMessage.c_str());

   parse(rawMessage);

   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Response::~Response()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Response::setResultCode(ResultCode resultCode)
//---------------------------------------------------------------------------------------
{
   setHeaderField(HEADER_RET_CODE,      Utils::to_string(resultCode));
   setHeaderField(HEADER_RET_CODE_DESC, mResultCodeDescriptions.at(resultCode));
}

//---------------------------------------------------------------------------------------
void Response::setVersion(const std::string& version)
//---------------------------------------------------------------------------------------
{
   setHeaderField(HEADER_PROTOCOL_VERSION, version);
}

//---------------------------------------------------------------------------------------
void Response::setBody(const std::string& body)
//---------------------------------------------------------------------------------------
{
   Message::setBody(body);
   mHeader[HEADER_CONTENT_LENGTH] = Utils::to_string(mBody.length());
}

//---------------------------------------------------------------------------------------
std::string Response::getStartLine() const
//---------------------------------------------------------------------------------------
{
    string header = mProtoVer;
    header += (" " + to_string(mErrCode));
    header += (" " + mErrStatus);

    return header;
}

//---------------------------------------------------------------------------------------
void Response::parseStartLine(const std::string &rawMessage)
//---------------------------------------------------------------------------------------
{
    char _1stField  [256] = {0};
    char _2ndField  [256] = {0};
    char _3rdField  [256] = {0};

    if ( sscanf( rawMessage.c_str(), "%[^ ] %[^ ] %[^ ]", _1stField, _2ndField, _3rdField ) != 3 )
    {
        throw ParseException("Request is not correct");
    }




    if (_2ndField == to_string(ResultCode::OK))
    {
        mErrCode = ResultCode::OK;
    }
    else if (_2ndField == to_string(ResultCode::CREATED))
    {
        mErrCode = ResultCode::CREATED;
    }
    else if (_2ndField == to_string(ResultCode::INTERNAL_SERVER_ERROR))
    {
        mErrCode = ResultCode::INTERNAL_SERVER_ERROR;
    }
    else
    {
        string msg = "Response error code is not recognized: ";
        msg += _2ndField;
        throw ParseException(msg);
    }

    mProtoVer   = _1stField;
    mErrStatus  = _3rdField;
}
