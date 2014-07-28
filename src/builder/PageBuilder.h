/*******************************************************************
 * PageBuilder2.h
 *
 *  @date: 28-7-2014
 *  @author: DB
 ******************************************************************/

#ifndef PAGEBUILDER2_H_
#define PAGEBUILDER2_H_

#include <string>

class PageBuilder
{
   public:
      PageBuilder();
      virtual ~PageBuilder();

      std::string build(std::string URL);
};

#endif /* PAGEBUILDER2_H_ */
