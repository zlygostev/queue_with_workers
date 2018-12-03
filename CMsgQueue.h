/* 
 * File:   CMsgQueue.h
 * Author: heven
 *
 * Created on 25 Декабрь 2012 г., 19:58
 */

#ifndef CMSGQUEUE_H
#define	CMSGQUEUE_H

#include "global_const.h"
#include <queue>
#include <semaphore.h>
#include "Request.h"


//extern unsigned char nRunningTasks;

class CMsgQueue {
public:
	static CMsgQueue * Instance;/*!< @brief Указатаель на объект класса CMGQueue (на себя, если MGQueue один) */

	CMsgQueue();
	// Initialize start data
	void Initialize();
	// Put msg in queue
	void Push(Request *);
	// Get msg from queue
        //Request* GetRequest(Stopper & stopSignal) __NO_THROW;
	Request * Pop();
	void Stop();
	virtual ~CMsgQueue();

private:
	std::queue<Request *> m_queue;
        
	pthread_mutex_t msg_queue_mutex;// мьютекс атомарности добавления и удаления сообщений из очереди
	sem_t msg_queue_count_sem;//семофор для засыпания процесса обработчика сообщений очереди в случае их отсутсвия

};

#endif	/* CMSGQUEUE_H */
