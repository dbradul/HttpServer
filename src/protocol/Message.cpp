/*******************************************************************
 * Message.cpp
 *
 *  @date: 30-7-2014
 *  @author: DB
 ******************************************************************/

#include <vector>
#include <exception>
#include <stdio.h>

#include "protocol/Message.h"
#include "protocol/Request.h"
#include "protocol/Response.h"
#include "common/traceout.h"
#include "common/Utils.h"

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
void Message::parse(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   parseHeader (rawMessage);
   parseBody   (rawMessage);
   mRawMessage = rawMessage;
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
      throw(std::range_error("Message is not correct"));
   }

   setHeaderField(getHeaderPreambleFields()[0], _1stField);
   setHeaderField(getHeaderPreambleFields()[1], _2ndField);
   setHeaderField(getHeaderPreambleFields()[2], _3rdField);

   size_t headerEnd     = rawMessage.find(HEADER_BODY_DELIM);
   size_t headerStart   = rawMessage.find(HEADER_FIELD_DELIM);

   if (   headerEnd   != std::string::npos
       && headerStart != std::string::npos)
   {
      std::string headerStr = rawMessage.substr(
                        headerStart + HEADER_FIELD_DELIM.size(),
            headerEnd - headerStart + HEADER_FIELD_DELIM.size());

      //error checking (parsing)
      std::vector<std::string> headerEntries;
      Utils::split(headerEntries, headerStr, HEADER_FIELD_DELIM);

      for (auto entry : headerEntries)
      {
         std::vector<std::string> headerEntryFields;
         Utils::split(  headerEntryFields,
                        entry,
                        HEADER_FIELD_NAME_DELIM);

         setHeaderField(headerEntryFields[0], headerEntryFields[1]);
      }
   }
}

//---------------------------------------------------------------------------------------
void Message::parseBody(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   size_t headerEnd = rawMessage.find(HEADER_BODY_DELIM);

   if (headerEnd != std::string::npos)
   {
      setBody(rawMessage.substr(headerEnd + HEADER_BODY_DELIM.size()));
   }
}

//---------------------------------------------------------------------------------------
const std::string& Message::getHeaderField(const std::string& headerFieldName) const
//---------------------------------------------------------------------------------------
{
   return mHeader[headerFieldName];
}

//---------------------------------------------------------------------------------------
void Message::setHeaderField(const std::string& fieldName, const std::string& fieldValue)
//---------------------------------------------------------------------------------------
{
   mHeader[fieldName] = fieldValue;
}

//---------------------------------------------------------------------------------------
const std::string& Message::getHeaderStr()
//---------------------------------------------------------------------------------------
{
   return mHeader.toString(getHeaderPreambleFields());
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
const std::string& Message::toString() const
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");

   if (0 == mRawMessage.size())
   {
      mRawMessage =
            mHeader.toString(getHeaderPreambleFields()) +
            HEADER_FIELD_DELIM +
            mBody;
   }

   TRC_DEBUG_FUNC_EXIT(0U);

   return mRawMessage;
}

//---------------------------------------------------------------------------------------
const std::string& Message::Header::toString(const std::vector<std::string>& preambleFields) const
//---------------------------------------------------------------------------------------
{
   if( mHeaderStr.empty() )
   {
      std::stringstream result;

      result << mHeaderFields.at(preambleFields[0]) << " ";
      result << mHeaderFields.at(preambleFields[1]) << " ";
      result << mHeaderFields.at(preambleFields[2]) << HEADER_FIELD_DELIM;

      auto skipPreambleFields = [&](const std::pair<std::string, std::string>& entry)
      {
         return ( std::find(preambleFields.begin(),
                            preambleFields.end(),
                            entry.first) == preambleFields.end() );
      };

      result << Utils::join( mHeaderFields,
                             Message::HEADER_FIELD_NAME_DELIM,
                             Message::HEADER_FIELD_DELIM,
                             skipPreambleFields );

      mHeaderStr = result.str();
   }
   return mHeaderStr;
}

//---------------------------------------------------------------------------------------
std::string& Message::Header::operator[](const std::string& key)
//---------------------------------------------------------------------------------------
{
   mHeaderStr.resize(0);
   return mHeaderFields[key];
}

//---------------------------------------------------------------------------------------
const std::string& Message::Header::operator[](const std::string& key) const
//---------------------------------------------------------------------------------------
{
   return mHeaderFields.at(key);
}
