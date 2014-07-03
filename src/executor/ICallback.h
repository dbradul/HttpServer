/*******************************************************************
 * ICallback.h
 *
 *  @date: 30 квіт. 2014
 *  @author: DB
 ******************************************************************/

#ifndef ICALLBACK_H_
#define ICALLBACK_H_

#include <functional>
#include <string>

typedef std::function<void(const std::string&)> tCallback;

#endif /* ICALLBACK_H_ */
