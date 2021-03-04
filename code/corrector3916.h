/***************************************************************************
                          corrector3916.h  -  description
                             -------------------
    begin                : Fri Dec 14 2007
    copyright            : (C) 2007 by Francesco Lazzarotto
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

#ifndef CORRECTOR3916_H
#define CORRECTOR3916_H

#include "sadatacorrector.h"

/**Correct 3916 telemetry data
  *@author Francesco Lazzarotto
  */
namespace DataCorrection{
class Corrector3916 : public SADataCorrector  {
public: 
	Corrector3916();
	Corrector3916(const string &fn, const string &ofn);
//	void prepare();
	~Corrector3916();
};
}
#endif
