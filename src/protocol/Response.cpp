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
//header template
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_HEADER_TEMPLATE = "%s\
Content-Length: %d\r\n\
Content-type: %s\r\n\r\n\
%s";

//---------------------------------------------------------------------------------------
//error code
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_ok =
  "HTTP/1.0 200 OK\r\n";
const std::string Response::RESPONSE_created =
  "HTTP/1.0 201 Created\r\n";
const std::string Response::RESPONSE_accepted =
  "HTTP/1.0 202 Accepted\r\n";
const std::string Response::RESPONSE_no_content =
  "HTTP/1.0 204 No Content\r\n";
const std::string Response::RESPONSE_multiple_choices =
  "HTTP/1.0 300 Multiple Choices\r\n";
const std::string Response::RESPONSE_moved_permanently =
  "HTTP/1.0 301 Moved Permanently\r\n";
const std::string Response::RESPONSE_moved_temporarily =
  "HTTP/1.0 302 Moved Temporarily\r\n";
const std::string Response::RESPONSE_not_modified =
  "HTTP/1.0 304 Not Modified\r\n";
const std::string Response::RESPONSE_bad_request =
  "HTTP/1.0 400 Bad Request\r\n";
const std::string Response::RESPONSE_unauthorized =
  "HTTP/1.0 401 Unauthorized\r\n";
const std::string Response::RESPONSE_forbidden =
  "HTTP/1.0 403 Forbidden\r\n";
const std::string Response::RESPONSE_not_found =
  "HTTP/1.0 404 Not Found\r\n";
const std::string Response::RESPONSE_internal_server_error =
  "HTTP/1.0 500 Internal Server Error\r\n";
const std::string Response::RESPONSE_not_implemented =
  "HTTP/1.0 501 Not Implemented\r\n";
const std::string Response::RESPONSE_bad_gateway =
  "HTTP/1.0 502 Bad Gateway\r\n";
const std::string Response::RESPONSE_service_unavailable =
  "HTTP/1.0 503 Service Unavailable\r\n";


//---------------------------------------------------------------------------------------
Response::Response()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
Response::Response(const std::string& preamble)
   : Message(preamble)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
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
      mRawMessage = Utils::formatString(  RESPONSE_HEADER_TEMPLATE,
                                          mHeader.mPreamble.c_str(),
                                          mBody.length(),
                                          "text/html",
                                          mBody.c_str() );
   }

   return mRawMessage;
}
