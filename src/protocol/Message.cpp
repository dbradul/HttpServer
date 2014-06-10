/*******************************************************************
 * Message.cpp
 *
 *  @date: 30 квіт. 2014
 *  @author: DB
 ******************************************************************/

#include <protocol/Message.h>

//----------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Message::MESSAGE_HEADER_BODY_DELIMITER      = "\r\n\r\n";
const std::string Message::MESSAGE_HEADER_FIRST_FIELD_ENTRIES_DELIMITER      = " ";
const std::string Message::MESSAGE_HEADER_FIELD_DELIMITER       = "\r\n";
const std::string Message::MESSAGE_HEADER_FIELD_NAME_DELIMITER  = ": ";

Message::Message()
{
    // TODO Auto-generated constructor stub
}

Message::~Message()
{
    // TODO Auto-generated destructor stub
}

const std::string& Message::getRawMessage() const
{
    return mRawMessage;
}
