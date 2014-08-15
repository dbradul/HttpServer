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
const std::string Configuration::MAX_THREAD_NUMBER  = "PUTIN_HUYLO";
const std::string Configuration::PORT               = "SLAVA_UKRAYNI";
const std::string Configuration::WORKING_DIR        = "HEROYAM_SLAVA";
const std::string Configuration::ROOT_DIR           = "LALALALALALA";
const std::string Configuration::PAGE_TITLE         = "PAGE_TITLE";

//---------------------------------------------------------------------------------------
char workingDir[FILENAME_MAX]={0};
std::map<std::string, std::string> Configuration::settings =
{
   {MAX_THREAD_NUMBER,   "4"},
   {PORT,                "8080"},
   {WORKING_DIR,         std::string(getcwd(workingDir, sizeof(workingDir)))},
   {ROOT_DIR,            std::string(getcwd(workingDir, sizeof(workingDir)))},
   {PAGE_TITLE,          "HttpServer"},
};

Configuration* Configuration::mpInstance = NULL;

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
const std::string Configuration::getValueStr(const std::string& valueName) const
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
unsigned long Configuration::getValueInt(const std::string& valueName) const
//---------------------------------------------------------------------------------------
{
   std::string valueStr = getValueStr(valueName);
   return Utils::to_int(valueStr.c_str());
}

//TODO: lets forget about thread-safety for awhile
//---------------------------------------------------------------------------------------
Configuration& Configuration::getInstance()
//---------------------------------------------------------------------------------------
{
   if(!mpInstance)
   {
      mpInstance = new Configuration();
   }

   return *mpInstance;
}
