/*******************************************************************
 * PageBuilder.h
 *
 *  @date: 4 черв. 2014
 *  @author: DB
 ******************************************************************/

#ifndef PAGEBUILDER_H_
#define PAGEBUILDER_H_

#include <string>
#include <map>
#include "builder/File.h"

class PageBuilder
{
    public:
        PageBuilder();
        virtual ~PageBuilder();

        std::string buildRootLayout(std::string& path);
        std::string buildPageTable(const std::string& dirPath);
        std::string buildPageTableLine(const File& file);
        std::string buildFileContent(const std::string& filePath);
        std::string buildFileContentLine(const std::string& contentLine, int idx);

};

#endif /* PAGEBUILDER_H_ */
