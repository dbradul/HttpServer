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
   std::string url = "/cygdrive/d/work/projects/HttpServer/templates/";

   Decorator<File> decorator;
   decorator.setURL(url);

   std::string page = pageBuilder.build(Utils::getDirContent(url), decorator);

   std::ofstream fs("C:/temp/1.html");
   fs << page;
   fs.close();

   // Assert
   ASSERT_TRUE(Utils::startsWith(page,"<!DOCTYPE html PUBLIC"));
}
