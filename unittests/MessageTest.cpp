#include <TestHarness.h>
#include <protocol/Message.h>
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////
TEST(Message, simple_test)
{
   // Arrange
   std::string fmtStr = "%s - %d";

   std::string fmtOut;
   fmtOut.resize(200);

   // Act
   sprintf(const_cast<char*>(fmtOut.c_str()), fmtStr.c_str(), "Meaning of life is", 42);

   // Assert
   ASSERT_TRUE(fmtOut == "Meaning of life is - 42");
}
