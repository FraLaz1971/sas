/***************************************************************************
                          type2exception.h  -  description
                             -------------------
    begin                : Wed Mar 8 2006
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
/***************************************************************************
This software is part of the of the SuperAGILE instrument data 
analysis software library
 ***************************************************************************/

#ifndef TYPE2EXCEPTION_H
#define TYPE2EXCEPTION_H


/**
  *@author Francesco Lazzarotto
  */
#include "saexception.h"
namespace SAExceptions{
using namespace SAExceptions;
class Type2Exception : public SAexception{
public: 
	Type2Exception() throw();
	~Type2Exception() throw();
  /** No descriptions */
  void handle2() throw();
};
}
#endif
