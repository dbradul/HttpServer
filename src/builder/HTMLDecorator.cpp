/*******************************************************************
 * HTMLDecorator.cpp
 *
 *  @date: 14-8-2014
 *  @author: DB
 ******************************************************************/

#include "builder/HTMLDecorator.h"

template<>
std::string HTMLDecorator<std::string>::decorateLine(std::string line)
{
   TRC_DEBUG_FUNC_ENTER(0U, "line='%s'", line.c_str());

   escapeSpecialEntities(line);

   Templater templater(Templater::TEMPLATE_PATH_STR_CONTENT_LINE);

   templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT, line);

   std::string decoratedLine = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return decoratedLine;
}

template<>
std::string HTMLDecorator<File>::decorateLine(File file)
{
   TRC_DEBUG_FUNC_ENTER(0U, "line='%s'", file.getName().c_str());

   Templater templater(Templater::TEMPLATE_PATH_DIR_CONTENT_LINE);

   templater.setMacro(Templater::TEMPLATE_MACROS_FILENAME,  file.getName());
   templater.setMacro(Templater::TEMPLATE_MACROS_FILEPATH,  file.getReference());
   templater.setMacro(Templater::TEMPLATE_MACROS_SIZE,      Utils::to_string(file.getSize()));
   templater.setMacro(Templater::TEMPLATE_MACROS_PERMS,     file.getPermissions());

   std::string decoratedLine = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return decoratedLine;
}

template<>
std::string HTMLDecorator<File>::decorateBody(const std::string& body)
{
   TRC_DEBUG_FUNC_ENTER(0U, "body='%s'", body.c_str());

   Templater templater(Templater::TEMPLATE_PATH_DIR_CONTENT);

   templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT, body);

   std::string decoratedBody = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return decoratedBody;
}

template<>
std::string HTMLDecorator<std::string>::decorateBody(const std::string& body)
{
   TRC_DEBUG_FUNC_ENTER(0U, "body='%s'", body.c_str());

   Templater templater = Templater(Templater::TEMPLATE_PATH_STR_CONTENT);

   templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT, body);

   std::string decoratedBody = templater.generate();

   TRC_DEBUG_FUNC_EXIT(0U);

   return decoratedBody;
}


