/*******************************************************************
 * Message.cpp
 *
 *  @date: 30 квіт. 2014
 *  @author: DB
 ******************************************************************/

#include "protocol/Message.h"
#include "common/traceout.h"

//----------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Message::MESSAGE_HEADER_BODY_DELIMITER      = "\r\n\r\n";
const std::string Message::MESSAGE_HEADER_FIRST_FIELD_ENTRIES_DELIMITER      = " ";
const std::string Message::MESSAGE_HEADER_FIELD_DELIMITER       = "\r\n";
const std::string Message::MESSAGE_HEADER_FIELD_NAME_DELIMITER  = ": ";

//---------------------------------------------------------------------------------------
Message::Message()
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
std::string Message::toString() const
//---------------------------------------------------------------------------------------
{
   if (0 == mRawMessage.size())
   {
      //FIXME can we format better?
      std::string fmtHeader;
      char fmtHeader2[256];
      fmtHeader.resize(mHeader.toString().size() + 24);
      sprintf(fmtHeader2, /*&fmtHeader[0],*/ mHeader.toString().c_str(), mBody.length());

      mRawMessage =
            fmtHeader2 +
            MESSAGE_HEADER_FIELD_DELIMITER +
            mBody;
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
