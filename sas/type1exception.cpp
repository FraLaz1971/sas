/***************************************************************************
                          type1exception.cpp  -  description
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

#include "type1exception.h"
namespace SAExceptions{
Type1Exception::Type1Exception() throw() {
}
Type1Exception::~Type1Exception() throw() {
}
}/** No descriptions */
void SAExceptions::Type1Exception::handle1() throw() {
  cout << "handling type 1 exception" << endl;
}
