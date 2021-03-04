/***************************************************************************
                          eventlist.h  -  description
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

#ifndef EVENTLIST_H
#define EVENTLIST_H


/**
  *@author Francesco Lazzarotto
  */
#include "event.h"
template <class Event>
class EventList {
public: 
	EventList(unsigned long evnum);
	~EventList();
  /** No descriptions */
  void setEvent(Event ev, unsigned long int index);
  void showEvents();
  /** No descriptions */
  void fillDefault();
protected:
Event  *evlist;
private:
unsigned long int k; /// counter variable for currently pointed event
unsigned long int dimension;
};

template <class Event>
EventList<Event>::EventList(unsigned long evnum){
  dimension = evnum;
  evlist = new Event[dimension];
  fillDefault();
}
template <class Event>
EventList<Event>::~EventList(){
}

template <class Event>
void EventList<Event>::showEvents(){
  k=0;
  while(k<dimension){
    cout << "list element n. "<< k << " = "<< evlist[k] << endl;
    k++;
  }
}

template <class Event>
void EventList<Event>::fillDefault(){
    k=0;
  while(k<dimension){
    evlist[k] = k*1.3;
    k++;
  }

}




/** No descriptions */
//template <class Event>
//void Eventlist<Event>::setEvent(Event ev, unsigned long int index){
//  evlist[index] =  ev;
//}
#endif
/** No descriptions */
