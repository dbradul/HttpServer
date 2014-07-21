/*******************************************************************
 * File.h
 *
 *  @date: 5-7-2014
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

      bool exists();

      //<,>,<=,=>
      inline bool operator<(const File& rhs) const
      {
         return ((mIsDir == rhs.mIsDir) ? mName < rhs.mName : mIsDir && !rhs.mIsDir);
      }
      inline bool operator>(const File& rhs) const{ return (rhs < *this); }
      inline bool operator<=(const File& rhs) const{ return !(rhs < *this); }
      inline bool operator>=(const File& rhs) const{ return !(*this < rhs); }

      //==, !=
      inline bool operator==(const File& rhs) const
      {
         return ((mIsDir == rhs.mIsDir) && (mName == rhs.mName));
      }
      inline bool operator!=(const File& rhs) const{ return !(*this == rhs); }
};

#endif /* FILE_H_ */
