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
#include "builder/File.h"

class Utils
{
    public:
        static const std::string getCurrentDateTime();
        static void split(std::vector<std::string> &tokens, const std::string &text, const std::string & delim);
        static bool readDir(const std::string& root, const std::string& relativePath, std::vector<File>& fileList);
        static std::string getTextFileContent(const char *filename);
        static bool readAndCheckIfItIsBinary(const char *filename, std::string& content);
        static bool endsWith(const std::string &str, const std::string &suffix);
        static void replaceAll(std::string &s, const std::string & search, const std::string & replace);
        static std::string to_string(unsigned long int_value);
        static unsigned long atoi(std::string str_value);

    private:
        // TODO: utility class, useful functions container. Replace with namespace?
        Utils();
        virtual ~Utils();
};


class Url
{
    public:
        Url(const std::string& url);
        void parse(const std::string& url);

        const std::string& getProtocol() const;
        const std::string& getHost() const;
        const std::string& getPath() const;
        const std::string& getQuery() const;

    private:
        std::string mProtocol;
        std::string mHost;
        std::string mPath;
        std::string mQuery;

        Url(const Url& rhs);
        Url& operator=(const Url& rhs);
};

#endif /* UTILS_H_ */
