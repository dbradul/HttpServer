/*******************************************************************
 * Utils.cpp
 *
 *  @date: 28 ���. 2014
 *  @author: DB
 ******************************************************************/

#include "Utils.h"

#include <string>
#include <algorithm>
#include <cctype>
#include <functional>

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <regex>
#include <fstream>
#include "bits/unique_ptr.h"
#include "common/traceout.h"
#include <exception>
#include "builder/File.h"

using namespace std;

//---------------------------------------------------------------------------------------
Utils::Utils()
//---------------------------------------------------------------------------------------
{}

//---------------------------------------------------------------------------------------
Utils::~Utils()
//---------------------------------------------------------------------------------------
{}

//---------------------------------------------------------------------------------------
const std::string Utils::getCurrentDateTime()
//---------------------------------------------------------------------------------------
{
   // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
   time_t now = time(0);
   struct tm tstruct;
   char buf[80];
   tstruct = *localtime(&now);
   // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
   // for more information about date/time format
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
Url::Url(const string& url_s)
//---------------------------------------------------------------------------------------
{
   parse(url_s);
}

//---------------------------------------------------------------------------------------
void Url::parse(const string& url)
//---------------------------------------------------------------------------------------
{
//    const std::string prot_end("://");
//    std::string::const_iterator protIdx = std::search(url.begin(), url.end(), prot_end.begin(), prot_end.end());
//    mProtocol.reserve(distance(url.begin(), protIdx));
//    if (protIdx != url.end())
//    {
//        std::transform(url.begin(), protIdx, std::back_inserter(mProtocol), std::ptr_fun<int, int>(tolower)); // protocol is icase
//        std::advance(protIdx, prot_end.length());
//    }
//    else
//    {
//        protIdx = url.begin();
//    }
//
//    std::string::const_iterator path_i = std::find(protIdx, url.end(), '/');
//    mHost.reserve(distance(protIdx, path_i));
//    std::transform(protIdx, path_i, std::back_inserter(mHost), std::ptr_fun<int, int>(tolower)); // host is icase
//    std::string::const_iterator query_i = find(path_i, url.end(), '?');
//    mPath.assign(path_i, query_i);
//    if (query_i != url.end())
//    {
//        ++query_i;
//    }
//    mQuery.assign(query_i, url.end());
}

const std::string& Url::getProtocol() const
{
   return mProtocol;
}

const std::string& Url::getHost() const
{
   return mHost;
}

const std::string& Url::getPath() const
{
   return mPath;
}

const std::string& Url::getQuery() const
{
   return mQuery;
}

//---------------------------------------------------------------------------------------
// TODO: error handling
bool Utils::readDir(const std::string& root, const std::string& relativePath, std::vector<File>& fileList)
{
   TRC_DEBUG_FUNC_ENTER(0U, "root='%s', relativePath='%s', fileList.size()=%d", root.c_str(), relativePath.c_str(), fileList.size());

   DIR *mydirhandle;
   bool bResult = true;

   struct dirent *mydirent;

   if (root.c_str() == NULL)
   {
      bResult = false;
   }

   else if ((mydirhandle = opendir((root + relativePath).c_str())) == NULL)
   {
      perror("opendir");
      bResult = false;
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
            struct stat statInfo;
            std::string fullPath = root + relativePath + mydirent->d_name;

            if (stat(fullPath.c_str(), &statInfo) == -1)
            {
               perror("stat");
               bResult = false;
            }

            char perms[1 + 3 + 3 + 3];
            sprintf(perms, "%c%c%c%c%c%c%c%c%c%c",

            S_ISDIR(statInfo.st_mode) ? 'd' : '-',

            statInfo.st_mode && S_IRUSR ? 'r' : '-', statInfo.st_mode && S_IWUSR ? 'w' : '-',
                  statInfo.st_mode && S_IXUSR ? 'x' : '-',

                  statInfo.st_mode && S_IRGRP ? 'r' : '-', statInfo.st_mode && S_IWGRP ? 'w' : '-',
                  statInfo.st_mode && S_IXGRP ? 'x' : '-',

                  statInfo.st_mode && S_IROTH ? 'r' : '-', statInfo.st_mode && S_IWOTH ? 'w' : '-',
                  statInfo.st_mode && S_IXOTH ? 'x' : '-');

            File file;
            file.size = statInfo.st_size;
            file.isDir = (mydirent->d_type == DT_DIR);
            file.name = mydirent->d_name;
            file.relativeFilePath = relativePath + mydirent->d_name;
            file.permissions = perms;

            fileList.push_back(file);
         }
      }

      closedir(mydirhandle);
   }

//   std::ifstream t("file.txt");
//   std::stringstream buffer;
//   buffer << t.rdbuf();

   TRC_DEBUG_FUNC_EXIT(0U);

   return bResult;
}

//---------------------------------------------------------------------------------------
std::string Utils::getTextFileContent(const char *filename)
{
   TRC_DEBUG_FUNC_ENTER(0, "filename='%s'", filename);

   std::string contents;
//   char workingDir[FILENAME_MAX];
//   TRC_INFO(0, "working dir='%s'", std::string(getcwd(workingDir, sizeof(workingDir))).c_str());

   std::ifstream in(filename, std::ios::in | std::ios::binary);

   if (!in)
   {
      throw(ios_base::failure(std::string("Read '") + filename + "': " + strerror(errno)));
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
   std::ifstream in(filename, std::ios::in | std::ios::binary);

   const char binaryArray[] =
   { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xB, 0xC, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
         0x18, 0x19, 0x16, 0x16, 0x7F, 0x0 };

   bool bBinary = false;

   const int BUFF_SIZE = 2048;
   char buffer[BUFF_SIZE+1] = { 0 };

   if (in)
   {
      ifstream::pos_type fileSize;
      in.seekg(0, std::ios::end);
      fileSize = in.tellg();
      int readBytes = 0;
      int bytesToRead = std::min(BUFF_SIZE, static_cast<int>(fileSize));

      while (bytesToRead > 0 && !bBinary)
      {
         in.seekg(readBytes, ios::beg);
         if (!in.read(&buffer[0], bytesToRead))
         {
            TRC_ERROR(0U, "Failed to read the file: %s", filename);
            throw std::exception();
         }

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
bool Utils::endsWith(const std::string &str, const std::string &suffix)
{
   return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

//---------------------------------------------------------------------------------------
void Utils::replaceAll(std::string &s, const std::string & search, const std::string & replace)
{
   for (size_t pos = 0;; pos += replace.length())
   {
      // Locate the substring to replace
      pos = s.find(search, pos);
      if (pos == string::npos)
         break;
      // Replace by erasing and inserting
      s.erase(pos, search.length());
      s.insert(pos, replace);
   }
}

//---------------------------------------------------------------------------------------
std::string Utils::to_string(unsigned long int_value)
{
   char buffer[16];
   sprintf(buffer, "%lu", int_value);
   return buffer;
}

//---------------------------------------------------------------------------------------
unsigned long Utils::atoi(std::string str_value)
{
   return ::atoi(str_value.c_str());
}
