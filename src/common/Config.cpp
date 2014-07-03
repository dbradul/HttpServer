/*******************************************************************
 * Config.cpp
 *
 *  @date: 5 черв. 2014
 *  @author: DB
 ******************************************************************/

#include <common/Config.h>
#include <stdio.h>
#include <stdlib.h>
#include <common/Utils.h>

//---------------------------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Config::CONFIG_MAX_THREAD_NUMBER  = "PUTIN_HUYLO";
const std::string Config::CONFIG_PORT               = "SLAVA_UKRAYNI";
const std::string Config::CONFIG_WORKING_DIR        = "HEROYAM_SLAVA";


std::map<std::string, std::string> Config::settings =
{
   {CONFIG_MAX_THREAD_NUMBER,   "4"},
   {CONFIG_PORT,                "8080"},
   {CONFIG_WORKING_DIR,         ""},
};

Config::Config()
{
}

Config::~Config()
{
    // TODO Auto-generated destructor stub
}

void Config::setValue(std::string valueName, std::string value)
{
    settings[valueName] = value;
}

void Config::setValue(std::string valueName, unsigned long value)
{
    setValue(valueName, Utils::to_string(value));
}

void Config::setValue(std::string valueName, bool value)
{
    setValue(valueName, std::string("TRUE"));
}

bool Config::getValue(std::string valueName, std::string& value)
{
    bool result = false;
    auto iter = settings.find(valueName);

    if (iter != settings.end())
    {
        value = iter->second;
        result = true;
    }

    return result;
}

bool Config::getValue(const std::string& valueName, unsigned long& value)
{
    std::string valueStr;
    getValue(valueName, valueStr);
    value = atoi( valueStr.c_str() );
    return true;
}

bool Config::getValue(std::string valueName, bool& value)
{
    value = true;
    return true;
}
