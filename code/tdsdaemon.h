/***************************************************************************
                          tdsdaemon.h  -  description
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

#ifndef TDSDAEMON_H
#define TDSDAEMON_H

#include "daemon.h"
#include "qapplication.h"
#include "tempdatasetbuilder.h"
#include "sadatacorrector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include "samonitor.h"
#include "saexception.h"
#include "orbitrebuilder.h"
#include "sourcesextractor.h"
#include "archivehandler.h"
#include "systemconnector.h"
#include "archivescanner.h"
#include "irospilot.h"
#include "timer.h"
#include <exception>
#include <stdexcept>
#include "saexception.h"

#include "agiletimer.h"


/**daemon to handle Temporal Data Set pipeline
  *@author Francesco Lazzarotto
  */

using namespace SAdata;
using namespace SApipeline;

namespace SApipeline {

namespace TDS {

using namespace SApipeline;
using namespace SAarchive;
using namespace std;
using namespace TDS;

class TDSDaemon : public Daemon  {
public:   
	TDSDaemon();
	TDSDaemon(vector<string> dbc);
	~TDSDaemon();
    void start(double tstart, double tstep);
    void setCotDir(string cotd);
    string getCotDir();
    void cotProcess();
    void launchTDS(double tstart, double tstop);
    vector<int> getContactRange(double tstart, double tstop);
    void processSRC();
    int process();
    void initArchiveEnv(ArchiveHandler *sarchiver, PipelineModule &pipemodule);
    void setLocalHost(string lh);
    string getLocalHost();
    void setRemoteUser(string ru);
    string getRemoteUser();
    void setRemoteHost(string ro);
    string getRemoteHost();

protected:

	string cotdir;
	AGILETimer atime;
	vector<int> myiv;
    	AGILEDBConnector *dbp;
	TempDataSetBuilder tdbuilder;
	string outfilename;
	string localhost;
	string remoteuser;
	string remotehost;

};
}
}
#endif
