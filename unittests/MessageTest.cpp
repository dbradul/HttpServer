#include <protocol/Message.h>
#include <protocol/Request.h>
#include "gtest/gtest.h"

using namespace std;

//---------------------------------------------------------------
TEST(TestMessage, RequestParseTest)
//---------------------------------------------------------------
{
    // Arrange
    Request msg;
    string origin = "GET http://www.server.com/page.html HTTP/1.0";

    // Act
    msg.parse(origin);

    // Assert
    ASSERT_EQ(msg.getType(),     Request::Type::GET);
    ASSERT_EQ(msg.getUrl(),      "http://www.server.com/page.html");
    ASSERT_EQ(msg.getProtoVer(), "HTTP/1.0");

    ASSERT_EQ(origin, msg.getRawMessage());
}

//---------------------------------------------------------------
TEST(TestMessage, RequestSessionIdTest)
//---------------------------------------------------------------
{
    // Arrange
    Request msg;

    // Act
    msg.setSessionId(42);

    // Assert
    ASSERT_EQ(msg.getSessionId(), 42);
}

//---------------------------------------------------------------
TEST(TestMessage, RequestParseExceptionTest)
//---------------------------------------------------------------
{
    // Arrange
    Request msg;

    // Act
    // Assert
    EXPECT_THROW({msg.parse("Badly_formatted_message");}, ParseException);
}
