/***************************************************************************
                          corrector3905.h  -  description
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

#ifndef CORRECTOR3905_H
#define CORRECTOR3905_H

#include "sadatacorrector.h"

/**correct 3905 SA telemetry data
  *@author Francesco Lazzarotto
  */
namespace DataCorrection{
using namespace DataCorrection;
using namespace SApipeline;
using namespace SAarchive;
using namespace std;
using namespace CCfits;

class Corrector3905 : public SADataCorrector  {
public: 
	Corrector3905();
	Corrector3905(const string &fn, const string &ofn);
	~Corrector3905();
    void Correct3905(const string &fn, const string &ofn, double tstart, double tstop);
	//void prepare();
	//void setASDC(bool val);
};
}
#endif
