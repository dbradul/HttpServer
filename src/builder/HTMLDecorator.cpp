/*******************************************************************
 * HTMLDecorator.cpp
 *
 *  @date: 14-8-2014
 *  @author: DB
 ******************************************************************/

#include "builder/HTMLDecorator.h"

template<>
std::string HTMLDecorator<std::string>::decorateLine(std::string line) const
{
    TRC_DEBUG_FUNC_ENTER(0U, "line='%s'", line.c_str());

    escapeSpecialEntities(line);

    Templater templater(Templater::PATH_STR_CONTENT_LINE);

    templater.setMacro(Templater::MACROS_CONTENT, line);

    TRC_DEBUG_FUNC_EXIT(0U);

    return templater.generate();
}

template<>
std::string HTMLDecorator<File>::decorateLine(File file) const
{
    TRC_DEBUG_FUNC_ENTER(0U, "line='%s'", file.getName().c_str());

    Templater templater(Templater::PATH_DIR_CONTENT_LINE);

    templater.setMacro(Templater::MACROS_FILENAME,  file.getName());
    templater.setMacro(Templater::MACROS_FILEPATH,  file.getReference());
    templater.setMacro(Templater::MACROS_SIZE,      std::to_string(file.getSize()));
    templater.setMacro(Templater::MACROS_PERMS,     file.getPermissions());

    TRC_DEBUG_FUNC_EXIT(0U);

    return templater.generate();
}

template<>
std::string HTMLDecorator<File>::decorateBody(const std::string& body) const
{
    TRC_DEBUG_FUNC_ENTER(0U, "body='%s'", body.c_str());

    Templater templater(Templater::PATH_DIR_CONTENT);

    templater.setMacro(Templater::MACROS_CONTENT, body);

    TRC_DEBUG_FUNC_EXIT(0U);

    return templater.generate();
}

template<>
std::string HTMLDecorator<std::string>::decorateBody(const std::string& body) const
{
    TRC_DEBUG_FUNC_ENTER(0U, "body='%s'", body.c_str());

    Templater templater = Templater(Templater::PATH_STR_CONTENT);

    templater.setMacro(Templater::MACROS_CONTENT, body);

    TRC_DEBUG_FUNC_EXIT(0U);

    return templater.generate();
}
