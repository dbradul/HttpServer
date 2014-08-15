#include <TestHarness.h>
#include <common/File.h>

/////////////////////////////////////////////////////////////////////////////
TEST(File, simple_test)
{
   // Arrange
   File file_a("aaa");
   File file_b("bbb");

   File dir_a("ccc");
   File dir_b("ddd");

   dir_a.setDir(true);
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
