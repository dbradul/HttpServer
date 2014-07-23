/*******************************************************************
 * Message.cpp
 *
 *  @date: 30 квіт. 2014
 *  @author: DB
 ******************************************************************/

#include "protocol/Message.h"
#include "common/traceout.h"

#include <vector>
#include "common/Utils.h"

//----------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Message::HEADER_BODY_DELIMITER                = "\r\n\r\n";
const std::string Message::HEADER_FIRST_FIELD_ENTRIES_DELIMITER = " ";
const std::string Message::HEADER_FIELD_DELIMITER               = "\r\n";
const std::string Message::HEADER_FIELD_NAME_DELIMITER          = ": ";

const std::string Message::HOST     = "Host";
const std::string Message::PATH     = "Path";
const std::string Message::METHOD   = "Method";
const std::string Message::CLIENT   = "Client";

//---------------------------------------------------------------------------------------
Message::Message()
   : mbValid(false)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Message::~Message()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
const std::string& Message::getRawMessage() const
//---------------------------------------------------------------------------------------
{
    return mRawMessage;
}

//---------------------------------------------------------------------------------------
const Message::Header& Message::getHeader() const
//---------------------------------------------------------------------------------------
{
    return mHeader;
}

//---------------------------------------------------------------------------------------
const std::string& Message::header(const std::string& headerFieldName) const
//---------------------------------------------------------------------------------------
{
   return mHeader[headerFieldName];
}

//---------------------------------------------------------------------------------------
std::string Message::toString() const
//---------------------------------------------------------------------------------------
{
   if (0 == mRawMessage.size())
   {
      mRawMessage = Utils::formatString(  mHeader.toString()+"%s%s",
                                          mBody.length(),
                                          HEADER_FIELD_DELIMITER.c_str(),
                                          mBody.c_str() );
   }

   return mRawMessage;
}

//---------------------------------------------------------------------------------------
void Message::setBody(const std::string& body)
//---------------------------------------------------------------------------------------
{
    mBody = body;
    mRawMessage.resize(0);
}

//---------------------------------------------------------------------------------------
void Message::setHeader(const std::string& header)
//---------------------------------------------------------------------------------------
{
    mHeader = Header(header);
    mRawMessage.resize(0);
}

//---------------------------------------------------------------------------------------
const std::string& Message::getBody() const
//---------------------------------------------------------------------------------------
{
   return mBody;
}

//TODO FSM?
//---------------------------------------------------------------------------------------
Message Message::parse(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   Message result;

   std::vector<std::string> headerBody;
   std::vector<std::string> headerEntries;
   std::vector<std::string> header1stFieldEntries;

   Utils::split(headerBody, rawMessage, HEADER_BODY_DELIMITER);

   result.setHeader(headerBody[0]);

   if (headerBody.size() > 1)
   {
      result.setBody(headerBody[1]);
   }

   //error checking (parsing)
   Utils::split(headerEntries, result.getHeader().toString(), HEADER_FIELD_DELIMITER);

   // 1st field is method name
   std::string _1stHeaderField = headerEntries[0];

   //error checking (parsing)
   Utils::split(header1stFieldEntries, _1stHeaderField, HEADER_FIRST_FIELD_ENTRIES_DELIMITER);

   result.mHeader[METHOD]   = header1stFieldEntries[0];
   result.mHeader[PATH]     = header1stFieldEntries[1];

   // the rest are header fields
   ////for(std::string entry : headerEntries)
   for (size_t i = 1; i < headerEntries.size(); ++i)
   {
      std::vector<std::string> headerEntryFields;
      Utils::split(headerEntryFields, headerEntries[i], HEADER_FIELD_NAME_DELIMITER);

      result.mHeader[headerEntryFields[0]] = headerEntryFields[1];
   }

   result.mbValid = true;
   result.mRawMessage = rawMessage;

   // check out passing the reference
   return result;
}

//---------------------------------------------------------------------------------------
bool Message::isValid() const
//---------------------------------------------------------------------------------------
{
    return mbValid;
}

//---------------------------------------------------------------------------------------
void Message::setValid(bool valid)
//---------------------------------------------------------------------------------------
{
    mbValid = valid;
}
