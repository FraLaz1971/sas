/***************************************************************************
                          type2exception.cpp  -  description
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

#include "type2exception.h"
namespace SAExceptions{
Type2Exception::Type2Exception() throw(){
}
Type2Exception::~Type2Exception() throw() {
}
}/** No descriptions */
void SAExceptions::Type2Exception::handle2() throw(){
  cout << "handling type 2 exception" << endl;
}
