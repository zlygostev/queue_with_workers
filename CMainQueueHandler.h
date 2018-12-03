/*
 * File:   CMainQueueHandler.h
 * Author: heven
 *
 * Created on 16 Декабрь 2010 г., 12:07
 */

#ifndef CMAINQUEUEHANDLER_H
#define	CMAINQUEUEHANDLER_H

#include "global_const.h"
#include <boost/thread/thread.hpp>
#include <glog/logging.h>
#include "Request.h"
#include "Stopper.h"

class CMainQueueHandler{
    int m_id;
    long m_taskProcessingTime;
public:
    CMainQueueHandler(const int id, const long & _taskProcessingTime);
    virtual ~CMainQueueHandler();
     /** @brief Start processing of main message queue*/
    void Start();
    /** @brief Stop processing  of main queue*/
    void Stop();
    int getID(){return m_id;};

private:
    /*обрабатывает запрос, но память не удаляет, завершает обработку досрочно, если
      // объект stopSignal указывает на необходимость остановки*/
    void ProcessRequest(Request* request, Stopper stopSignal) __NO_THROW;

    void HandlingCycle();
    boost::shared_ptr<boost::thread> m_thread;
};

#endif	/* CMAINQUEUEHANDLER_H */

