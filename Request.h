/* 
 * File:   Request.h
 * Author: heven
 *
 * Created on 26 Декабрь 2012 г., 22:53
 */

#ifndef REQUEST_H
#define	REQUEST_H

#include<string>
#include "global_const.h"
#include <glog/logging.h>

class Request {
    std::string m_sMessage;
    int m_nId;
public:
    Request();
//    Request(const Request& orig);
    virtual ~Request();
    int getID() const{return m_nId;};
    void setID(int id){m_nId = id;};
    inline const std::string & getMessage(){return m_sMessage;};
    void setMessage(const std::string & s){m_sMessage = s;};
private:
};

#endif	/* REQUEST_H */

