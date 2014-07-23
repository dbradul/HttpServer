/*******************************************************************
 * Config.cpp
 *
 *  @date: 5 ����. 2014
 *  @author: DB
 ******************************************************************/

#include <common/Config.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <common/Utils.h>

#include "common/traceout.h"
#include "builder/Templater.h"

//---------------------------------------------------------------------------------------
// Protocol constants
//---------------------------------------------------------------------------------------
const std::string Configuration::CONFIG_MAX_THREAD_NUMBER  = "PUTIN_HUYLO";
const std::string Configuration::CONFIG_PORT               = "SLAVA_UKRAYNI";
const std::string Configuration::CONFIG_WORKING_DIR        = "HEROYAM_SLAVA";
const std::string Configuration::CONFIG_ROOT_DIR           = "LALALALALALA";

//---------------------------------------------------------------------------------------
char workingDir[FILENAME_MAX]={0};
std::map<std::string, std::string> Configuration::settings =
{
   {CONFIG_MAX_THREAD_NUMBER,   "4"},
   {CONFIG_PORT,                "8080"},
   {CONFIG_WORKING_DIR,         std::string(getcwd(workingDir, sizeof(workingDir)))},
   {CONFIG_ROOT_DIR,            std::string(getcwd(workingDir, sizeof(workingDir)))},
};

//---------------------------------------------------------------------------------------
Configuration::Configuration()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
Configuration::~Configuration()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
void Configuration::setValue(std::string valueName, std::string value)
//---------------------------------------------------------------------------------------
{
   settings[valueName] = value;
}

//---------------------------------------------------------------------------------------
void Configuration::setValue(std::string valueName, unsigned long value)
//---------------------------------------------------------------------------------------
{
   setValue(valueName, Utils::to_string(value));
}

//---------------------------------------------------------------------------------------
const std::string& Configuration::getValueStr(const std::string& valueName)
//---------------------------------------------------------------------------------------
{
   std::string result = "UNKNOWN";

   auto iter = settings.find(valueName);

   if (iter != settings.end())
   {
      result = iter->second;
   }

   return result;
}

//---------------------------------------------------------------------------------------
unsigned long Configuration::getValueInt(const std::string& valueName)
//---------------------------------------------------------------------------------------
{
   std::string valueStr = getValueStr(valueName);
   return Utils::to_int(valueStr.c_str());
}

