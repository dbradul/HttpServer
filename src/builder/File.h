/*******************************************************************
 * File.h
 *
 *  @date: 5 ����. 2014
 *  @author: DB
 ******************************************************************/

#ifndef FILE_H_
#define FILE_H_

#include <string>

class File
{
    public:
        File();
        ~File();

        int size;
        std::string permissions;
        std::string name;
        std::string relativeFilePath;
        bool isDir;

        ///friend bool operator< (const File& a, const File& b);
        bool operator< (const File& rhs) const
        {
           return ( (isDir == rhs.isDir) ?
                    name < rhs.name :
                    isDir && !rhs.isDir );
        }
};

#endif /* FILE_H_ */
