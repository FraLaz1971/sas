/***************************************************************************
                          corrector3906.h  -  description
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

#ifndef CORRECTOR3906_H
#define CORRECTOR3906_H

#include "sadatacorrector.h"

/**correct 3906 SA telemetry data
  *@author Francesco Lazzarotto
  */
namespace DataCorrection{
using namespace DataCorrection;
using namespace SApipeline;
using namespace SAarchive;
using namespace std;
using namespace CCfits;

class Corrector3906 : public SADataCorrector  {
public: 
	Corrector3906();
	Corrector3906(const string &fn, const string &ofn);
	~Corrector3906();
	//void prepare();
	//void setASDC(bool val);
};
}
#endif
