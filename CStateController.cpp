/* 
 * File:   CStateController.cpp
 * Author: heven
 * 
 * Created on 26 Декабрь 2012 г., 0:44
 */

#include "CStateController.h"
#include "CMainQueueHandler.h"

CStateController * CStateController::m_pStateController = NULL;
int CStateController::m_nLastThreadId = 0;
task_state CStateController::m_eQueueState = e_NOT_STARTED_TASK;
task_state CStateController::m_eThreadState = e_NOT_STARTED_TASK;

CStateController::CStateController() {
    LOG(INFO) << "CStateController()";
    m_pStateController = this;
}

CStateController::~CStateController() {
    LOG(INFO) << "~CStateController()";
}

CStateController &  CStateController::Instance(){
    if(m_pStateController == NULL){
        try{
            m_pStateController = new CStateController;
            //m_pStateController->initialize();
        }catch(std::bad_alloc & e){
            m_pStateController = NULL;
        }
    }
    return *m_pStateController;
};

//void CStateController::initialize(){
//    m_MsgQueue.Initialize();
//}

CMainQueueHandler * CStateController::CreateNewMainQueueHandler(const long & _taskProcessingTime){
    CMainQueueHandler * pResult = NULL;
    try{
        pResult = new CMainQueueHandler(m_nLastThreadId++, _taskProcessingTime);
        m_HandlersThreads[pResult->getID()] = e_NOT_STARTED_TASK;
    }catch(std::bad_alloc & e){
        pResult = NULL;
    }
    return pResult;
}

void CStateController::SetQueueHandlerThreadState(const int _id, const task_state _state){
    m_HandlersThreads[_id] = _state;
}

void CStateController::GetStopFlagForHandler(const int _handlerId, Stopper &  _stopper) const{
    _stopper.setState(e_STOP_NOW);
    std::map<int,task_state>::const_iterator iter = m_HandlersThreads.find(_handlerId);
    if(iter != m_HandlersThreads.end()){
        if((e_INIITIALIZING_TASK == m_eThreadState)||(e_WORKING_TASK == m_eThreadState)){
            _stopper.setState(e_NO_NEED_STOP);
        }else{
            //_stopper.setState(e_STOP_NOW);
        }
    }else{
        //if no this thread in threads managed list - looks like it's shouldn't work.
        //_stopper.setState(e_STOP_NOW);
    }
}

void CStateController::GetStopFlagForMessageCreater(Stopper &  _stopper) const{
        if((e_INIITIALIZING_TASK == m_eThreadState)||(e_WORKING_TASK == m_eThreadState)){
            _stopper.setState(e_NO_NEED_STOP);
        }else{
            _stopper.setState(e_STOP_NOW);
        }
}

bool CStateController::IsTaskFullFinished(){
    std::map<int,task_state>::iterator iter = m_HandlersThreads.begin();
    bool foundWorkingThread = false;
    for(; (iter != m_HandlersThreads.end())&&(!foundWorkingThread);iter++){
        if(iter->second == !e_TERMINATED_TASK){
            foundWorkingThread = true;
        }
    }
    if(m_eThreadState != e_TERMINATED_TASK){
        foundWorkingThread = true;
    }
    return !foundWorkingThread;
}

void CStateController::Terminate(){
    if(m_pStateController != NULL){
        //m_pStateController->m_MsgQueue.Stop();
        delete m_pStateController;
        VLOG(0) << "CStateController::terminate() finished";
        m_pStateController = NULL;
    }
}



