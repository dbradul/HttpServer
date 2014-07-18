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
Request::Request()
    : mbValid(false)
    , mSessionId(-1)
//---------------------------------------------------------------------------------------
{
    // TODO Auto-generated constructor stub
}

//---------------------------------------------------------------------------------------
Request::Request(const std::string& rawMessage)
    : mbValid(false)
    , mSessionId(-1)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Request::~Request()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//TODO FSM?
//TODO Move to the parent class?
//---------------------------------------------------------------------------------------
Request Request::parse(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
    Request result;

    std::vector<std::string> headerBody;
    std::vector<std::string> headerEntries;
    std::vector<std::string> header1stFieldEntries;

    Utils::split(headerBody, rawMessage, MESSAGE_HEADER_BODY_DELIMITER);

    if (headerBody.size() > 1)
    {
        result.mBody = headerBody[1];
    }

    result.setHeader(headerBody[0]);

    //error checking (parsing)
    Utils::split(headerEntries, headerBody[0], MESSAGE_HEADER_FIELD_DELIMITER);

    // 1st field is method name
    std::string _1stHeaderField = headerEntries[0];

    //error checking (parsing)
    Utils::split(header1stFieldEntries, _1stHeaderField, MESSAGE_HEADER_FIRST_FIELD_ENTRIES_DELIMITER);

    result.mMethod = header1stFieldEntries[0];
    result.mPath = header1stFieldEntries[1];

    // the rest are header fields
    ////for(std::string entry : headerEntries)
    for(size_t i = 1; i<headerEntries.size(); ++i)
    {
        std::vector<std::string> headerEntryFields;
        Utils::split(headerEntryFields, headerEntries[i], MESSAGE_HEADER_FIELD_NAME_DELIMITER);

        result.mHeaderFields.insert(std::pair<std::string, std::string>(headerEntryFields[0],
                                                                        headerEntryFields[1]));
    }

    result.mbValid = true;
    result.mRawMessage = rawMessage;

    // check out passing the reference
    return result;
}

//---------------------------------------------------------------------------------------
bool Request::isValid()
//---------------------------------------------------------------------------------------
{
    return mbValid;
}

//---------------------------------------------------------------------------------------
const std::string& Request::getHost() const
//---------------------------------------------------------------------------------------
{
    return mHeaderFields.at("Host");//["Host"];
}

//TODO: enum?
//---------------------------------------------------------------------------------------
const std::string& Request::getMethodType() const
//---------------------------------------------------------------------------------------
{
    return mMethod;
}

//---------------------------------------------------------------------------------------
void Request::setValid(bool valid)
//---------------------------------------------------------------------------------------
{
    mbValid = valid;
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
const std::string& Request::getPath() const
//---------------------------------------------------------------------------------------
{
    return mPath;
}

//---------------------------------------------------------------------------------------
Request::operator bool()
//---------------------------------------------------------------------------------------
{
    return isValid();
}
