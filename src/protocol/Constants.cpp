/*******************************************************************
 * Constants.cpp
 *
 * Contains protocol constants
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/
#include "protocol/Message.h"
#include "protocol/Request.h"
#include "protocol/Response.h"

//---------------------------------------------------------------------------------------
//
// Message
//
//---------------------------------------------------------------------------------------
const std::string Message::HEADER_BODY_DELIM       = "\r\n\r\n";
const std::string Message::HEADER_FIELD_DELIM      = "\r\n";
const std::string Message::HEADER_FIELD_NAME_DELIM = ": ";
const std::string Message::HEADER_PROTOCOL_VERSION = "Protocol";


const std::string Message::METHOD_GET              = "GET";
const std::string Message::METHOD_POST             = "POST";

//---------------------------------------------------------------------------------------
//
// Request
//
//---------------------------------------------------------------------------------------
const std::string Request::HEADER_PATH             = "Path";
const std::string Request::HEADER_METHOD           = "Method";

//---------------------------------------------------------------------------------------
//
// Response
//
//---------------------------------------------------------------------------------------
const std::string Response::SUPPORTED_VERSION      = "HTTP/1.0";
const std::string Response::TEXT_HTML              = "text/html";
const std::string Response::HEADER_RET_CODE        = "ReturnCode";
const std::string Response::HEADER_RET_CODE_DESC   = "ReturnCodeDescription";
const std::string Response::HEADER_CONTENT_LENGTH  = "Content-Length";
const std::string Response::HEADER_CONTENT_TYPE    = "Content-type";

//---------------------------------------------------------------------------------------
const std::map<Response::ResultCode, std::string> Response::mResultCodeDescriptions =
//---------------------------------------------------------------------------------------
{
      {Response::OK,                               "OK"},
      {Response::CREATED,                          "Created"},
      //...
      {Response::INTERNAL_SERVER_ERROR,            "Internal Server Error"}
      //...
};
