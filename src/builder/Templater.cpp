/*******************************************************************
 * Templater.cpp
 *
 *  @date: 16-8-2014
 *  @author: DB
 ******************************************************************/

#include <cstddef>
#include <cstdio>
#include <iterator>
#include <utility>

#include <builder/Templater.h>
#include <common/Config.h>
#include <common/traceout.h>
#include <common/Utils.h>

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
std::map<std::string, std::string> Templater::mTemplateCache = {};

//---------------------------------------------------------------------------------------
const std::string Templater::MACRO_TAG = "##";

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
         TRC_DEBUG(0U, "macro recognized: '%s' -> '%s'", token.c_str(), iter->second.c_str());

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
std::string Templater::lookupTemplate(const std::string& templateName)
//---------------------------------------------------------------------------------------
{
   auto iter = mTemplateCache.find(templateName);

   if (iter == mTemplateCache.end())
   {
      std::string workDir = Config::getValueStr(Config::WORKING_DIR);

      mTemplateCache.insert({
                              templateName,
                              Utils::getTextFileContent((workDir + templateName).c_str())
                           });

      iter = mTemplateCache.find(templateName);
   }

   return iter->second;
}

//---------------------------------------------------------------------------------------
void Templater::purgeCache()
//---------------------------------------------------------------------------------------
{
   mTemplateCache.clear();
}
