#include <TestHarness.h>
#include <common/File.h>

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
   dir_a.setDir(true);
   dir_b.mName  = "ddd";
   dir_b.setDir(true);

   // Act
   // Assert
   ASSERT_TRUE(file_a < file_b);
   ASSERT_TRUE(dir_a  < dir_b);

   ASSERT_TRUE(dir_a < file_a);
   ASSERT_TRUE(dir_a < file_b);

   ASSERT_TRUE(dir_b < file_a);
   ASSERT_TRUE(dir_b < file_b);
}
