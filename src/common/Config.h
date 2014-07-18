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

        bool isValid();

        static void setValue(std::string valueName, std::string value);
        static void setValue(std::string valueName, unsigned long value);
        static void setValue(std::string valueName, bool value);

        static bool getValue(std::string valueName, std::string& value);
        static bool getValue(const std::string& valueName, unsigned long& value);
        static bool getValue(std::string valueName, bool& value);

        static const std::string CONFIG_MAX_THREAD_NUMBER;
        static const std::string CONFIG_PORT;
        static const std::string CONFIG_WORKING_DIR;
        static const std::string CONFIG_ROOT_DIR;

    private:
         static std::map<std::string, std::string> settings;
};

#endif /* CONFIG_H_ */
