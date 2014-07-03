/*******************************************************************
 * Templater.h
 *
 *  @date: 16 трав. 2014
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
        Templater(const std::string& templateFilepath);
        virtual ~Templater();

        std::string generate();
        void setMacro(const std::string& macroName, const std::string& macroValue);
        void setMacro(const std::string& macroName, unsigned long macroValue);
        static std::map<std::string, std::string> mTemplateMap;

        static const std::string TEMPLATE_ROOT_LAYOUT;
        static const std::string TEMPLATE_PAGE_TABLE;
        static const std::string TEMPLATE_PAGE_TABLE_LINE;
        static const std::string TEMPLATE_FILE_CONTENT;
        static const std::string TEMPLATE_FILE_CONTENT_LINE;

    private:
        std::string lookupTemplate(const std::string& templateName);
        static std::map<std::string, std::string> macroses;
        static const std::string MACRO_TAG;
        std::string mTemplate;
};

#endif /* TEMPLATER_H_ */
