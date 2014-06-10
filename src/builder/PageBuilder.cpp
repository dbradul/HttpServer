/*******************************************************************
 * PageBuilder.cpp
 *
 *  @date: 4 черв. 2014
 *  @author: DB
 ******************************************************************/

#include "builder/PageBuilder.h"
#include "builder/Templater.h"
#include "builder/File.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/Config.h"
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>


//---------------------------------------------------------------------------------------
PageBuilder::PageBuilder()
{
    // TODO Auto-generated constructor stub
}

//---------------------------------------------------------------------------------------
PageBuilder::~PageBuilder()
{
    // TODO Auto-generated destructor stub
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildRootLayout(std::string& path)
{
    Templater templater(Templater::TEMPLATE_ROOT_LAYOUT);

    std::string content;

    try
    {
        if(Utils::endsWith(path, "/"))
        {
            content = buildPageTable(path);
        }
        else
        {
            content = buildFileContent(path);
        }
    }
    catch(const std::exception& e)
    {
        TRC_ERROR(0U, ( "Reading dir content has failed" ), NULL);
        content = "Reading content has failed for \"" + path + "\"";
    }

    templater.setMacro("root",      path);
    templater.setMacro("content",   content);
    templater.setMacro("time",      Utils::getCurrentDateTime());

    return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildPageTable(const std::string& dirPath)
{
    Templater templater(Templater::TEMPLATE_PAGE_TABLE);

    std::vector<File> flist;

    std::string workingDir;
    Config::getValue(Config::CONFIG_WORKING_DIR, workingDir);

    if (!Utils::readDir(workingDir, dirPath, flist))
    {
        templater.setMacro("table_body", "ERROR while reading the dir!<br/>");
    }
    else
    {
        std::string tableBody;

        for_each(flist.begin(), flist.end(), [&](const File& file)
        {
            tableBody += buildPageTableLine(file);
        });

        templater.setMacro("table_body", tableBody);
    }

    return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildPageTableLine(const File& file)
{
    Templater templater(Templater::TEMPLATE_PAGE_TABLE_LINE);
    templater.setMacro("filename",  file.name);
    templater.setMacro("filepath",  "\"" + file.relativeFilePath + (file.isDir?"/":"") + "\""); //TODO: sync with buildRootLayout logic
    templater.setMacro("size",      (file.size?Utils::to_string(file.size):""));
    templater.setMacro("perms",     file.permissions);

    return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildFileContent(const std::string& filePath)
{
    std::string fileContent;
    std::string output;
    Templater templater(Templater::TEMPLATE_FILE_CONTENT);

    std::string workingDir;
    Config::getValue(Config::CONFIG_WORKING_DIR, workingDir);

    if (Utils::readAndCheckIfItIsBinary((workingDir + filePath).c_str(), fileContent))
    {
        output = "(binary content)";
    }

    else
    {
        std::vector<std::string> fileLines;
        Utils::split(fileLines, fileContent, "\r\n");

        int i = 1;
        for_each(fileLines.begin(), fileLines.end(), [&](const std::string& line)
        {
            output += buildFileContentLine(line, i++);
            output += "\n";
        });
    }

    templater.setMacro("file_content", output);

    return templater.generate();
}

//---------------------------------------------------------------------------------------
std::string PageBuilder::buildFileContentLine(const std::string& contentLine, int idx)
{
    Templater templater(Templater::TEMPLATE_FILE_CONTENT_LINE);

    std::string result = contentLine;

    Utils::replaceAll(result, "<", "&lt;");
    Utils::replaceAll(result, ">", "&gt;");

    templater.setMacro("idx", Utils::to_string(idx));
    templater.setMacro("line_content", result);

    return templater.generate();
}
