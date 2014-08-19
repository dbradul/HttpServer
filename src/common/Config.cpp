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
const std::string Config::MAX_THREAD_NUMBER  = "PUTIN_HUYLO";
const std::string Config::PORT               = "SLAVA_UKRAYNI";
const std::string Config::WORKING_DIR        = "HEROYAM_SLAVA";
const std::string Config::ROOT_DIR           = "LALALALALALA";
const std::string Config::PAGE_TITLE         = "PAGE_TITLE";

//---------------------------------------------------------------------------------------
char workingDir[FILENAME_MAX]={0};
std::map<std::string, std::string> Config::settings =
{
   {MAX_THREAD_NUMBER,   "4"},
   {PORT,                "8080"},
   {WORKING_DIR,         std::string(getcwd(workingDir, sizeof(workingDir)))},
   {ROOT_DIR,            std::string(getcwd(workingDir, sizeof(workingDir)))},
   {PAGE_TITLE,          "HttpServer"},
};

Config* Config::mpInstance = NULL;

//---------------------------------------------------------------------------------------
Config::Config()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
Config::~Config()
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "");
   TRC_DEBUG_FUNC_EXIT (0U);
}

//---------------------------------------------------------------------------------------
void Config::setValue(std::string valueName, std::string value)
//---------------------------------------------------------------------------------------
{
   settings[valueName] = value;
}

//---------------------------------------------------------------------------------------
void Config::setValue(std::string valueName, unsigned long value)
//---------------------------------------------------------------------------------------
{
   setValue(valueName, Utils::to_string(value));
}

//---------------------------------------------------------------------------------------
const std::string Config::getValueStr(const std::string& valueName)
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
unsigned long Config::getValueInt(const std::string& valueName)
//---------------------------------------------------------------------------------------
{
   std::string valueStr = getValueStr(valueName);
   return Utils::to_int(valueStr.c_str());
}

////TODO: lets forget about thread-safety for awhile
////---------------------------------------------------------------------------------------
//Config& Config::getInstance()
////---------------------------------------------------------------------------------------
//{
//   if(!mpInstance)
//   {
//      mpInstance = new Config();
//   }
//
//   return *mpInstance;
//}
