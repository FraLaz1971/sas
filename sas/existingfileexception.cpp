/***************************************************************************
                          existingfileexception.cpp  -  description
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

#include "existingfileexception.h"
//#include "qmessagebox.h"
namespace SAExceptions {
ExistingFileException::ExistingFileException(){
}
ExistingFileException::~ExistingFileException() throw(){
}
}/** No descriptions */
//const char * SAexceptions::ExistingFileException::handle(){
//   const char * s;
//   cout << "ExistingFileException::handle() handling exception!" << endl;
//   QMessageBox::critical(0, "It's impossible create the directory ",
//                              "...",
//                              QMessageBox::Ok, QMessageBox::NoButton);
//   s = (const char*)"/usr/local/data";
//  return s;
//}

