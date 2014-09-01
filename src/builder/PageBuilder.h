/*******************************************************************
 * PageBuilder.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef PAGEBUILDER_H_
#define PAGEBUILDER_H_

#include <string>
#include "builder/HTMLDecorator.h"
#include "common/Config.h"

//---------------------------------------------------------------------------------------
// Page builder
//---------------------------------------------------------------------------------------
class PageBuilder
{
   public:
      PageBuilder();
      virtual ~PageBuilder();

      template<typename T>
      std::string build(   const std::vector<T>& content,
                           HTMLDecorator<T> decorator);
};

//---------------------------------------------------------------------------------------
template<typename T>
std::string PageBuilder::build(  const std::vector<T>& content,
                                 HTMLDecorator<T> decorator)
//---------------------------------------------------------------------------------------
{
   std::string body;
   for(T line : content)
   {
      std::string decoratedLine = decorator.decorateLine(line);
      body += (decoratedLine + "\n");
   }

   std::string title = Config::getValueStr(Config::PAGE_TITLE);
   std::string decoratedHeader  = decorator.decorateHeader(title);
   std::string decoratedBody    = decorator.decorateBody  (body);
   std::string decoratedFooter  = decorator.decorateFooter(Utils::getCurrentDateTime());

   std::string result = decorator.decoratePage( decoratedHeader,
                                                decoratedBody,
                                                decoratedFooter);

   return (result);
}

#endif /* PAGEBUILDER_H_ */
