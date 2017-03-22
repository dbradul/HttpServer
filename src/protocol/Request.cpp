/*******************************************************************
 * Request.cpp
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#include <vector>
#include <stdexcept>
#include <algorithm>

#include "common/Utils.h"
#include "common/traceout.h"
#include "Request.h"

using namespace std;

//---------------------------------------------------------------------------------------
Request::Request()
    : mSessionId(-1)
    //---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");
    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Request::Request(const std::string& rawMessage)
    : mSessionId(-1)
    , mType(Type::GET)
    //---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "rawMessage='%s'", rawMessage.c_str());

    parse(rawMessage);

    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Request::~Request()
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "");
    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Request::setSessionId(int sessionId)
//---------------------------------------------------------------------------------------
{
    mSessionId = sessionId;
}

//---------------------------------------------------------------------------------------
const int Request::getSessionId() const
//---------------------------------------------------------------------------------------
{
    return mSessionId;
}

//---------------------------------------------------------------------------------------
Request::Type Request::getType() const
//---------------------------------------------------------------------------------------
{
    return mType;
}

//---------------------------------------------------------------------------------------
const string &Request::getUrl() const
//---------------------------------------------------------------------------------------
{
    return mURL;
}

//---------------------------------------------------------------------------------------
const string &Request::getProtoVer() const
//---------------------------------------------------------------------------------------
{
    return mProtoVer;
}

//---------------------------------------------------------------------------------------
void Request::parseStartLine(const std::string &rawMessage)
//---------------------------------------------------------------------------------------
{
    char _1stField  [256] = {0};
    char _2ndField  [256] = {0};
    char _3rdField  [256] = {0};

    if ( sscanf( rawMessage.c_str(), "%[^ ] %[^ ] %[^ ]", _1stField, _2ndField, _3rdField ) != 3 )
    {
        throw ParseException("Request is not correct");
    }



    if (_1stField == Message::METHOD_POST)
    {
        mType = Type::POST;
    }
    else if (_1stField == Message::METHOD_GET)
    {
        mType = Type::GET;
    }
    else
    {
        string msg = "Request type is not recognized: ";
        msg += _1stField;
        throw ParseException(msg);
    }

    mURL        = _2ndField;
    mProtoVer   = _3rdField;
}

string Request::getStartLine() const
{
    string header = "GET"; //FIXME
    header += (" " + mURL);
    header += (" " + mProtoVer);

    return header;
}
