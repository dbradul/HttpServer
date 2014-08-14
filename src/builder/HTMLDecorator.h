/*******************************************************************
 * DecoratorNew.h
 *
 *  @date: 14-8-2014
 *  @author: DB
 ******************************************************************/

#ifndef HTMLDECORATOR_H_
#define HTMLDECORATOR_H_

#include <string>
#include "stdio.h"
#include "common/traceout.h"
#include "common/Utils.h"
#include "common/File.h"
#include "builder/Templater.h"

//---------------------------------------------------------------------------------------
template<typename T>
class HTMLDecorator
//---------------------------------------------------------------------------------------
{
   public:
      HTMLDecorator();
      virtual ~HTMLDecorator();

      std::string decorateLine(T line);
      std::string decorateBody(const std::string& body);
      std::string decorateHeader(const std::string& header) {return "<title>HttpServer: "+ header +" </title>";}
      std::string decorateFooter(const std::string& footer) {return "<span class=\"tag\"> " + footer + " </span>";}

      std::string decoratePage(  const std::string& header,
                                 const std::string& body,
                                 const std::string& footer);

   private:
      void escapeSpecialEntities(std::string& text);
};

//---------------------------------------------------------------------------------------
template<typename T>
HTMLDecorator<T>::HTMLDecorator(){}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
template<typename T>
HTMLDecorator<T>::~HTMLDecorator(){}
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
template<typename T>
void HTMLDecorator<T>::escapeSpecialEntities(std::string& text)
//---------------------------------------------------------------------------------------
{
   Utils::replaceAll(text, "<", "&lt;");
   Utils::replaceAll(text, ">", "&gt;");
   //Utils::replaceAll(text, "&", "&amp;");
   Utils::replaceAll(text, "\"", "&quot;");
   Utils::replaceAll(text, "ˆ", "&euro;");
}

//---------------------------------------------------------------------------------------
template<typename T>
std::string HTMLDecorator<T>::decoratePage(  const std::string& header,
                                             const std::string& body,
                                             const std::string& footer)
//---------------------------------------------------------------------------------------
{
   TRC_DEBUG_FUNC_ENTER(0U, "header='%s'", header.c_str());

   Templater templater(Templater::TEMPLATE_PATH_ROOT_LAYOUT);

   templater.setMacro(Templater::TEMPLATE_MACROS_HEADER,    header);
   templater.setMacro(Templater::TEMPLATE_MACROS_CONTENT,   body);
   templater.setMacro(Templater::TEMPLATE_MACROS_FOOTER,    footer);

   std::string output = templater.generate();

   TRC_DEBUG_FUNC_EXIT (0U);

   return output;
}

#endif /* HTMLDECORATOR_H_ */
