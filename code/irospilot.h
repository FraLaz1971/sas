/***************************************************************************
                          irospilot.h  -  description
                             -------------------
    begin                : Tue Mar 20 2007
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

#ifndef IROSPILOT_H
#define IROSPILOT_H

#include "pipelinemodule.h"
#include "sal3eventlist.h"
#include <string>

/**class that implements all the interfaces with original iros IDL code
  *@author Francesco Lazzarotto
  */

namespace   SApipeline{
using namespace SApipeline;
using namespace SAExceptions;
using namespace SAdata;
using namespace std;
//using namespace SAdata;
class IrosPilot : public PipelineModule  {
public: 
	IrosPilot();
	~IrosPilot();
  /** */
  void setDataDir(const string & dn);
  /** */
  string getDataDir();
  /** */
  void setBaseDir(const string & fn);
  /** */
  string getBaseDir();
  /** */
  void setFileName(const string & fn);
  /** */
  string getFileName();
  /** */
  void setCatalogName(const string & cn);
  /** */
  string getCatalogName();
  /** */
  void setDetector(unsigned char d);
  /** */
  unsigned char getDetector();
  /** */
  void setLadGap(unsigned short lg);
  /** */
  unsigned short  getLadGap();
  /** */
  void setGapStart(unsigned short gs);
  /** */
  unsigned short  getGapStart();
  /** */
  void setMaxRounds(unsigned short mr);
  /** */
  unsigned short  getMaxRounds();
  /** */
  void setMinSigmas(unsigned short ms);
  /** */
  unsigned short  getMinSigmas();
  /** */
  void setCatalogueOption(bool co);
  /** */
  void getCatalogueOption();
  /** No descriptions */
  string getPilotFileDir();
    
  /** No descriptions */
  void createPilot(byte det, const string pfn);
  /** No descriptions */
  void createPilot(byte det);
  
  /** No descriptions */
  void createPointingPilot();

  /** No descriptions */
  void readDefaultPilot(const string &pfn);

  /** No descriptions */
  void readDefaultPointPilot(const string &ppfn);

  /** No descriptions */
  void setPilotFilename(const string &pfn);

  /** No descriptions */
  void setPointPilotFilename(const string &ppfn);

  /** No descriptions */
  void launchIros(byte det);

  /** No descriptions */
  string getPilotFilename();

  /** No descriptions */
  string getPointPilotFilename();

  /** No descriptions */
  void setOutfilePrefix(const string &prfn);
  /** No descriptions */
  string getOutfilePrefix();

  /** No descriptions */
  void setLogfileName(const string &lfn);
  /** No descriptions */
  string getLogfileName();
  /** No descriptions */
  void createPointingPilot(const string &pfn, const string &cn);

protected:
// pointing batch infos
// iros pilot batch infos
string base_dir; /// Base directory
string data_dir; /// data dir
string file; /// Input file name
unsigned char detector; /// Detector number
unsigned short lad_gap; ///  Gap between ladders
unsigned short gap_start; ///  Strip No. after gap
unsigned short max_rounds; /// No. os IROS rounds
unsigned short min_sigmas; ///  Number os STDs
unsigned char use_cat; /// Set to 1 if catalog is to be used
string iroscommand;
string pilotfilename;
string pointpilotfilename;
string logfilename;
string catalogname;
string outfileprefix;


vector<string> pilotlines;
vector<string> pointpilotlines;
  
};

/* 
./launchIros "/home/lazza/projects/attitude_launcher/MD_IROS_Pilot_v4_test_0" "/home/lazza/.MD_IROS_Point_Pilot_v4" "iros_out.log" "thisprefix"




        os << "BASE_DIR    = "<<getSasoaHome()<<"/stg_2/	      ; Base directory" << endl;
            os << "FILE	    = "+irosmapfilename+"    ; Input file name " << endl;
            os << "DETECTOR    = "<<int(det)<<"			          ; -- Detector number" << endl;
            os << "LAD_GAP	    = 19			       ; Gap between ladders" << endl;
            os << "GAP_START   = 768			   ; Strip No. after gap" << endl;
            os << "MAX_ROUNDS  = 2				   ; No. os IROS rounds" << endl;
            os << "MIN_SIGMAS  = -1			       ; Number os STDs." << endl;
            os << "USE_CAT	    = 0 			          ; Set to 1 if catalog is to be used. " << endl;
*/
}
#endif
