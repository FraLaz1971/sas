//
// C++ Interface: tdssrcnrgdaemon
//
// Description: 
//
//
// Author: TDS src & energy account <TDS_src_nrg@bigfoot>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TDSTDSSRCNRGDAEMON_H
#define TDSTDSSRCNRGDAEMON_H
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

namespace SApipeline {
namespace TDS {

using namespace SApipeline;
using namespace SAarchive;
using namespace std;

/**
daemon to run TDS soruce & energy filter analysis

	@author TDS src & energy account <TDS_src_nrg@bigfoot>
*/
class TDSSrcNrgDaemon : public Daemon
{
public:
    TDSSrcNrgDaemon();
    TDSSrcNrgDaemon(vector<string> dbc);
    ~TDSSrcNrgDaemon();
    void start(double tstart, double tstep);
    void setCotDir(string cotd);
    string getCotDir();
    void cotProcess();
    //void launch_TDS_Source(double mtstart, double mtstop, double msrc_ra, double msrc_dec, string prefix); // disabled
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
    void launch_TDS_src_nrg(double mtstart, double mtstop, double msrc_ra, double msrc_dec, string prefix, double emin, double emax);

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
	string src_prefix;
	double src_ra;
	double src_dec;
};

}
}
#endif
