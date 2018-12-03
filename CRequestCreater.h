/* 
 * File:   CRequestCreater.h
 * Author: heven
 *
 * Created on 26 Декабрь 2012 г., 0:21
 */

#ifndef CREQUESTCREATER_H
#define	CREQUESTCREATER_H
#include "global_const.h"
#include "Request.h"
#include "Stopper.h"
#include <boost/thread/thread.hpp>
#include <glog/logging.h>


class CRequestCreater {
    boost::shared_ptr<boost::thread> m_thread;// Preiodically create Request messages here and push it in thread
    int messageCounter;
    long m_lMSDealay;
public:
    CRequestCreater(const long & mc_delay);
    virtual ~CRequestCreater();
    Request* GetRequest(Stopper stopSignal) __NO_THROW;

    void Start();
    void Stop();
private:
    void _RequestsCreatingCycle();
};

#endif	/* CREQUESTCREATER_H */

