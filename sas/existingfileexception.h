/***************************************************************************
                          existingfileexception.h  -  description
                             -------------------
    begin                : Thu Apr 7 2005
    copyright            : (C) 2005 by Francesco Lazzarotto
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

#ifndef EXISTINGFILEEXCEPTION_H
#define EXISTINGFILEEXCEPTION_H

#include <exception>
#include <iostream>
//#include <qmessagebox.h>
/**
  *@author Francesco Lazzarotto
  */

namespace SAExceptions {
using namespace std;
using namespace SAExceptions;
class ExistingFileException : public exception  {
public: 
	ExistingFileException();
	~ExistingFileException() throw();
  /** No descriptions */
  const char * handle();
  
};
}

#endif
