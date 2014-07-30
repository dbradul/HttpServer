/*******************************************************************
 * PageBuilder.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef PAGEBUILDER_H_
#define PAGEBUILDER_H_

#include <string>

class PageBuilder
{
   public:
      PageBuilder();
      virtual ~PageBuilder();

      std::string build(const std::string& URL);
};

#endif /* PAGEBUILDER_H_ */
