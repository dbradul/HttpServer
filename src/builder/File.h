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
        File(const std::string& name);
        ~File();

        int size;
        std::string mPermissions;
        std::string mName;
        std::string mRelativeFilePath;
        bool mIsDir;

        ///friend bool operator< (const File& a, const File& b);
        bool operator< (const File& rhs) const
        {
           return ( (mIsDir == rhs.mIsDir) ?
                    mName < rhs.mName :
                    mIsDir && !rhs.mIsDir );
        }

        bool exists();

};

#endif /* FILE_H_ */
