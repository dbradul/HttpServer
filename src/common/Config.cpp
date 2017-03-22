/*******************************************************************
 * Config.cpp
 *
 *  @date: 5-8-2014
 *  @author: DB
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common/Config.h"
#include "common/Utils.h"
#include "common/traceout.h"
#include "builder/Templater.h"

namespace
{
char workingDir[FILENAME_MAX] = {};
std::string UNKNOWN = "<UNKNOWN>";
}

//---------------------------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Config::MAX_THREAD_NUMBER  = "MAX_THREAD_NUMBER";
const std::string Config::PORT               = "PORT";
const std::string Config::WORKING_DIR        = "WORKING_DIR";
const std::string Config::ROOT_DIR           = "ROOT_DIR";
const std::string Config::PAGE_TITLE         = "PAGE_TITLE";

//---------------------------------------------------------------------------------------
std::map<std::string, std::string> Config::m_settings =
{
    {MAX_THREAD_NUMBER,              "4"},
    {PORT,                           "8080"},
    {PAGE_TITLE,                     "HttpServer"},
    {WORKING_DIR,                    std::string(getcwd(workingDir, sizeof(workingDir)))},
    {ROOT_DIR,                       std::string(getcwd(workingDir, sizeof(workingDir)))},

    {UNKNOWN,                        UNKNOWN},
};

//---------------------------------------------------------------------------------------
void Config::setValue(const std::string& valueName, const std::string& value)
//---------------------------------------------------------------------------------------
{
    m_settings[valueName] = value;
}

//---------------------------------------------------------------------------------------
void Config::setValue(const std::string& valueName, unsigned long value)
//---------------------------------------------------------------------------------------
{
    setValue(valueName, std::to_string(value));
}

//---------------------------------------------------------------------------------------
const std::string& Config::getValueStr(const std::string& valueName)
//---------------------------------------------------------------------------------------
{
    auto iter = m_settings.find(valueName);

    return (iter != m_settings.end()) ? iter->second
                                      : m_settings[UNKNOWN];
}

//---------------------------------------------------------------------------------------
unsigned long Config::getValueInt(const std::string& valueName)
//---------------------------------------------------------------------------------------
{
    std::string valueStr = getValueStr(valueName);
    return Utils::to_int(valueStr.c_str());
}
