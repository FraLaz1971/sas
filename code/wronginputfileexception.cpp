/***************************************************************************
                          wronginputfileexception.cpp  -  description
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

#include "wronginputfileexception.h"
#include "iostream.h"

namespace SAExceptions{

WrongInputFileException::WrongInputFileException(){
}
WrongInputFileException::~WrongInputFileException() throw(){
}
}
/** handles the exception when a wrong input file is selected */
//const char* SAexceptions::WrongInputFileException::handle(){
//  cout << "WrongInputFileException::handle() handling exception!" << endl;
//   QMessageBox::critical(0, "Wrong filename",
//                              "Please select a correct L2 data file.",
//                              QMessageBox::Ok, QMessageBox::NoButton);
//   return (const char*)"/home/lazza/data/fits/SAF_SFTE_scie_010230_040127_182841_3_red.fits";
//}
