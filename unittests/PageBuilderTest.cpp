#include <TestHarness.h>
#include <builder/PageBuilder.h>
#include <common/Utils.h>
#include <fstream>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
TEST(PageBuilder, simple_test)
{
   // Arrange
   PageBuilder pageBuilder;

   // Act
   std::string page = pageBuilder.build("/cygdrive/d/work/projects/HttpServer/templates/");

   std::ofstream fs("C:/temp/1.html");
   fs << page;
   fs.close();

   // Assert
   ASSERT_TRUE(Utils::startsWith(page,"<!DOCTYPE html PUBLIC"));
}
