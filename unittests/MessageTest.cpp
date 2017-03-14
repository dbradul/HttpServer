#include <protocol/Message.h>
#include <protocol/Request.h>
#include "gtest/gtest.h"

using namespace std;

/////////////////////////////////////////////////////////////////
TEST(TestMessage, RequestTest)
{
   // Arrange
   Request msg;
   
   // Act
   msg.parse("GET http://www.server.com/page.html HTTP/1.0");

   // Assert
   ASSERT_EQ(msg.getHeaderField(Request::HEADER_METHOD),            Message::METHOD_GET);
   ASSERT_EQ(msg.getHeaderField(Request::HEADER_PATH),              "http://www.server.com/page.html");
   ASSERT_EQ(msg.getHeaderField(Request::HEADER_PROTOCOL_VERSION),  "HTTP/1.0");
}


/////////////////////////////////////////////////////////////////
TEST(TestMessage, RequestSessionIdTest)
{
   // Arrange
   Request msg;

   // Act
   msg.setSessionId(42);

   // Assert
   ASSERT_EQ(msg.getSessionId(), 42);
}

