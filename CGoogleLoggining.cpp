/* 
 * File:   CGoogleLoggining.cpp
 * Author: heven
 * 
 * Created on 7 Февраль 2011 г., 10:43
 */

#include "CGoogleLoggining.h"

CGoogleLoggining::CGoogleLoggining() {
      google::InitGoogleLogging("AAM");
}

CGoogleLoggining::~CGoogleLoggining() {
    sleep(3);
    google::ShutdownGoogleLogging();
}
