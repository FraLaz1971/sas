/***************************************************************************
                          saexception.h  -  description
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

#ifndef SAEXCEPTION_H
#define SAEXCEPTION_H

#include <exception>
#include <iostream>
#include <string>

//#include <qmessagebox.h>

/**
  *@author Francesco Lazzarotto
  */
using namespace std;
namespace SAExceptions{

class SAexception : public exception  {
public: 
	SAexception();
	~SAexception()  throw();
  /** No descriptions */
  const char * handle();
  /** No descriptions */
  string getMsg();
  /** No descriptions */
  string getMsg() const;
  /** No descriptions */
  void setMsg(string ms);
  protected:
  /** No descriptions */
  const char * s;
  /** No descriptions */
  string msg;  
};
}
#endif
