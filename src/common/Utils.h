/*******************************************************************
 * Utils.h
 *
 *  @date: 28 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "common/File.h"

class Utils
{
    public:
        static const std::string getCurrentDateTime();
        static void split(std::vector<std::string> &tokens, const std::string &text, const std::string & delim);
        static void readDir(const std::string& root, const std::string& relativePath, std::vector<File>& fileList);
        static std::string getTextFileContent(const char *filename);
        static bool readAndCheckIfItIsBinary(const char *filename, std::string& content);
        static bool endsWith(const std::string &str, const std::string &suffix);
        static bool startsWith(const std::string &str, const std::string &prefix);
        static void replaceAll(std::string &s, const std::string & search, const std::string & replace);
        static std::string to_string(unsigned long int_value);
        static unsigned long to_int(std::string str_value);
        static std::string formatString(const std::string fmt_str, ...);
        static void readDir(const std::string& requestPath, std::vector<File>& fileList);

    private:
        // TODO: utility class, useful functions container. Replace with namespace?
        Utils();
        virtual ~Utils();
};

#endif /* UTILS_H_ */
