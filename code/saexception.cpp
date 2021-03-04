/***************************************************************************
                          saexception.cpp  -  description
                             -------------------
    begin                : Thu Jun 22 2006
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

#include "saexception.h"
namespace SAExceptions{

SAexception::SAexception(){
}
SAexception::~SAexception()  throw(){
}
/** No descriptions */
const char * SAexception::handle(){
}
}/** No descriptions */
void SAExceptions::SAexception::setMsg(string ms){
  msg = ms;
}
/** No descriptions */
string SAExceptions::SAexception::getMsg() const{
  return msg;
}

string SAExceptions::SAexception::getMsg() {
  return msg;
}
