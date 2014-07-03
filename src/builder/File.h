/*******************************************************************
 * File.h
 *
 *  @date: 5 черв. 2014
 *  @author: DB
 ******************************************************************/

#ifndef FILE_H_
#define FILE_H_

#include <string>

class File
{
    public:
        File();
        virtual ~File();

        int size;
        std::string permissions;
        std::string name;
        std::string relativeFilePath;
        bool isDir;
};

#endif /* FILE_H_ */
