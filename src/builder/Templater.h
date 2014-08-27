/*******************************************************************
 * Templater.h
 *
 *  @date: 16-8-2014
 *  @author: DB
 ******************************************************************/

#ifndef TEMPLATER_H_
#define TEMPLATER_H_

#include <string>
#include <vector>
#include <map>

class Templater
{
   public:
      static const std::string MACROS_ROOT;
      static const std::string MACROS_HEADER;
      static const std::string MACROS_FILEPATH;
      static const std::string MACROS_FILENAME;
      static const std::string MACROS_PERMS;
      static const std::string MACROS_SIZE;
      static const std::string MACROS_FOOTER;
      static const std::string MACROS_CONTENT;

      static const std::string PATH_ROOT_LAYOUT;
      static const std::string PATH_DIR_CONTENT;
      static const std::string PATH_DIR_CONTENT_LINE;
      static const std::string PATH_STR_CONTENT;
      static const std::string PATH_STR_CONTENT_LINE;
      static const std::string PATH_ERROR;

      Templater();
      explicit Templater(const std::string& templateFilepath);
      ~Templater();

      void setMacro(const std::string& macroName, const std::string& macroValue);

      std::string generate();

      static void purgeCache();

   private:
      std::map<std::string, std::string> mMacroses;
      std::string mContent;
      static std::map<std::string, std::string> mTemplateCache;
      static const std::string MACRO_TAG;
      static std::string lookupTemplate(const std::string& templateName);
};

#endif /* TEMPLATER_H_ */
