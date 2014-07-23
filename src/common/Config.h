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

class Configuration
{
    public:
        virtual ~Configuration();
        Configuration();

        static void setValue(std::string valueName, std::string value);
        static void setValue(std::string valueName, unsigned long value);

        static const std::string& getValueStr(const std::string& valueName);
        static unsigned long getValueInt(const std::string& valueName);

        static const std::string CONFIG_MAX_THREAD_NUMBER;
        static const std::string CONFIG_PORT;
        static const std::string CONFIG_WORKING_DIR;
        static const std::string CONFIG_ROOT_DIR;

    private:
         static std::map<std::string, std::string> settings;
};

#endif /* CONFIG_H_ */
