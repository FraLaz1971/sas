/***************************************************************************
                          saparameterslist.h  -  description
                             -------------------
    begin                : Mon May 8 2006
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

#ifndef SAPARAMETERS_H
#define SAPARAMETERS_H

#include <sametadata.h>
#include <iostream>
#include <string>

#include <vector>
#include <map>

#include <iterator>
#include"sasoacommand.h"
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <pipelinemodule.h>
#include "saparameter.h"
/**
  *@author Francesco Lazzarotto
  */
using namespace std;

namespace SApipeline{
class SAParametersList : public map<string, string>, public PipelineModule  {
public: 
	SAParametersList ();
	~SAParametersList ();
  /** No descriptions */
  void setNoisyLutName(const string &nlutnam);
  /** No descriptions */
  string getGainLutName();
  /** No descriptions */
  void setGainLutName(const string &glutnam);
  /** No descriptions */
  string getNoisyLutName();
  /** No descriptions */
  void show();
  /** No descriptions */
  void saveParameterList(bool extlang);
  /** No descriptions */
  map<string, string> getMap();
  /** No descriptions */
  void setMap(const map<string, string> &passmap);
  /** No descriptions */
  void setParameter(const SAParameter &sp);
  /** No descriptions */
  void saveCalibrationParameters(bool extlang);
  /** No descriptions */
  void savePhotonParameters(bool extlang);

private:
  /** map object containing parameters to configure SASOA pipeline*/
  map<string, string> pars_map;
  vector<string> defpar;
};
}
#endif
