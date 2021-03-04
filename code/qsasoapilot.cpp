/***************************************************************************
                          qsasoapilot.cpp  -  description
                             -------------------
    begin                : Fri Dec 1 2006
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

#include "qsasoapilot.h"

QSasoaPilot::QSasoaPilot(){
}
QSasoaPilot::~QSasoaPilot(){
}
/** No descriptions */
void QSasoaPilot::run(){
  system("./launch_exec_sasoa &");
}
/** No descriptions */
void QSasoaPilot::debug(){
  system("./launch_debug_sasoa &");
}
/** No descriptions */
void QSasoaPilot::uninstal(){
  system("./launch_uninstall &");
}
/** No descriptions */                       
void QSasoaPilot::clean(){
  try{
    system("./launch_clean_sasoa &");
    sasoaUI->clean();
  } catch (const exception &e){
    cerr << "exception "<< e.what() << endl;
  }
}
/** No descriptions */
void QSasoaPilot::setSasoa(SasoaUserInterface &sui){
  sasoaUI = &sui;
}
/** No descriptions */
void QSasoaPilot::quitSasoa(){  
  sasoaUI->handle_quit();
  close();  exit(0);
}
