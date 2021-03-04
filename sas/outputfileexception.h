/***************************************************************************
                          outputfileexception.h  -  description
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

#ifndef OUTPUTFILEEXCEPTION_H
#define OUTPUTFILEEXCEPTION_H

#include <saexception.h>

/**
  *@author Francesco Lazzarotto
  */
//#include <qmessagebox.h>
using namespace std;
namespace SAExceptions{

class OutputFileException : public SAexception  {
public: 
	OutputFileException();
	~OutputFileException() throw();
  /** No descriptions */
  const char * handle();
};
}
#endif
