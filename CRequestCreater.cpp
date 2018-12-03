/* 
 * File:   CRequestCreater.cpp
 * Author: heven
 * 
 * Created on 26 Декабрь 2012 г., 0:21
 */

#include "CRequestCreater.h"
#include "CStateController.h"

CRequestCreater::CRequestCreater(const long & _msDelay) {
    messageCounter = 0;
    m_lMSDealay = _msDelay;
}

CRequestCreater::~CRequestCreater() {
    VLOG(0) << "~CRequestCreater";
}


void CRequestCreater::Start(){
   CStateController & StateController = CStateController::Instance();
   m_thread =  boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&CRequestCreater::_RequestsCreatingCycle, boost::ref(*this))));
   VLOG(0) << "[Started] Request Creater";
}

void CRequestCreater::Stop(){
    VLOG(0) << "[Stopping] Request Creater";
    if(m_thread.get() != NULL){
        m_thread->interrupt();
        m_thread->join();
    }
}

Request* CRequestCreater::GetRequest(Stopper stopSignal) __NO_THROW{
    Request* pResult = NULL;
#ifdef __NO_THROW
    try{
#endif //__NO_THROW
        pResult = new Request();
        pResult->setID(messageCounter++);
        pResult->setMessage("message text");
#ifdef __NO_THROW
    }catch(std::bad_alloc & e){
        pResult = NULL;
    }
#endif //__NO_THROW
    return pResult;
}

void CRequestCreater::_RequestsCreatingCycle(){
    CStateController & StateController = CStateController::Instance();
    Stopper stopSignal;
    do{
#ifdef __NO_THROW
        try{
#endif //__NO_THROW
            StateController.GetStopFlagForMessageCreater(stopSignal);
            if(stopSignal.getState() == e_NO_NEED_STOP){
                CMsgQueue * pQueue = CMsgQueue::Instance;
                Request* pRequest = GetRequest(stopSignal);
                if(pRequest != NULL){
                    pQueue->Push(pRequest);
                }else{
                    stopSignal.setState(e_STOP_NOW);
                }
            }
#ifdef __NO_THROW
        }catch(...){// I Don't know what throws will be here in future.
            stopSignal.setState(e_STOP_NOW);
        }
#endif //__NO_THROW
        if( stopSignal.getState() == e_NO_NEED_STOP){
            //just for testing time
            usleep(m_lMSDealay);//Delay between messages
        }
    }while(stopSignal.getState() == e_NO_NEED_STOP);
}