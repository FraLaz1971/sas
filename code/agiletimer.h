/***************************************************************************
                          agiletimer.h  -  description
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

#ifndef AGILETIMER_H
#define AGILETIMER_H

#include "timer.h"
#include "sadatetime.h"
#include <cstdlib>

/**Gives all utilities for AGILE timing operations
  *@author Francesco Lazzarotto
  */
namespace SApipeline {
  
namespace TDS {

using namespace SApipeline;

using namespace SAdata;
using namespace TDS;
using namespace std;
class AGILETimer : public Timer  {
public: 
	AGILETimer();
	~AGILETimer();
    string AGILETimeToUTC(double tf);
    double UTCToAGILETime(string temps2);
	string AGILETimeToUTCDateTime(double tf);
protected:
SADateTime datetime;
double mytime;
};
}
}
#endif
