/* 
 * File:   CMsgQueue.cpp
 * Author: heven
 * 
 * Created on 26 Декабрь 2012 г., 19:58
 */

#include "CMsgQueue.h"
#include "CStateController.h"
#include <glog/logging.h>
#include <pthread.h>
namespace google {
    typedef int int32 ;
};


CMsgQueue * CMsgQueue::Instance = NULL;
CMsgQueue::CMsgQueue(){
	// TODO Auto-generated constructor stub
        LOG(INFO) << "CMsgQueue()";
}

CMsgQueue::~CMsgQueue(){
        VLOG(2) << "~CMsgQueue(), size ["<< m_queue.size() << "]";
        int i = 0;
	while(!m_queue.empty()){
		Request * pMsg = NULL;
		pMsg = m_queue.front();
		if(pMsg == NULL){
                   LOG(INFO) << "Get(mq) = NULL msg.";
                }
		m_queue.pop();
                    if(pMsg != NULL){
                       delete pMsg;
                    }
	}
	// TODO Auto-generated destructor stub
}

void CMsgQueue::Initialize(){
    Instance = this;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);// Для проверки пока создадим такой
    pthread_mutex_init(&msg_queue_mutex ,&attr);
    pthread_mutexattr_destroy(&attr);// ch
    sem_init(&msg_queue_count_sem,0,0);
    CStateController & StateController = CStateController::Instance();
    StateController.SetQueueState(e_WORKING_TASK);
}

void CMsgQueue::Push(Request * _pMsg){
    if(_pMsg == NULL){
            LOG(WARNING) << "In mq pushed NULL msg.";
    }
    pthread_mutex_lock(&msg_queue_mutex);
    m_queue.push(_pMsg);// It's not safe, but looks like not too metter in test task
    sem_post(&msg_queue_count_sem);
    pthread_mutex_unlock(&msg_queue_mutex);
    VLOG(2) << "Push(mq) msg. mq size ["<< m_queue.size() << "]";
}

Request * CMsgQueue::Pop(){
    bool bPrintDebug = false;
    Request * pMsg = NULL;
    // Мьютекс ограничивающий общий доступ к очереди
    int nLen = 0;
    sem_getvalue(&msg_queue_count_sem, &nLen);
    if(nLen == 0){// Хоть одна очередь да подконекчена для обмена
            LOG(INFO) << "Waiting for a message...";
    }
    if(CStateController::GetQueueState() == e_WORKING_TASK){// Не выключаемся ли мы?
            sem_wait(&msg_queue_count_sem);
    }else{
            LOG(INFO) << "Some of other components is stopped.";
            return NULL;
    }
    pthread_mutex_lock(&msg_queue_mutex);
    if(m_queue.empty()){
            bPrintDebug = true;
    }else{
            pMsg = m_queue.front();
            if(pMsg == NULL){
                LOG(WARNING) <<"Get NULL msg from queue.";
            }
            m_queue.pop();
            VLOG(2) << ":Pop msg queue size ["<< m_queue.size() <<"]";
    }
    pthread_mutex_unlock(&msg_queue_mutex);
    if(bPrintDebug == true){
            VLOG(1) << "Tried to get message. There is no messages in the queue.";
    }
    return pMsg;
}

void CMsgQueue::Stop(){
    LOG(INFO) << "Message queue stopping";
    CStateController::SetQueueState(e_TERMINATED_TASK);
    pthread_mutex_destroy(&msg_queue_mutex);
    sem_destroy(&msg_queue_count_sem);
}

