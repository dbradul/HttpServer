/*******************************************************************
 * Templater.cpp
 *
 *  @date: 16 трав. 2014
 *  @author: DB
 ******************************************************************/

#include <builder/Templater.h>
#include <errno.h>
#include <fstream>
#include <sstream>
#include "common/Utils.h"
#include "stdlib.h"

//---------------------------------------------------------------------------------------
Templater::Templater()
{
}

//---------------------------------------------------------------------------------------
Templater::Templater(const std::string& templateFilepath)
{
    ////mTemplate = Utils::getTextFileContent(templateFilepath.c_str());;
    mTemplate = lookupTemplate(templateFilepath);
}

//---------------------------------------------------------------------------------------
Templater::~Templater()
{
    // TODO Auto-generated destructor stub
}

//---------------------------------------------------------------------------------------
std::map<std::string, std::string> Templater::macroses =
{
   {"root",     "NOT DEFINED"},
   {"filepath", "NOT DEFINED"},
   {"filename", "NOT DEFINED"},
   {"perms",    "NOT DEFINED"},
   {"size",     "NOT DEFINED"},
   {"time",     "NOT DEFINED"},
   {"idx",      "NOT DEFINED"},
};


std::map<std::string, std::string> Templater::mTemplateMap =
{
//   {TEMPLATE_ROOT_LAYOUT,       ""},
//   {TEMPLATE_PAGE_TABLE,        ""},
//   {TEMPLATE_PAGE_TABLE_LINE,   ""},
//   {TEMPLATE_FILE_CONTENT,      ""},
//   {TEMPLATE_FILE_CONTENT_LINE, ""},
};


//---------------------------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Templater::TEMPLATE_ROOT_LAYOUT         = "templates/rootlayout.tmpl";
const std::string Templater::TEMPLATE_PAGE_TABLE          = "templates/pagetable.tmpl";
const std::string Templater::TEMPLATE_PAGE_TABLE_LINE     = "templates/pagetableline.tmpl";
const std::string Templater::TEMPLATE_FILE_CONTENT        = "templates/filecontent.tmpl";
const std::string Templater::TEMPLATE_FILE_CONTENT_LINE   = "templates/filecontentline.tmpl";

//---------------------------------------------------------------------------------------
const std::string Templater::MACRO_TAG = "##";

//---------------------------------------------------------------------------------------
void Templater::setMacro(const std::string& macroName, const std::string& macroValue)
{
    macroses[macroName] = macroValue;
}

//---------------------------------------------------------------------------------------
void Templater::setMacro(const std::string& macroName, unsigned long macroValue)
{
    char buffer[16];
    sprintf(buffer, "%lu", macroValue);
    setMacro(macroName, buffer);
}

//---------------------------------------------------------------------------------------
bool isMacro(std::string const &token, std::string const &tag, std::string& macroTrimmed);

//---------------------------------------------------------------------------------------
std::string Templater::generate()
{
    std::string result;
    std::stringstream sstream(mTemplate);

    if (sstream)
    {
//        sstream.seekg(0, std::ios::end);
//        result.resize(sstream.tellg());
//        sstream.seekg(0, std::ios::beg);

        std::string token;
        while (sstream >> token)
        {
            std::string macro;
            if (isMacro(token, MACRO_TAG, macro))
            {
                auto iter = macroses.find(macro);
                if (iter != macroses.end())
                {
                    result += iter->second;
                    result += " ";
                }
            }
            else
            {
                result += token;
                result += " ";
            }
        }
    }

    return result;
}

//---------------------------------------------------------------------------------------
// regex optimization
bool isMacro(std::string const &token, std::string const &tag, std::string& macroTrimmed)
{
    bool isMacro = false;
    macroTrimmed = token;
    size_t lengthOf2Tags = 2 * tag.length();

    if (token.length() >= lengthOf2Tags)
    {
        isMacro = (0 == token.compare(0, tag.length(), tag));
        isMacro &= (0 == token.compare(token.length() - tag.length(), tag.length(), tag));

        if (isMacro)
        {
            macroTrimmed = token.substr(tag.length(), token.length() - lengthOf2Tags);
        }
    }

    return isMacro;
}

//---------------------------------------------------------------------------------------
std::string Templater::lookupTemplate(const std::string& templateName)
{
    auto iter = mTemplateMap.find(templateName);

    if (iter == mTemplateMap.end())
    {
        mTemplateMap.insert(
                              { templateName,
                                Utils::getTextFileContent(templateName.c_str())
                              }
                           );

        iter = mTemplateMap.find(templateName);
    }

    return iter->second;
}

