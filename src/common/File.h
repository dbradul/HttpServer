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
      explicit File(const std::string& filePath);
      ~File();

      std::string mReferenceFilePath;
      std::string mFilePath;

      bool exists();
      std::string getPermissions() const;
      const std::string& getName() const;
      std::string getReference() const;
      unsigned long getSize() const;
      bool isDir() const;
      void setDir(bool isDir);
      void setName(const std::string& name);

      // define comparison operator to put dirs ahead of files
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

   private:

      void loadFileMetadata() const;

      std::string mName;
      mutable bool mIsDir;
      mutable int mSize;
      mutable std::string mPermissions;
};

#endif /* FILE_H_ */
