/*******************************************************************
 * Response.cpp
 *
 *  @date: 28 квіт. 2014
 *  @author: DB
 ******************************************************************/

#include "Response.h"
#include "stdio.h"

//----------------------------------------------------------------------
//ok response template
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_OK = "HTTP/1.0 200 OK\r\n\
Content-Length: %d\r\n\
Content-type: text/html\r\n\
\r\n";

//----------------------------------------------------------------------
//fail response bad request
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_FAIL_BAD_REQUEST = "HTTP/1.0 400 Bad Request\r\n\
Content-Length: %d\r\n\
Content-type: text/html\r\n\
\r\n\
<html>\n\
 <body>\n\
  <h1>Bad Request</h1>\n\
  <p>This server did not understand your request.</p>\n\
 </body>\n\
</html>\n";

//----------------------------------------------------------------------
//fail response not found
//---------------------------------------------------------------------------------------
const std::string Response::RESPONSE_FAIL_NOT_FOUND = "HTTP/1.0 404 Not Found\r\n\
Content-type: text/html\r\n\
\r\n\
<html>\n\
 <body>\n\
  <h1>Not Found</h1>\n\
  <p>The requested URL %s was not found on this server.</p>\n\
 </body>\n\
</html>\n";


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
std::string Response::toString()
//---------------------------------------------------------------------------------------
{
    //FIXME can we format better?
    char buff[1024] = {0};
    sprintf(buff, mHeader.toString().c_str(), mBody.length());
    return (buff + mBody);
}
