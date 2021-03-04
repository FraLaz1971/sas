/***************************************************************************
                          outputfileexception.cpp  -  description
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

#include "outputfileexception.h"

namespace SAExceptions{

OutputFileException::OutputFileException(){
}
OutputFileException::~OutputFileException()  throw(){
}
const char * OutputFileException::handle(){
   cout << "WrongInputFileException::handle() handling exception!" << endl;
//   QMessageBox::critical(0, "Empty filename",
//                              "Please select a SA L2 data file.",
//                              QMessageBox::Ok, QMessageBox::NoButton);
   s = (const char*)"/home/lazza/data/fits/SAF_SFTE_scie_010230_040127_182841_3_red.fits";
  return s;
}
}