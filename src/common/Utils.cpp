/*******************************************************************
 * Utils.cpp
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/


#include <string>
#include <algorithm>
#include <cctype>
#include <functional>
#include <exception>
#include <sstream>
#include <fstream>
#include <memory>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "common/Utils.h"
#include "common/traceout.h"
#include "common/File.h"
#include "common/Config.h"

#include "boost/lexical_cast.hpp"

//---------------------------------------------------------------------------------------
const std::string Utils::getCurrentDateTime()
//---------------------------------------------------------------------------------------
{
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

//---------------------------------------------------------------------------------------
void Utils::split(std::vector<std::string> &tokens, const std::string &text, const std::string & delim)
//---------------------------------------------------------------------------------------
{
    size_t start = 0, end = 0;
    while ((end = text.find(delim, start)) != std::string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = end + delim.length();
    }
    tokens.push_back(text.substr(start));
}

//---------------------------------------------------------------------------------------
void Utils::readDir(const std::string& root, const std::string& requestPath, std::vector<File>& fileList)
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "root='%s', relativePath='%s', fileList.size()=%zu", root.c_str(), requestPath.c_str(), fileList.size());

    readDir(root+requestPath, fileList);

    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
void Utils::readDir(const std::string& requestPath, std::vector<File>& fileList)
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "relativePath='%s', fileList.size()=%zu", requestPath.c_str(), fileList.size());

    DIR *mydirhandle;

    struct dirent *mydirent;

    std::string errMsg = std::string("Failed to read dir '") + requestPath + "': ";

    if ((mydirhandle = opendir(requestPath.c_str())) == NULL)
    {
        throw(std::ios_base::failure(errMsg + strerror(errno)));
    }

    else
    {
        while ((mydirent = readdir(mydirhandle)) != NULL)
        {
            if ((strcmp(mydirent->d_name, ".") == 0) /*|| (strcmp(mydirent->d_name, "..") == 0)*/)
            {
                continue;
            }

            else
            {
                File file(requestPath + mydirent->d_name);

                std::string rootDir = Config::getValueStr(Config::ROOT_DIR);
                std::string requestPathWithoutBase = requestPath;
                requestPathWithoutBase = requestPathWithoutBase.replace(requestPath.find(rootDir), rootDir.length(), "");

                file.mReferenceFilePath = requestPathWithoutBase + mydirent->d_name;
                file.setDir(mydirent->d_type == DT_DIR);
                file.setName(mydirent->d_name);

                fileList.push_back(file);
            }
        }

        closedir(mydirhandle);
    }

    //   std::ifstream t("file.txt");
    //   std::stringstream buffer;
    //   buffer << t.rdbuf();

    TRC_DEBUG_FUNC_EXIT(0U);
}

//---------------------------------------------------------------------------------------
std::string Utils::getTextFileContent(const char *filename)
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0, "filename='%s'", filename);

    std::string contents;

    std::ifstream in(filename, std::ios::in | std::ios::binary);

    if (!in)
    {
        throw(std::ios_base::failure(std::string("Reading file '") + filename + "' failed: " + strerror(errno)));
    }

    else
    {
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
    }

    TRC_DEBUG_FUNC_EXIT(0);

    return contents;
}

//---------------------------------------------------------------------------------------
bool Utils::readAndCheckIfItIsBinary(const char *filename, std::string& content)
{
    bool bBinary = false;

    static const char binaryArray[] =
    {
        0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xB,
        0xC, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
        0x16, 0x17, 0x18, 0x19, 0x7F, 0x0
    };

    std::ifstream in(filename, std::ios::in | std::ios::binary);

    if (!in)
    {
        throw(std::ios_base::failure(std::string("Failed to read the file '") + filename + "': " + strerror(errno)));
    }

    else
    {
        const int BUFF_SIZE = 2048;
        char buffer[BUFF_SIZE+1] = { 0 };

        std::ifstream::pos_type fileSize;
        in.seekg(0, std::ios::end);
        fileSize = in.tellg();
        int readBytes = 0;
        int bytesToRead = std::min(BUFF_SIZE, static_cast<int>(fileSize));

        while (bytesToRead > 0 && !bBinary)
        {
            in.seekg(readBytes, std::ios::beg);
            if (!in.read(&buffer[0], bytesToRead))
            {
                TRC_ERROR(0U, "Failed to read the file '%s': %s", filename, strerror(errno));
                throw(std::ios_base::failure(std::string("Failed to read the file '") + filename + "': " + strerror(errno)));
            }


            //TODO: replace with std::find();

            int cntr = 0;
            while (cntr < bytesToRead)
            {
                if (strchr(binaryArray, buffer[cntr]))
                {
                    bBinary = true;
                    break;
                }
                cntr++;
            }

            buffer[bytesToRead] = '\0';
            content += buffer;
            readBytes += bytesToRead;
            bytesToRead = std::min(BUFF_SIZE, static_cast<int>(fileSize) - readBytes);
        }

        in.close();
    }

    return bBinary;
}

