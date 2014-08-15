/*******************************************************************
 * Config.h
 *
 *  @date: 5 ����. 2014
 *  @author: DB
 ******************************************************************/

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <map>

class Configuration
{
   public:
      static Configuration& getInstance();
      virtual ~Configuration();

      void setValue(std::string valueName, std::string value);
      void setValue(std::string valueName, unsigned long value);

      const std::string getValueStr(const std::string& valueName) const;
      unsigned long getValueInt(const std::string& valueName) const;

      static const std::string MAX_THREAD_NUMBER;
      static const std::string PORT;
      static const std::string WORKING_DIR;
      static const std::string ROOT_DIR;
      static const std::string PAGE_TITLE;

   private:
      Configuration();
      Configuration(const Configuration& rhs);
      static std::map<std::string, std::string> settings;
      static Configuration* mpInstance;
};

#endif /* CONFIG_H_ */
