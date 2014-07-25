/*******************************************************************
 * PageBuilder.h
 *
 *  @date: 4-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef PAGEBUILDER_H_
#define PAGEBUILDER_H_

#include <string>
#include <map>
#include "common/File.h"

class PageBuilder
{
    public:
        PageBuilder();
        ~PageBuilder();

        std::string buildRootLayout       (const std::string& path);

    private:
        std::string buildPageTable        (const std::string& dirPath);
        std::string buildPageTableLine    (const File& file);
        std::string buildFileContent      (const std::string& filePath);
        std::string buildFileContentLine  (const std::string& contentLine, int idx);
};

#endif /* PAGEBUILDER_H_ */
