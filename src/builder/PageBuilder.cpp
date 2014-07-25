/*******************************************************************
 * PageBuilder.cpp
 *
 *  @date: 4 ����. 2014
 *  @author: DB
 ******************************************************************/

#include "builder/PageBuilder.h"
#include "builder/Templater.h"
#include "common/File.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------------------
PageBuilder::PageBuilder()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
PageBuilder::~PageBuilder()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildRootLayout(const std::string& path)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "path='%s'", path.c_str());

   Templater templater(Templater::TEMPLATE_PATH_ROOT_LAYOUT);

   TRC_INFO(0, "Templater for root layout is created");

   std::string content;

   TRC_INFO(0, "Utils::endsWith(path, \"/\")");

   if (Utils::endsWith(path, "/"))
   {
      TRC_INFO(0, "Reading dir content. Why here!?");

      content = buildPageTable(path);
   }
   else
   {
      TRC_INFO(0, "Reading file content. Why here!?");

      content = buildFileContent(path);
   }

   templater.setMacro(Templater::TEMPLATE_MACROS_ROOT,      path);
   templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT,   content);
   templater.setMacro(Templater::TEMPLATE_MACROS_TIME,      Utils::getCurrentDateTime());

   TRC_DEBUG_FUNC_EXIT (0U);

   return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildPageTable(const std::string& dirPath)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "dirPath='%s'", dirPath.c_str());

   Templater templater(Templater::TEMPLATE_PATH_PAGE_TABLE);

   std::vector<File> flist;

   std::string rootDir = Configuration::getInstance().getValueStr(Configuration::CONFIG_ROOT_DIR);

   TRC_INFO(0U, "workingDir='%s'", rootDir.c_str());

   Utils::readDir(rootDir, dirPath, flist);

   // sort
   std::sort(flist.begin(), flist.end());

   std::string tableBody;

   for_each(flist.begin(), flist.end(), [&](const File& file)
   {
      tableBody += buildPageTableLine(file);
   });

   templater.setMacro(Templater::TEMPLATE_MACROS_TABLE_BODY, tableBody);

   std::string result = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return result;
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildPageTableLine(const File& file)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "file='%s'", file.mName.c_str());

   Templater templater(Templater::TEMPLATE_PATH_PAGE_TABLE_LINE);

   templater.setMacro(Templater::TEMPLATE_MACROS_FILENAME,  file.mName);
   templater.setMacro(Templater::TEMPLATE_MACROS_FILEPATH,  "\"" + file.mRelativeFilePath + (file.isDir() ? "/" : "") + "\""); //TODO: sync with buildRootLayout logic
   templater.setMacro(Templater::TEMPLATE_MACROS_SIZE,      Utils::to_string(file.getSize()));
   templater.setMacro(Templater::TEMPLATE_MACROS_PERMS,     file.getPermissions());

   TRC_DEBUG_FUNC_EXIT(0U);

   return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildFileContent(const std::string& filePath)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "filePath='%s'", filePath.c_str());

   std::string fileContent;
   std::string output;
   Templater templater(Templater::TEMPLATE_PATH_FILE_CONTENT);

   std::string workingDir = Configuration::getInstance().getValueStr(Configuration::CONFIG_ROOT_DIR);

   if (Utils::readAndCheckIfItIsBinary((workingDir + filePath).c_str(), fileContent))
   {
      output = "(binary content)";
   }

   else
   {
      std::vector<std::string> fileLines;
      Utils::split(fileLines, fileContent, "\r\n");

      int i = 1;
      for_each(fileLines.begin(), fileLines.end(), [&](const std::string& line)
      {
         output += buildFileContentLine(line, i++);
         output += "\n";
      });
   }

   templater.setMacro(Templater::TEMPLATE_MACROS_FILE_CONTENT, output);

   TRC_DEBUG_FUNC_EXIT(0U);

   return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildFileContentLine(const std::string& contentLine, int idx)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "contentLine='%s', idx=%d", contentLine.c_str(), idx);

   Templater templater(Templater::TEMPLATE_PATH_FILE_CONTENT_LINE);

   std::string result = contentLine;

   Utils::replaceAll(result, "<", "&lt;");
   Utils::replaceAll(result, ">", "&gt;");

   templater.setMacro(Templater::TEMPLATE_MACROS_IDX,          Utils::to_string(idx));
   templater.setMacro(Templater::TEMPLATE_MACROS_LINE_CONTENT, result);

   TRC_DEBUG_FUNC_EXIT(0U);

   return templater.generate();
}
