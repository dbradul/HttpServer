/*******************************************************************
 * Config.h
 *
 *  @date: 5 черв. 2014
 *  @author: DB
 ******************************************************************/

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <map>

class Config
{
   public:
      ////static Config& getInstance();
      virtual ~Config();

      static void setValue(const std::string& valueName, const std::string& value);
      static void setValue(const std::string& valueName, unsigned long value);

      static const std::string getValueStr(const std::string& valueName);
      static unsigned long getValueInt(const std::string& valueName);

      static const std::string MAX_THREAD_NUMBER;
      static const std::string PORT;
      static const std::string WORKING_DIR;
      static const std::string ROOT_DIR;
      static const std::string PAGE_TITLE;

   private:
      Config();
      Config(const Config& rhs);
      static std::map<std::string, std::string> settings;
      static Config* mpInstance;
};

#endif /* CONFIG_H_ */
