/* 
 * File:   Stopper.h
 * Author: heven
 *
 * Created on 26 Декабрь 2012 г., 0:25
 */

#ifndef STOPPER_H
#define	STOPPER_H
enum stop_command_t{
    e_NO_NEED_STOP,
    e_STOP_NOW,
    e_STOP_AFTER_PROCESSING
};

class Stopper {
 stop_command_t  m_StopState;
public:
    Stopper();
   // Stopper(const Stopper& orig);
   virtual ~Stopper();
   stop_command_t getState() const {return m_StopState;};
   stop_command_t setState(const stop_command_t _state){m_StopState = _state;};
private:

};

#endif	/* STOPPER_H */

