/***************************************************************************
                          commandlineexception.cpp  -  description
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

#include "commandlineexception.h"
namespace SAExceptions{
CommandlineException::CommandlineException(){
}
CommandlineException::~CommandlineException() throw() {
}
  const char * CommandlineException::handle(){
       cout << "handling exception "<< what() << " "<< exception::what() << endl;
       return "";
  }

  /** No descriptions */
  const char * CommandlineException::what(){
    
       return "SASOA Commandline exception";
  }
}