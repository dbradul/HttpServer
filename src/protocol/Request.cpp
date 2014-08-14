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

const std::string Request::REQUEST_HOST           = "Host";
const std::string Request::PATH           = "Path";
const std::string Request::METHOD         = "Method";

//---------------------------------------------------------------------------------------
Request::Request()
   : mSessionId(-1)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Request::Request(const std::string& header)
   : /*Message(preamble)
   , */mSessionId(-1)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   parseHeader(header);
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
Request::operator bool()
//---------------------------------------------------------------------------------------
{
    return isValid();
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
std::string Request::toString() const
//---------------------------------------------------------------------------------------
{
   if (0 == mRawMessage.size())
   {
      mRawMessage =
            mHeader.toString(getHeaderPreambleFields()) +
            HEADER_FIELD_DELIM +
            mBody;
   }

   return mRawMessage;
}

//---------------------------------------------------------------------------------------
const std::vector<std::string>& Request::getHeaderPreambleFields() const
//---------------------------------------------------------------------------------------
{
   static std::vector<std::string> fields =
   {
      METHOD,
      PATH,
      PROTOCOL
   };

   return fields;
}
