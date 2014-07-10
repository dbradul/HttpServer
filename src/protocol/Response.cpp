/*******************************************************************
 * Response.cpp
 *
 *  @date: 28 ���. 2014
 *  @author: DB
 ******************************************************************/

#include "Response.h"
#include "stdio.h"

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


//---------------------------------------------------------------------------------------
Response::Response()
//---------------------------------------------------------------------------------------
{
    // TODO Auto-generated constructor stub

}

//---------------------------------------------------------------------------------------
Response::~Response()
//---------------------------------------------------------------------------------------
{
    // TODO Auto-generated destructor stub
}

//---------------------------------------------------------------------------------------
void Response::setBody(const std::string& body)
//---------------------------------------------------------------------------------------
{
    mBody = body;
}

//---------------------------------------------------------------------------------------
void Response::setHeader(const std::string& header)
//---------------------------------------------------------------------------------------
{
    mHeader = Header(header);
}

//---------------------------------------------------------------------------------------
const Response::Header& Response::getHeader() const
//---------------------------------------------------------------------------------------
{
    return mHeader;
}

//---------------------------------------------------------------------------------------
std::string Response::toString() const
//---------------------------------------------------------------------------------------
{
    //FIXME can we format better?
    std::string fmtHeader;
    fmtHeader.resize(mHeader.toString().size() + 24);
    sprintf(&fmtHeader[0], mHeader.toString().c_str(), mBody.length());
    return (
             fmtHeader +
             MESSAGE_HEADER_FIELD_DELIMITER +
             mBody
           );
}
