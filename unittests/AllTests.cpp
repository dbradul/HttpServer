#include <TestHarness.h>
#include <builder/Templater.h>
#include <builder/File.h>

namespace
{
   struct Example
   {
         int value()
         {
            return 42;
         }
   };

   struct ExampleFixture
   {
     Example e_;
   };
} // namespace

TEST_F(ExampleFixture, when_doing_this_that_will_happen_as_a_result)
{
  // Arrange
  // Act
  // Assert
  ASSERT_EQ(42, e_.value());
}

/////////////////////////////////////////////////////////////////////////////
TEST(Example, simple_test_of_something_that_should_result_in_something)
{
  // Arrange
  Example e;
  // Act
  int value = e.value();
  // Assert
  ASSERT_EQ(42, value);
}

/////////////////////////////////////////////////////////////////////////////
TEST(Templater, simple_test)
{
  // Arrange
  Templater templater;
  Templater templater2(Templater::TEMPLATE_ROOT_LAYOUT);
  // Act
  // Assert
}


/////////////////////////////////////////////////////////////////////////////
TEST(File, simple_test)
{
   // Arrange
   File file_a;
   File file_b;

   File dir_a;
   File dir_b;

   file_a.mName = "aaa";
   file_b.mName = "bbb";

   dir_a.mName  = "ccc";
   dir_a.mIsDir = true;
   dir_b.mName  = "ddd";
   dir_b.mIsDir = true;

   // Act
   // Assert
   ASSERT_TRUE(file_a < file_b);
   ASSERT_TRUE(dir_a  < dir_b);

   ASSERT_TRUE(dir_a < file_a);
   ASSERT_TRUE(dir_a < file_b);

   ASSERT_TRUE(dir_b < file_a);
   ASSERT_TRUE(dir_b < file_b);
}
