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
const std::string Response::VERSION                   = "HTTP/1.0";
const std::string Response::RET_CODE                  = "ReturnCode";
const std::string Response::RET_CODE_DESC             = "ReturnCodeDescription";
const std::string Response::HEADER_CONTENT_LENGTH     = "Content-Length";
const std::string Response::HEADER_CONTENT_TYPE       = "Content-type";

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
   Response::RET_CODE,
   Response::RET_CODE_DESC
};

//---------------------------------------------------------------------------------------
Response::Response()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   setHeaderField(HEADER_CONTENT_TYPE, "text/html");
   setHeaderField(PROTOCOL_VERSION,    VERSION);
   setResultCode(Response::OK);
   TRC_DEBUG_FUNC_EXIT(0U);

}

//---------------------------------------------------------------------------------------
Response::Response(const std::string& rawMessage)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
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
   setHeaderField(RET_CODE,      Utils::to_string(resultCode));
   setHeaderField(RET_CODE_DESC, mResultCodeDescriptions.at(resultCode));
}

//---------------------------------------------------------------------------------------
void Response::setVersion(const std::string& version)
//---------------------------------------------------------------------------------------
{
   setHeaderField(PROTOCOL_VERSION, version);
}

//---------------------------------------------------------------------------------------
std::string Response::toString() const
//---------------------------------------------------------------------------------------
{
   if (0 == mRawMessage.size())
   {
      mHeader[HEADER_CONTENT_LENGTH] = Utils::to_string(mBody.length());

      mRawMessage =
            mHeader.toString(getHeaderPreambleFields()) +
            HEADER_FIELD_DELIM +
            mBody;
   }

   return mRawMessage;
}


//---------------------------------------------------------------------------------------
const std::vector<std::string>& Response::getHeaderPreambleFields() const
//---------------------------------------------------------------------------------------
{
   return mHeaderPreambleFields;;
}
