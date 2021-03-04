/***************************************************************************
                          archivemodule.h  -  description
                             -------------------
    begin                : Mon Sep 18 2006
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

#ifndef ARCHIVEMODULE_H
#define ARCHIVEMODULE_H


/**general archive handling class
  *@author Francesco Lazzarotto
  */
#include <vector>
#include <string>
#include "hertagbase.h" 
#include "systemconnector.h" 


/**Handles archive functions (path for input files, output files, archive organization)
  *@author Francesco Lazzarotto
  */
//static enum SATask = {Preprocessing, Correction, OrbitRebuilding,
//  PhotonListBuilding, SourcesExtraction, SourceAnalysis};

namespace SAarchive{

using namespace SAarchive;
using namespace std;
using namespace System;

class ArchiveModule: public HertagBase {

public: 
   ArchiveModule();

  ~ArchiveModule();


protected:

SystemConnector syscon;
  
SATask task;

string inputfilename;

string outputfilename;

bool verbose;

};
}
#endif
