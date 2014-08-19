/*******************************************************************
 * Templater.cpp
 *
 *  @date: 16 Jul 2014
 *  @author: DB
 ******************************************************************/

#include <fstream>
#include <sstream>
#include "errno.h"
#include "stdlib.h"

#include <builder/Templater.h>
#include "common/Utils.h"
#include "common/traceout.h"
#include "common/Config.h"

//---------------------------------------------------------------------------------------
Templater::Templater()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
Templater::Templater(const std::string& templateFilepath)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "templateFilepath='%s'", templateFilepath.c_str());

   mContent = lookupTemplate(templateFilepath);

   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
Templater::~Templater()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
std::map<std::string, std::string> Templater::mTemplateCache =
{
//   {TEMPLATE_ROOT_LAYOUT,       ""},
//   {TEMPLATE_PAGE_TABLE,        ""},
//   {TEMPLATE_PAGE_TABLE_LINE,   ""},
//   {TEMPLATE_FILE_CONTENT,      ""},
//   {TEMPLATE_FILE_CONTENT_LINE, ""},
};

//---------------------------------------------------------------------------------------
// Template pathes constants
//---------------------------------------------------------------------------------------
const std::string Templater::PATH_ROOT_LAYOUT         = "/templates/rootlayout.tmpl";
const std::string Templater::PATH_DIR_CONTENT         = "/templates/dircontent.tmpl";
const std::string Templater::PATH_DIR_CONTENT_LINE    = "/templates/dircontentline.tmpl";
const std::string Templater::PATH_STR_CONTENT         = "/templates/filecontent.tmpl";
const std::string Templater::PATH_STR_CONTENT_LINE    = "/templates/filecontentline.tmpl";
const std::string Templater::PATH_ERROR               = "/templates/error.tmpl";

//---------------------------------------------------------------------------------------
// Macros constants
//---------------------------------------------------------------------------------------
const std::string Templater::MACROS_ROOT              = "root";
const std::string Templater::MACROS_HEADER            = "header";
const std::string Templater::MACROS_FILEPATH          = "filepath";
const std::string Templater::MACROS_FILENAME          = "filename";
const std::string Templater::MACROS_PERMS             = "perms";
const std::string Templater::MACROS_SIZE              = "size";
const std::string Templater::MACROS_FOOTER            = "footer";
const std::string Templater::MACROS_CONTENT           = "content";

//---------------------------------------------------------------------------------------
const std::string Templater::MACRO_TAG = "##";

//---------------------------------------------------------------------------------------
void Templater::setMacro(const std::string& macroName, const std::string& macroValue)
//---------------------------------------------------------------------------------------
{
   mMacroses[macroName] = macroValue;
}

//---------------------------------------------------------------------------------------
std::string Templater::generate()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");

   std::size_t tagOpenBracket  = mContent.find(Templater::MACRO_TAG);
   std::size_t tagCloseBracket = mContent.find(Templater::MACRO_TAG, tagOpenBracket+1);

   while(   std::string::npos != tagOpenBracket
         && std::string::npos != tagCloseBracket)
   {
      std::string token = mContent.substr(   tagOpenBracket + Templater::MACRO_TAG.length(),
                           tagCloseBracket - tagOpenBracket - Templater::MACRO_TAG.length() );

      std::size_t lastModifiedSymbol = tagCloseBracket + 1;

      auto iter = mMacroses.find(token);
      if (iter != mMacroses.end())
      {
         TRC_DEBUG(0U, "macro recognized: '%s' -> '%s'", token.c_str(),
                                                         iter->second.c_str());

         mContent.replace( mContent.begin() + tagOpenBracket,
                           mContent.begin() + tagCloseBracket + Templater::MACRO_TAG.length(),
                           iter->second);

         lastModifiedSymbol = tagOpenBracket + iter->second.length();
      }

      tagOpenBracket  = mContent.find(Templater::MACRO_TAG, lastModifiedSymbol + 1);
      tagCloseBracket = mContent.find(Templater::MACRO_TAG, tagOpenBracket + 1);
   }

   TRC_DEBUG_FUNC_EXIT(0U);

   return mContent;
}

//---------------------------------------------------------------------------------------
std::string Templater::trimTags(std::string const &token)
//---------------------------------------------------------------------------------------
{
   std::string trimmed = token;
   const std::string tag = Templater::MACRO_TAG;
   size_t lengthOf2Tags = 2 * tag.length();

   if (token.length() >= lengthOf2Tags)
   {
      bool isTagged = false;
      isTagged = (0 == token.compare(0, tag.length(), tag));
      isTagged &= (0 == token.compare(token.length() - tag.length(), tag.length(), tag));

      if (isTagged)
      {
         trimmed = token.substr(tag.length(), token.length() - lengthOf2Tags);
      }
   }

   return trimmed;
}

//---------------------------------------------------------------------------------------
std::string Templater::lookupTemplate(const std::string& templateName)
//---------------------------------------------------------------------------------------
{
   auto iter = mTemplateCache.find(templateName);

   if (iter == mTemplateCache.end())
   {
      std::string workDir = Config::getValueStr(Config::WORKING_DIR);

      mTemplateCache.insert(
                              {
                                 templateName,
                                 Utils::getTextFileContent((workDir + templateName).c_str())
                              }
                           );

      iter = mTemplateCache.find(templateName);
   }

   return iter->second;
}