//---------------------------------------------------------------------------------------
std::string Utils::formatString(const std::string fmt_str, ...)
//---------------------------------------------------------------------------------------
{
    int final_n, n = ((int) fmt_str.size()) * 2; /* reserve 2 times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while (1)
    {
        formatted.reset(new char[n]); /* wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
        {
            n += abs(final_n - n + 1);
        }
        else
        {
            break;
        }
    }
    return std::string(formatted.get());
}

//---------------------------------------------------------------------------------------
bool Utils::endsWith(const std::string &str, const std::string &suffix)
//---------------------------------------------------------------------------------------
{
    return ( str.size() >= suffix.size() &&
             str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0 );
}

//---------------------------------------------------------------------------------------
bool Utils::startsWith(const std::string &str, const std::string &prefix)
//---------------------------------------------------------------------------------------
{
    return ( str.size() >= prefix.size() &&
             str.compare(0, prefix.size(), prefix) == 0 );
}

//---------------------------------------------------------------------------------------
void Utils::replaceAll(std::string &s, const std::string & search, const std::string & replace)
//---------------------------------------------------------------------------------------
{
    for (size_t pos = 0;; pos += replace.length())
    {
        // Locate the substring to replace
        pos = s.find(search, pos);
        if (pos == std::string::npos)
        {
            break;
        }
        // Replace by erasing and inserting
        s.erase(pos, search.length());
        s.insert(pos, replace);
    }
}

//---------------------------------------------------------------------------------------
std::string Utils::to_string(unsigned long int_value)
//---------------------------------------------------------------------------------------
{
//    char buffer[16];
//    sprintf(buffer, "%lu", int_value);
//    return buffer;

    return boost::lexical_cast<std::string>(int_value);
}

//---------------------------------------------------------------------------------------
unsigned long Utils::to_int(std::string str_value)
//---------------------------------------------------------------------------------------
{
    return ::atoi(str_value.c_str());
}

//---------------------------------------------------------------------------------------
std::string Utils::join(const std::vector<std::string>& list, const std::string& delim)
//---------------------------------------------------------------------------------------
{
    std::stringstream result;

    std::for_each( list.begin(),
                   list.end()-1,
                   [&](const std::string& entry){result << entry << delim;});

    result << list.back(); //no trailing delimiter

    return result.str();
}


//---------------------------------------------------------------------------------------
std::string Utils::join(  const std::map<std::string, std::string>& map,
                          const std::string& delim1,
                          const std::string& delim2,
                          const std::function<bool(const std::pair<std::string, std::string>&)>& predicate)
//---------------------------------------------------------------------------------------
{
    std::stringstream result;

    std::for_each( map.begin(),
                   map.end(),
                   [&](const std::pair<std::string, std::string>& entry)
    {
        if(predicate(entry))
        {
            result << entry.first << delim1 << entry.second << delim2;
        }
    }
    );

    return result.str();
}

//---------------------------------------------------------------------------------------
std::string Utils::join(  const std::map<std::string, std::string>& map,
                          const std::string& delim1,
                          const std::string& delim2)
//---------------------------------------------------------------------------------------
{
    return Utils::join( map, delim1, delim2, [&](const std::pair<std::string, std::string>& entry)
    {
        return true;
    });
}

//---------------------------------------------------------------------------------------
std::vector<std::string> Utils::getFileContent(std::string URL)
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "URL='%s'", URL.c_str());

    std::string fileContent;
    std::vector<std::string> entries;

    if (Utils::readAndCheckIfItIsBinary(URL.c_str(), fileContent))
    {
        entries.push_back("(binary content)");
    }

    else
    {
        Utils::split(entries, fileContent, "\r\n");
    }

    TRC_DEBUG_FUNC_EXIT(0U);

    return entries;
}

//---------------------------------------------------------------------------------------
std::vector<File> Utils::getDirContent(std::string URL)
//---------------------------------------------------------------------------------------
{
    TRC_DEBUG_FUNC_ENTER(0U, "URL='%s'", URL.c_str());

    std::vector<File> flist;

    Utils::readDir(URL, flist);

    std::sort(flist.begin(), flist.end());

    TRC_DEBUG_FUNC_EXIT(0U);

    return flist;
}

