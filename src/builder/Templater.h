/*******************************************************************
 * Templater.h
 *
 *  @date: 16 ����. 2014
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

      Templater();
      Templater(const std::string& templateFilepath);
      ~Templater();

      void load(const std::string& templateFilepath);
      void setMacro(const std::string& macroName, const std::string& macroValue);
      void setMacro(const std::string& macroName, unsigned long macroValue);
      std::string generate();

      static const std::string TEMPLATE_MACROS_ROOT;
      static const std::string TEMPLATE_MACROS_FILEPATH;
      static const std::string TEMPLATE_MACROS_FILENAME;
      static const std::string TEMPLATE_MACROS_PERMS;
      static const std::string TEMPLATE_MACROS_SIZE;
      static const std::string TEMPLATE_MACROS_TIME;
      static const std::string TEMPLATE_MACROS_IDX;
      static const std::string TEMPLATE_MACROS_CONTENT;
      static const std::string TEMPLATE_MACROS_FILE_CONTENT;
      static const std::string TEMPLATE_MACROS_LINE_CONTENT;
      static const std::string TEMPLATE_MACROS_TABLE_BODY;

      static const std::string TEMPLATE_PATH_ROOT_LAYOUT;
      static const std::string TEMPLATE_PATH_PAGE_TABLE;
      static const std::string TEMPLATE_PATH_PAGE_TABLE_LINE;
      static const std::string TEMPLATE_PATH_FILE_CONTENT;
      static const std::string TEMPLATE_PATH_FILE_CONTENT_LINE;

   private:
      std::string trimTags(std::string const &token);

      static std::map<std::string, std::string> mTemplateMap;
      std::string lookupTemplate(const std::string& templateName);
      static std::map<std::string, std::string> macroses;
      static const std::string MACRO_TAG;
      std::string mTemplateContent;
};

#endif /* TEMPLATER_H_ */
