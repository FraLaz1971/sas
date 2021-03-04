/***************************************************************************
                          commandlineexception.h  -  description
                             -------------------
    begin                : Thu Aug 3 2006
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

#ifndef COMMANDLINEEXCEPTION_H
#define COMMANDLINEEXCEPTION_H

#include <exception>
#include <iostream>
namespace SAExceptions{
using namespace std;

/**
  *@author Francesco Lazzarotto
  */

class CommandlineException : public exception  {
public: 
	CommandlineException();
	~CommandlineException() throw();
    /** No descriptions */
  const char * handle();

  const char * what();

};
}
#endif
