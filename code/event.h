/***************************************************************************
                          event.h  -  description
                             -------------------
    begin                : Thu Jul 20 2006
    copyright            : (C) 2006 by Francesco Lazzarotto
    email                : lazza@rm.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef EVENT_H
#define EVENT_H
#include <iostream>

/**
  *@author Francesco Lazzarotto
  */
using namespace std;
//template <class T>
class MyEvent {
public:
	MyEvent();
	~MyEvent();
  /** No descriptions */
  int getPosition();
  /** No descriptions */
  void setPosition(int pos);
  /** No descriptions */
  float getEnergy();
  /** No descriptions */
  void setEnergy(float en);
  /** No descriptions */
  unsigned long getTime();
  /** No descriptions */
  void setTime(unsigned long time);
  /** No descriptions */
  void show();
protected:
int position;
unsigned long time;
float energy;
};
//template <class T>
//MyEvent::MyEvent(){
//}
//template <class T>
//MyEvent::~MyEvent(){
//}
/** No descriptions */
//template <class T>
//void MyEvent::setPosition(int pos){
//  position = pos;
//}
///** No descriptions */
//template <class T>
//int MyEvent::getPosition(){
//  return position;
//}
///** No descriptions */
//template <class T>
//void MyEvent::setTime(unsigned long time){
//}
///** No descriptions */
//template <class T>
//unsigned long MyEvent::getTime(){
//  return time;
//}
///** No descriptions */
//template <class T>
//void MyEvent::setEnergy(float en){
//  energy = en;
//}
///** No descriptions */
//template <class T>
//float MyEvent::getEnergy(){
//  return energy;
//}


/** No descriptions */
//template <class T>

#endif