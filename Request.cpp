/* 
 * File:   Request.cpp
 * Author: heven
 * 
 * Created on 26 Декабрь 2012 г., 22:53
 */

#include "Request.h"


Request::Request() {
}

//Request::Request(const Request& orig) {
//}

Request::~Request() {
   VLOG(1) <<"~Request() Id="<< getID();
}

