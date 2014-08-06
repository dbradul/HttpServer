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
#include "common/Utils.h"

#include <vector>
#include <exception>
#include <stdio.h>

//----------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Message::HEADER_BODY_DELIMITER                = "\r\n\r\n";
const std::string Message::HEADER_FIELD_DELIMITER               = "\r\n";
const std::string Message::HEADER_FIELD_NAME_DELIMITER          = ": ";

const std::string Message::HOST           = "Host";
const std::string Message::PATH           = "Path";
const std::string Message::METHOD         = "Method";
const std::string Message::PROTOCOL       = "Protocol";
const std::string Message::RET_CODE       = "ReturnCode";
const std::string Message::RET_CODE_DESC  = "ReturnCodeDescription";
const std::string Message::CONTENT_LENGTH = "Content-Length";
const std::string Message::CONTENT_TYPE   = "Content-type";

//---------------------------------------------------------------------------------------
Message::Message()
   : mbValid(false)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

////---------------------------------------------------------------------------------------
//Message::Message(const std::string& preamble)
//   : mbValid(false)
////---------------------------------------------------------------------------------------
//{
//   TRC_DEBUG_FUNC_ENTER(0U, "");
//   mHeader = Header(preamble);
//   TRC_DEBUG_FUNC_EXIT(0U);
//}

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
void Message::parseHeader(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   char _1stField  [256] = {0};
   char _2ndField  [256] = {0};
   char _3rdField  [256] = {0};

   if ( sscanf( rawMessage.c_str(), "%[^ ] %[^ ] %[^ ]", _1stField, _2ndField, _3rdField ) != 3 )
   {
      //  send_error( 400, "Bad Request", (char*) 0, "Can't parse request." );
      throw(std::range_error("Message is not correct"));
   }

   header(getHeaderPreambleFields()[0])   = _1stField;
   header(getHeaderPreambleFields()[1])   = _2ndField;
   header(getHeaderPreambleFields()[2])   = _3rdField;

   size_t headerEnd = rawMessage.find(HEADER_BODY_DELIMITER);
   size_t headerStart = rawMessage.find(HEADER_FIELD_DELIMITER);

   if (  headerEnd != std::string::npos &&
         headerStart != std::string::npos)
   {
      std::string headerStr = rawMessage.substr(
                        headerStart + HEADER_FIELD_DELIMITER.size(),
            headerEnd - headerStart + HEADER_FIELD_DELIMITER.size());

      //error checking (parsing)
      std::vector<std::string> headerEntries;
      Utils::split(headerEntries, headerStr, HEADER_FIELD_DELIMITER);

      for (auto entry : headerEntries)
      {
         std::vector<std::string> headerEntryFields;
         Utils::split(  headerEntryFields,
                        entry,
                        HEADER_FIELD_NAME_DELIMITER);

         header(headerEntryFields[0]) = headerEntryFields[1];
      }
   }

}

//---------------------------------------------------------------------------------------
void Message::parseBody(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   size_t headerEnd = rawMessage.find(HEADER_BODY_DELIMITER);
   if (headerEnd != std::string::npos)
   {
      setBody(rawMessage.substr(headerEnd + HEADER_BODY_DELIMITER.size()));
   }
}

//---------------------------------------------------------------------------------------
void Message::setHeader(const std::string& header)
//---------------------------------------------------------------------------------------
{
   parseHeader(header);
   mRawMessage.resize(0);
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

//---------------------------------------------------------------------------------------
////std::shared_ptr<Message> Message::parse(const std::string& rawMessage)
Message* Message::parse(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
////      message = std::shared_ptr<Request>(new Request());
   Message* message = Utils::startsWith(rawMessage, "HTTP/") ?
                        static_cast<Message *>(new Response()) :
                        static_cast<Message *>(new Request());

   message->parseHeader (rawMessage);
   message->parseBody   (rawMessage);

   message->mbValid = true;
   message->mRawMessage = rawMessage;

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

