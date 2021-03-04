/***************************************************************************
                          emptyfilenameexception.h  -  description
                             -------------------
    begin                : Tue Mar 22 2005
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

#ifndef EMPTYFILENAMEEXCEPTION_H
#define EMPTYFILENAMEEXCEPTION_H

#include <exception>
//#include <qmessagebox.h>

namespace SAExceptions{ 
using namespace std;
/**
  *@author Francesco Lazzarotto
  */

class EmptyFileNameException : public exception  {
public: 
	EmptyFileNameException();
	~EmptyFileNameException() throw();
  /** No descriptions */
  const char * handle();
  /** No descriptions */

};
}

#endif
/** No descriptions */

