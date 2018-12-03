/* 
 * File:   CStateController.h
 * Author: heven
 *
 * Created on 26 Декабрь 2012 г., 0:44
 */

#ifndef CSTATECONTROLLER_H
#define	CSTATECONTROLLER_H
#include <cstddef>
#include <map>
#include "Stopper.h"
#include "CMsgQueue.h"

//forward
class CMainQueueHandler;
class Stopper;

enum task_state{
    e_NOT_STARTED_TASK = 0,
    e_INIITIALIZING_TASK,
    e_WORKING_TASK,
    e_FINISHING_TASK,
    e_TERMINATED_TASK
};


class CStateController {
     static CStateController * m_pStateController;
     static int m_nLastThreadId;
     static task_state m_eQueueState;
     static task_state m_eThreadState;//Main Thread
     std::map<int, task_state> m_HandlersThreads;
//     CMsgQueue m_MsgQueue;
     CStateController();
public:
    virtual ~CStateController();

    static CStateController &  Instance();
    bool IsTaskFullFinished();//all threads have terminated state
    static void Terminate();
    //void initialize();
    
    //inline CMsgQueue & getQueue(){return m_MsgQueue;};
    void GetStopFlagForHandler(const int _handlerId, Stopper &  _stopper) const;
    void GetStopFlagForMessageCreater(Stopper &  _stopper) const;
    CMainQueueHandler * CreateNewMainQueueHandler(const long & _taskProcessingTime);
    void SetQueueHandlerThreadState(const int _id, const task_state _state);

    static task_state GetMainThreadState() {return m_eThreadState;};
    static void SetMainThreadState(const task_state _state){ m_eThreadState = _state;};
    static void SetQueueState(const task_state _state){ m_eQueueState = _state;};
    static task_state GetQueueState(){return m_eQueueState;};
};
#endif	/* CSTATECONTROLLER_H */

