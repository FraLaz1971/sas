/***************************************************************************
                          tempdatasetbuilder.h  -  description
                             -------------------
    begin                : Wed Dec 12 2007
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

#ifndef TEMPDATASETBUILDER_H
#define TEMPDATASETBUILDER_H

#include "pipelinemodule.h"

/**builds data set useful for analysis on temporal data set
  *@author Francesco Lazzarotto
  */
using namespace SApipeline;
using namespace SAExceptions;
using namespace std;
//using namespace SAdata;
using namespace System;

namespace SApipeline{
namespace TDS {
class TempDataSetBuilder : public PipelineModule  {
public: 
  	TempDataSetBuilder();
	~TempDataSetBuilder();
    void unzipEphRange(int contactmin, int contactmax);
    void unzipAttRange(int contactmin, int contactmax);
    void unzipL2Range(int contactmin, int contactmax);
    string getCentString(int contact);
};
}
}
#endif
/*
	unzipAttRange $pars
		ss.str("");ss << "./rsync_l2file.sh " << contint[0] << " " << contint[1] << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);
	unzipEphRange $pars
		ss.str("");ss << "./rsync_l2file.sh " << contint[0] << " " << contint[1] << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);
	unzipL2Range $pars
		ss.str("");ss << "./rsync_l2file.sh " << contint[0] << " " << contint[1] << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);
*/