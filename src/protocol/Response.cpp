/*******************************************************************
 * Response.cpp
 *
 *  @date: 28 ���. 2014
 *  @author: DB
 ******************************************************************/

#include "Response.h"
#include "stdio.h"
#include "common/traceout.h"

//----------------------------------------------------------------------
//ok response template
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_OK = "HTTP/1.0 200 OK\r\n\
Content-Length: %d\r\n\
Content-type: text/html\r\n";

//----------------------------------------------------------------------
//fail RESPONSE BAD REQUEST
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_FAIL_BAD_REQUEST = "HTTP/1.0 400 Bad Request\r\n\
Content-Length: %d\r\n\
Content-type: text/html\r\n";

//----------------------------------------------------------------------
//fail RESPONSE NOT FOUND
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_FAIL_NOT_FOUND = "HTTP/1.0 404 Not Found\r\n\
Content-Length: %d\r\n\
Content-type: text/html\r\n";

//----------------------------------------------------------------------
//fail RESPONSE INTERNAL SERVER ERROR
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_FAIL_INTERNAL_SERVER_ERROR = "HTTP/1.0 500 Internal server error\r\n\
Content-Length: %d\r\n\
Content-type: text/html\r\n";

//---------------------------------------------------------------------------------------
Response::Response()
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



