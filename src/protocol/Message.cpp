/*******************************************************************
 * Message.cpp
 *
 *  @date: 30 квіт. 2014
 *  @author: DB
 ******************************************************************/

#include "protocol/Message.h"
#include "protocol/Request.h"
#include "protocol/Response.h"
#include "common/traceout.h"

#include <vector>
#include "common/Utils.h"

#include "stdio.h"

//----------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Message::HEADER_BODY_DELIMITER                = "\r\n\r\n";
const std::string Message::HEADER_FIELD_DELIMITER               = "\r\n";
const std::string Message::HEADER_FIELD_NAME_DELIMITER          = ": ";

const std::string Message::HOST     = "Host";
const std::string Message::PATH     = "Path";
const std::string Message::METHOD   = "Method";

//---------------------------------------------------------------------------------------
Message::Message()
   : mbValid(false)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Message::Message(const std::string& preamble)
   : mbValid(false)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   mHeader = Header(preamble);
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
std::string& Message::header(const std::string& headerFieldName)
//---------------------------------------------------------------------------------------
{
   return mHeader[headerFieldName];
}

//---------------------------------------------------------------------------------------
Message::Header& Message::header()
//---------------------------------------------------------------------------------------
{
   return mHeader;
}

//---------------------------------------------------------------------------------------
void Message::setBody(const std::string& body)
//---------------------------------------------------------------------------------------
{
    mBody = body;
    mRawMessage.resize(0);
}

//---------------------------------------------------------------------------------------
const std::string& Message::getBody() const
//---------------------------------------------------------------------------------------
{
   return mBody;
}

//TODO Regex
//---------------------------------------------------------------------------------------
////std::shared_ptr<Message> Message::parse(const std::string& rawMessage)
Message* Message::parse(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   char _1st  [256] = {0};
   char _2nd  [256] = {0};
   char _3rd  [256] = {0};

   if ( sscanf( rawMessage.c_str(), "%[^ ] %[^ ] %[^ ]", _1st, _2nd, _3rd ) != 3 )
   {
      //ERRORLOG
      //  send_error( 400, "Bad Request", (char*) 0, "Can't parse request." );
   }

   Message* message = NULL;

   if(Utils::startsWith(_1st, "HTTP/"))
   {
////      message = std::shared_ptr<Request>(new Request());
      message = new Response();
   }
   else
   {
      message = new Request();
   }

   message->header(METHOD)=_1st;
   message->header(PATH)=_2nd;

   std::vector<std::string> headerBody;
   std::vector<std::string> headerEntries;

   Utils::split(headerBody, rawMessage, HEADER_BODY_DELIMITER);

   if (headerBody.size() > 1)
   {
      message->setBody(headerBody[1]);
   }

   //error checking (parsing)
   Utils::split(headerEntries, headerBody[0], HEADER_FIELD_DELIMITER);

   for (size_t i = 1; i < headerEntries.size(); ++i)
   {
      std::vector<std::string> headerEntryFields;
      Utils::split(headerEntryFields, headerEntries[i], HEADER_FIELD_NAME_DELIMITER);

      message->header(headerEntryFields[0]) = headerEntryFields[1];
   }

   message->mbValid = true;
   message->mRawMessage = rawMessage;

   // check out passing the reference
   return message;
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
