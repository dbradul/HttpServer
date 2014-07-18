/*******************************************************************
 * PageBuilder.cpp
 *
 *  @date: 4 ����. 2014
 *  @author: DB
 ******************************************************************/

#include "builder/PageBuilder.h"
#include "builder/Templater.h"
#include "builder/File.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------------------------------------
PageBuilder::PageBuilder()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
PageBuilder::~PageBuilder()
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildRootLayout(std::string& path)
{
   TRC_DEBUG_FUNC_ENTER(0U, "path='%s'", path.c_str());

   Templater templater(Templater::TEMPLATE_ROOT_LAYOUT);

   TRC_INFO(0, "Templater for root layout is created");

   std::string content;

//   try
//   {
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
//   }
//   catch (const std::exception& e)
//   {
//      TRC_ERROR(0U, "Reading dir content has failed");
//      content = "Reading content has failed for \"" + path + "\"";
//   }

   templater.setMacro("root", path);
   templater.setMacro("content", content);
   templater.setMacro("time", Utils::getCurrentDateTime());

   TRC_DEBUG_FUNC_EXIT (0U);

   return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildPageTable(const std::string& dirPath)
{
   TRC_DEBUG_FUNC_ENTER(0U, "dirPath='%s'", dirPath.c_str());

   Templater templater(Templater::TEMPLATE_PAGE_TABLE);

   std::vector<File> flist;

   std::string rootDir;
   Configuration::getValue(Configuration::CONFIG_ROOT_DIR, rootDir);

   TRC_INFO(0U, "workingDir='%s'", rootDir.c_str());

   Utils::readDir(rootDir, dirPath, flist);

   // sort to put dirs ahead of files
   std::sort(flist.begin(), flist.end());

   std::string tableBody;

   for_each(flist.begin(), flist.end(), [&](const File& file)
   {
      tableBody += buildPageTableLine(file);
   });

   templater.setMacro("table_body", tableBody);

   std::string result = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return result;
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildPageTableLine(const File& file)
{
   TRC_DEBUG_FUNC_ENTER(0U, "file='%s'", file.mName.c_str());

   Templater templater(Templater::TEMPLATE_PAGE_TABLE_LINE);
   templater.setMacro("filename", file.mName);
   templater.setMacro("filepath", "\"" + file.mRelativeFilePath + (file.mIsDir ? "/" : "") + "\""); //TODO: sync with buildRootLayout logic
   templater.setMacro("size", (file.size ? Utils::to_string(file.size) : ""));
   templater.setMacro("perms", file.mPermissions);

   TRC_DEBUG_FUNC_EXIT(0U);

   return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildFileContent(const std::string& filePath)
{
   TRC_DEBUG_FUNC_ENTER(0U, "filePath='%s'", filePath.c_str());

   std::string fileContent;
   std::string output;
   Templater templater(Templater::TEMPLATE_FILE_CONTENT);

   std::string workingDir;
   Configuration::getValue(Configuration::CONFIG_ROOT_DIR, workingDir);

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

   templater.setMacro("file_content", output);

   TRC_DEBUG_FUNC_EXIT(0U);

   return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildFileContentLine(const std::string& contentLine, int idx)
{
   TRC_DEBUG_FUNC_ENTER(0U, "contentLine='%s', idx=%d", contentLine.c_str(), idx);

   Templater templater(Templater::TEMPLATE_FILE_CONTENT_LINE);

   std::string result = contentLine;

   Utils::replaceAll(result, "<", "&lt;");
   Utils::replaceAll(result, ">", "&gt;");

   templater.setMacro("idx", Utils::to_string(idx));
   templater.setMacro("line_content", result);

   TRC_DEBUG_FUNC_EXIT(0U);

   return templater.generate();
}
