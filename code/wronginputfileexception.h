/***************************************************************************
                          wronginputfileexception.h  -  description
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

#ifndef WRONGINPUTFILEEXCEPTION_H
#define WRONGINPUTFILEEXCEPTION_H

#include <exception>
//#include <qmessagebox.h> 
/**
  *@author Francesco Lazzarotto
  */
using namespace std;
namespace SAExceptions {
class WrongInputFileException : public exception  {
public: 
	WrongInputFileException();
	~WrongInputFileException() throw();
  /** handles the exception when a wrong input file is selected */
  const char * handle();
};
}
#endif
