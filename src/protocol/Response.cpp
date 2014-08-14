/*******************************************************************
 * Response.cpp
 *
 *  @date: 28 ���. 2014
 *  @author: DB
 ******************************************************************/

#include "Response.h"
#include "stdio.h"
#include "common/traceout.h"

//---------------------------------------------------------------------------------------
// error code
//---------------------------------------------------------------------------------------
const std::string Response::RESULT_OK =
   "HTTP/1.0 200 OK\r\n";
const std::string Response::RESULT_CREATED =
   "HTTP/1.0 201 Created\r\n";
const std::string Response::RESULT_ACCEPTED =
   "HTTP/1.0 202 Accepted\r\n";
const std::string Response::RESULT_NO_CONTENT =
   "HTTP/1.0 204 No Content\r\n";
const std::string Response::RESULT_multiple_choices =
   "HTTP/1.0 300 Multiple Choices\r\n";
const std::string Response::RESULT_moved_permanently =
   "HTTP/1.0 301 Moved Permanently\r\n";
const std::string Response::RESULT_moved_temporarily =
   "HTTP/1.0 302 Moved Temporarily\r\n";
const std::string Response::RESULT_not_modified =
   "HTTP/1.0 304 Not Modified\r\n";
const std::string Response::RESULT_bad_request =
   "HTTP/1.0 400 Bad Request\r\n";
const std::string Response::RESULT_unauthorized =
   "HTTP/1.0 401 Unauthorized\r\n";
const std::string Response::RESULT_forbidden =
   "HTTP/1.0 403 Forbidden\r\n";
const std::string Response::RESULT_not_found =
   "HTTP/1.0 404 Not Found\r\n";
const std::string Response::RESULT_internal_server_error =
   "HTTP/1.0 500 Internal Server Error\r\n";
const std::string Response::RESULT_not_implemented =
   "HTTP/1.0 501 Not Implemented\r\n";
const std::string Response::RESULT_bad_gateway =
   "HTTP/1.0 502 Bad Gateway\r\n";
const std::string Response::RESULT_service_unavailable =
   "HTTP/1.0 503 Service Unavailable\r\n";


//---------------------------------------------------------------------------------------
Response::Response()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   setHeaderField(CONTENT_TYPE) = "text/html";
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Response::Response(const std::string& header)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   parseHeader(header);
   setHeaderField(CONTENT_TYPE) = "text/html";
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
std::string Response::toString() const
//---------------------------------------------------------------------------------------
{
   if (0 == mRawMessage.size())
   {
      mHeader[CONTENT_LENGTH] = Utils::to_string(mBody.length());

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
   static std::vector<std::string> fields =
   {
      PROTOCOL,
      RET_CODE,
      RET_CODE_DESC
   };

   return fields;
}
