/* 
 * File:   CMainQueueHandler.cpp
 * Author: heven
 * 
 * Created on 25 Декабрь 2012 г., 23:22
 */


#include "CMainQueueHandler.h"
#include "CStateController.h"
#include "Request.h"
#include "CMsgQueue.h"

CMainQueueHandler::CMainQueueHandler(const int _id,const long & _taskProcessingTime) {
    m_id = _id;
    m_taskProcessingTime = _taskProcessingTime;
    VLOG(0) << "CMainQueueHandler with ID=" << m_id;
}

CMainQueueHandler::~CMainQueueHandler() {
    Stop();
}


void CMainQueueHandler::Start(){
   CStateController & StateController = CStateController::Instance();
   StateController.SetQueueHandlerThreadState(m_id, e_WORKING_TASK);
   m_thread =  boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&CMainQueueHandler::HandlingCycle, boost::ref(*this))));
    VLOG(0) << ":Handler Started With Id="<< getID();

}

void CMainQueueHandler::Stop(){
    VLOG(0) << ":Handler Stopping with Id="<< getID();
    if(m_thread.get() != NULL){
        m_thread->interrupt();
        m_thread->join();
    }
    CStateController & StateController = CStateController::Instance();
    StateController.SetQueueHandlerThreadState(m_id, e_TERMINATED_TASK);
//    delete m_thread.get();
//    m_thread.reset();
}

void CMainQueueHandler::ProcessRequest(Request* request, Stopper stopSignal) __NO_THROW{
    usleep(m_taskProcessingTime);
}

void CMainQueueHandler::HandlingCycle(){
    CStateController & StateController = CStateController::Instance();
    Stopper stopSignal;
    
    do{

#ifdef __NO_THROW
        try{
#endif //__NO_THROW
            StateController.GetStopFlagForHandler(m_id, stopSignal);
            if(stopSignal.getState() == e_NO_NEED_STOP){
                CMsgQueue * pQueue = CMsgQueue::Instance;
                Request * pRequest = pQueue->Pop();// sleeping here
                if(pRequest != NULL){
                    boost::shared_ptr<Request> RequestPtr(pRequest);// for message deleting
                    VLOG(1) <<"[" << getID() <<"]:HandlingCycle. Process new message Id=" << pRequest->getID();
                    ProcessRequest(pRequest, stopSignal);
                }else{
                    stopSignal.setState(e_STOP_NOW);
                }
            }
#ifdef __NO_THROW
        }catch(...){
            stopSignal.setState(e_STOP_NOW);
        }
#endif //__NO_THROW
        if( stopSignal.getState() == e_NO_NEED_STOP){
            //just for testing time
            sleep(1);
        }
    }while(stopSignal.getState() == e_NO_NEED_STOP);
    int id = getID();
    VLOG(1) <<"[" << id <<"]:HandlingCycle. Break cycle. Finish thread.";
}
