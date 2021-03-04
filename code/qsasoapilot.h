/***************************************************************************
                          qsasoapilot.h  -  description
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

#ifndef QSASOAPILOT_H
#define QSASOAPILOT_H

#include "SasoaPilotBase.h"
#include "sasoauserinterface.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <exception>

/**pilots sasoa pipeline
  *@author Francesco Lazzarotto
  */

class QSasoaPilot : public SasoaPilotBase  {
public: 
	QSasoaPilot();
	~QSasoaPilot();
  /** No descriptions */
  void clean();
  /** No descriptions */
  void uninstal();
  /** No descriptions */
  void debug();
  /** No descriptions */
  void run();
  /** No descriptions */
  void setSasoa(SasoaUserInterface &sui);
  /** No descriptions */
  void quitSasoa();
  
private:

  SasoaUserInterface *sasoaUI;
  
};

#endif
