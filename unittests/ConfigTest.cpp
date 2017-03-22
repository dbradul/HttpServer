#include "gtest/gtest.h"
#include "common/Config.h"

using namespace std;

////////////////////////////////////////////////////////
TEST(TestConfig, BaseTest)
{
    // Arrange
    Config::setValue("A", "A");
    Config::setValue("B", "42");
    Config::setValue("C", 5);

    // Act
    // Assert
    EXPECT_EQ(Config::getValueStr("A"), "A");
    EXPECT_EQ(Config::getValueStr("B"), "42");
    EXPECT_EQ(Config::getValueInt("B"), 42);
    EXPECT_EQ(Config::getValueStr("C"), "5");
    EXPECT_EQ(Config::getValueInt("C"), 5);
    EXPECT_EQ(Config::getValueStr("D"), "<UNKNOWN>");
}
