/*******************************************************************
 * Response.cpp
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

//#include "stdio.h"

#include "common/traceout.h"
#include "Response.h"

//---------------------------------------------------------------------------------------
const std::string Response::VERSION                = "HTTP/1.0";
const std::string Response::HEADER_RET_CODE        = "ReturnCode";
const std::string Response::HEADER_RET_CODE_DESC   = "ReturnCodeDescription";
const std::string Response::HEADER_CONTENT_LENGTH  = "Content-Length";
const std::string Response::HEADER_CONTENT_TYPE    = "Content-type";
const std::string Response::TEXT_HTML              = "text/html";

//---------------------------------------------------------------------------------------
const std::map<Response::ResultCode, std::string> Response::mResultCodeDescriptions =
//---------------------------------------------------------------------------------------
{
      {Response::OK,                      "OK"},
      {Response::CREATED,                 "Created"},
      //...
      {Response::INTERNAL_SERVER_ERROR,   "Internal Server Error"}
      //...
};

//---------------------------------------------------------------------------------------
const std::vector<std::string>  Response::mHeaderPreambleFields =
//---------------------------------------------------------------------------------------
{
   "Protocol",//Response::PROTOCOL_VERSION,
   Response::HEADER_RET_CODE,
   Response::HEADER_RET_CODE_DESC
};

//---------------------------------------------------------------------------------------
Response::Response()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");

   setHeaderField (HEADER_CONTENT_TYPE,       TEXT_HTML);
   setHeaderField (HEADER_PROTOCOL_VERSION,   VERSION);
   setResultCode  (Response::OK);

   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Response::Response(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "rawMessage='%s'", rawMessage.c_str());

   parse(rawMessage);

   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Response::~Response()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Response::setResultCode(ResultCode resultCode)
//---------------------------------------------------------------------------------------
{
   setHeaderField(HEADER_RET_CODE,      Utils::to_string(resultCode));
   setHeaderField(HEADER_RET_CODE_DESC, mResultCodeDescriptions.at(resultCode));
}

//---------------------------------------------------------------------------------------
void Response::setVersion(const std::string& version)
//---------------------------------------------------------------------------------------
{
   setHeaderField(HEADER_PROTOCOL_VERSION, version);
}

//---------------------------------------------------------------------------------------
void Response::setBody(const std::string& body)
//---------------------------------------------------------------------------------------
{
   Message::setBody(body);
   mHeader[HEADER_CONTENT_LENGTH] = Utils::to_string(mBody.length());
}

//---------------------------------------------------------------------------------------
const std::vector<std::string>& Response::getHeaderPreambleFields() const
//---------------------------------------------------------------------------------------
{
   return mHeaderPreambleFields;
}
