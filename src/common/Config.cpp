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
#include <builder/File.h>//TODO: move to common
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
bool checkEnv()
//---------------------------------------------------------------------------------------
{
   bool bResult = true;

   bResult &= File(Templater::TEMPLATE_ROOT_LAYOUT)        .exists();
   bResult &= File(Templater::TEMPLATE_PAGE_TABLE)         .exists();
   bResult &= File(Templater::TEMPLATE_PAGE_TABLE_LINE)    .exists();
   bResult &= File(Templater::TEMPLATE_FILE_CONTENT)       .exists();
   bResult &= File(Templater::TEMPLATE_FILE_CONTENT_LINE)  .exists();

   return bResult;
}

//---------------------------------------------------------------------------------------
bool Configuration::isValid()
//---------------------------------------------------------------------------------------
{
   return checkEnv();
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
void Configuration::setValue(std::string valueName, bool value)
//---------------------------------------------------------------------------------------
{
   setValue(valueName, std::string("TRUE"));
}

//TODO: ->getValueStr
//---------------------------------------------------------------------------------------
bool Configuration::getValue(std::string valueName, std::string& value)
//---------------------------------------------------------------------------------------
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

//TODO: ->getValueInt
//---------------------------------------------------------------------------------------
bool Configuration::getValue(const std::string& valueName, unsigned long& value)
//---------------------------------------------------------------------------------------
{
   std::string valueStr;
   getValue(valueName, valueStr);
   value = atoi(valueStr.c_str());
   return true;
}

//---------------------------------------------------------------------------------------
bool Configuration::getValue(std::string valueName, bool& value)
//---------------------------------------------------------------------------------------
{
   value = true;
   return true;
}
