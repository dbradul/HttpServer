/*******************************************************************
 * PageBuilder2.cpp
 *
 *  @date: 28 лип. 2014
 *  @author: DB
 ******************************************************************/

#include <builder/PageBuilder.h>
#include <jobs/JobFactoryGET.h>
#include "executor/IJob.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include "builder/Templater.h"
#include <algorithm>

//---------------------------------------------------------------------------------------
class ContentReader
//---------------------------------------------------------------------------------------
{
   public:
      template<typename T>
      std::vector<T> getContent(std::string URL);
};

//---------------------------------------------------------------------------------------
template<>
std::vector<std::string> ContentReader::getContent(std::string URL)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "URL='%s'", URL.c_str());

   std::string fileContent;
   std::vector<std::string> entries;

   ////fileContent = Utils::getTextFileContent((workingDir + filePath).c_str());
   if (Utils::readAndCheckIfItIsBinary(URL.c_str(), fileContent))
   {
      entries.push_back("(binary content)");
   }

   else
   {
      Utils::split(entries, fileContent, "\r\n");
   }

   TRC_DEBUG_FUNC_EXIT(0U);

   return entries;
}

//---------------------------------------------------------------------------------------
template<>
std::vector<File> ContentReader::getContent(std::string URL)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "URL='%s'", URL.c_str());

   std::vector<File> flist;

   Utils::readDir(URL, flist);

   std::sort(flist.begin(), flist.end());

   TRC_DEBUG_FUNC_EXIT(0U);

   return flist;
}

//---------------------------------------------------------------------------------------
class Decorator
//---------------------------------------------------------------------------------------
{
   public:
      template<typename T>
      std::string decorateContent(std::vector<T> entries)
      {
         TRC_DEBUG_FUNC_ENTER(0U, "");

         std::string decoratedEntries;

         for(T entry : entries)
         {
            std::string decoratedEntry = decorateEntry(entry);
            decoratedEntries += decoratedEntry;
            decoratedEntries += "\n";
         }

         std::string decoratedBody = decorateBody<T>(decoratedEntries);

         TRC_DEBUG_FUNC_EXIT(0U);

         return decoratedBody;
      }

   protected:
      template<typename T>
      std::string decorateBody(std::string body)
      {
         TRC_DEBUG_FUNC_ENTER(0U, "Body='%s'", body.c_str());

         Templater templater = getBodyTemplater<T>();

         std::string decoratedBody;

         templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT, body);

         decoratedBody = templater.generate();

         TRC_DEBUG_FUNC_EXIT(0U);

         return decoratedBody;
      }

      template<typename T>
      std::string decorateEntry(T entry);

      template<typename T>
      Templater getBodyTemplater();

      template<typename T>
      Templater getEntryTemplater();
};

//---------------------------------------------------------------------------------------
template<>
Templater Decorator::getBodyTemplater<std::string>()
//---------------------------------------------------------------------------------------
{
   return Templater(Templater::TEMPLATE_PATH_FILE_CONTENT);
}

//---------------------------------------------------------------------------------------
template<>
Templater Decorator::getEntryTemplater<std::string>()
//---------------------------------------------------------------------------------------
{
   return Templater(Templater::TEMPLATE_PATH_FILE_CONTENT_LINE);
}

//---------------------------------------------------------------------------------------
template<>
Templater Decorator::getBodyTemplater<File>()
//---------------------------------------------------------------------------------------
{
   return Templater(Templater::TEMPLATE_PATH_DIR_CONTENT);
}

//---------------------------------------------------------------------------------------
template<>
Templater Decorator::getEntryTemplater<File>()
//---------------------------------------------------------------------------------------
{
   return Templater(Templater::TEMPLATE_PATH_DIR_CONTENT_LINE);
}

//---------------------------------------------------------------------------------------
template<>
std::string Decorator::decorateEntry(std::string entry)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "entry='%s'", entry.c_str());

   Utils::replaceAll(entry, "<", "&lt;");
   Utils::replaceAll(entry, ">", "&gt;");

   Templater templater = getEntryTemplater<decltype(entry)>();

   templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT, entry);

   std::string decoratedEntry = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return decoratedEntry;
}

//---------------------------------------------------------------------------------------
template<>
std::string Decorator::decorateEntry<File>(File entry)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "entry='%s'", entry.mName.c_str());

   Templater templater = getEntryTemplater<decltype(entry)>();

   templater.setMacro(Templater::TEMPLATE_MACROS_FILENAME,  entry.mName);
   templater.setMacro(Templater::TEMPLATE_MACROS_FILEPATH,  "\"" + entry.mReferenceFilePath + (entry.isDir() ? "/" : "") + "\""); //TODO: sync with buildRootLayout logic
   templater.setMacro(Templater::TEMPLATE_MACROS_SIZE,      Utils::to_string(entry.getSize()));
   templater.setMacro(Templater::TEMPLATE_MACROS_PERMS,     entry.getPermissions());

   std::string decoratedEntry = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return decoratedEntry;
}

//---------------------------------------------------------------------------------------
PageBuilder::PageBuilder()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
PageBuilder::~PageBuilder()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::build(const std::string& URL)
//---------------------------------------------------------------------------------------
{
   ContentReader reader;
   Decorator decorator;

   std::string result;

   TRC_DEBUG_FUNC_ENTER(0U, "path='%s'", URL.c_str());

   Templater templater(Templater::TEMPLATE_PATH_ROOT_LAYOUT);

   if (Utils::endsWith(URL, "/"))
   {
      result = decorator.decorateContent(reader.getContent<File>(URL));
   }
   else
   {
      result = decorator.decorateContent(reader.getContent<std::string>(URL));
   }

   templater.setMacro(Templater::TEMPLATE_MACROS_ROOT,      URL);
   templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT,   result);
   templater.setMacro(Templater::TEMPLATE_MACROS_TIME,      Utils::getCurrentDateTime());

   std::string output = templater.generate();

   TRC_DEBUG_FUNC_EXIT (0U);

   return output;
}
