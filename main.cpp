/* 
 * File:   main.cpp
 * Author: heven
 *
 * Created on 25 Декабрь 2012 г., 12:36
 */

#include "global_const.h"
namespace google {
    typedef int int32 ;
};
#include <cstddef>
#include <cstdlib>
#include "CMainQueueHandler.h"
#include "CRequestCreater.h"
#include "CStateController.h"
#include <boost/thread/thread.hpp>
#include "CGoogleLoggining.h"

using namespace std;

CGoogleLoggining GoogleLog;// It should be first in list of global objects

long MC_DELAY_OF_POST_MESSAGES = 200000;// 0,2 sec - 5 messages for second
int TIME_OF_WORK = 30;// Full time of message exchanging in sec's
int THREADS_HEANDLERS_COUNT = 5;
long TIME_OF_TASK_PROCESSING = 1000000;// 1 sec

//CMsgQueue IncMsgQueue;

/*
 * 
 */
int main(int argc, char** argv) {
  CMsgQueue m_MsgQueue;
  m_MsgQueue.Initialize();
  std::list<CMainQueueHandler *> threadsList ;
  VLOG(0) << "Start main thread";
  CStateController & stateController = CStateController::Instance();
  stateController.SetMainThreadState(e_INIITIALIZING_TASK);
  CRequestCreater RequestCreater(MC_DELAY_OF_POST_MESSAGES);
  RequestCreater.Start();
  stateController.SetMainThreadState(e_WORKING_TASK);
  for(int i=0;i<THREADS_HEANDLERS_COUNT;i++){
      CMainQueueHandler * pHandler = stateController.CreateNewMainQueueHandler(TIME_OF_TASK_PROCESSING);
      if(pHandler != NULL){
        pHandler->Start();
        threadsList.push_back(pHandler);
        VLOG(0) << "thread ["<< i <<"] with id["<< pHandler->getID() <<"] is created and started.";
      }
  }
  sleep(TIME_OF_WORK);// Time of Message processing
  //Finish Threads
  stateController.SetMainThreadState(e_FINISHING_TASK);
  RequestCreater.Stop();
  std::list<CMainQueueHandler *>::iterator iter = threadsList.begin();
  for(;iter != threadsList.end();iter++){
      CMainQueueHandler * pHendler = *iter;      
      VLOG(0) << "thread with id["<< pHendler->getID() <<"] is stopped. Removing.";
      delete pHendler;
  }
  threadsList.clear();
  stateController.SetMainThreadState(e_TERMINATED_TASK);
  m_MsgQueue.Stop();
  if(stateController.IsTaskFullFinished()){
    CStateController::Terminate();
  }
  VLOG(0) << "Finish main thread";
  return 0;
}

