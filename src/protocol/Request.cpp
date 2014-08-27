/*******************************************************************
 * Request.cpp
 *
 *  @date: 28 квіт. 2014
 *  @author: DB
 ******************************************************************/

#include <vector>
#include <stdexcept>
#include <algorithm>

#include "common/Utils.h"
#include "common/traceout.h"
#include "Request.h"

//---------------------------------------------------------------------------------------
const std::string Request::REQUEST_HOST   = "Host";
const std::string Request::PATH           = "Path";
const std::string Request::METHOD         = "Method";

//---------------------------------------------------------------------------------------
const std::vector<std::string>  Request::mHeaderPreambleFields =
//---------------------------------------------------------------------------------------
{
   Request::METHOD,
   Request::PATH,
   "Protocol",//Request::PROTOCOL_VERSION
};

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
const std::vector<std::string>& Request::getHeaderPreambleFields() const
//---------------------------------------------------------------------------------------
{
   return mHeaderPreambleFields;
}
