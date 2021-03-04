/***************************************************************************
                          archivehandler.h  -  description
                             -------------------
    begin                : Wed Feb 22 2006
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
/***************************************************************************
This software is part of the of the SuperAGILE instrument data 
analysis software library
 ***************************************************************************/

#ifndef ARCHIVEHANDLER_H
#define ARCHIVEHANDLER_H

#include "safilenamer.h"
#include "filelist.h"
#include "archivemodule.h"
#include "sadatetime.h"
#include <vector>
#include <string>
#include "agiledbconnector.h"

/**Handles archive functions (path for input files, output files, archive organization)
  *@author Francesco Lazzarotto
  */


namespace SAarchive{
using namespace DB;
using namespace SAarchive;
using namespace std;
using namespace SAdata;
using namespace System;


class ArchiveHandler: public ArchiveModule {
public: 
  /** No descriptions */

    ArchiveHandler();
  /** No descriptions */
    ArchiveHandler(ArchiveHandler &a);
  /** No descriptions */
 ~ArchiveHandler();
  /** No descriptions */
	string getIrosMapFileName();
  /** No descriptions */
	void setIrosMapFileName(const string &imfn);
  /** No descriptions */
    void clear_SAL1Cor_Data();
  /** No descriptions */
    void clear_SAL1Orb_Data();
  /** No descriptions */
    void clear_L2_Data();
  /** No descriptions */
    void clear_L3_Data();
  /** No descriptions */
    void clear_L19_Data();
   
  /** No descriptions */
    void set_SAL1Cor_Dir(const string &l1corn);
  /** No descriptions */
    void set_SAL1Orb_Dir(const string &l1orbn);
  /** No descriptions */
    void set_L1_Dir(const string &l1n);
  /** No descriptions */
    void set_L2_Dir(const string &l2n);
  /** No descriptions */
    void set_L3_Dir(const string &l3n);
  /** No descriptions */
    void set_L19_Dir(const string &l19n);
  /** No descriptions */
    void set_Contacts_Dir(const string &cd);
  /** No descriptions */
    void createTDSArchiveDir(double tstart, double tstop);
  /** No descriptions */
    void createTDSSourceArchiveDir(double tstart, double tstop, double src_ra, double src_dec);
  /** No descriptions */
    string getTDSSourceArchiveDir(double tstart, double tstop, double src_ra, double src_dec);
  /** No descriptions */
    string get_SAL1Cor_Dir();
  /** No descriptions */
    string get_SAL1Orb_Dir();
  /** No descriptions */
    string get_L1_Dir();
  /** No descriptions */
    string get_L2_Dir();
  /** No descriptions */
    string get_L3_Dir();
  /** No descriptions */
    string get_L19_Dir();
  /** No descriptions */
    string get_Contacts_Dir();
  /** No descriptions */
    string get_L2_Filename(int contactnum);
  /** No descriptions */
    string get_Att_Filename(int contactnum);
  /** No descriptions */
  void setSagaGTI_filename(const string &sh);
  /** No descriptions */
  void setExposureGTI_filename(const string &sh);

  /** No descriptions */
    string getSasoaHome();
  /** No descriptions */
    void setSasoaHome(const string &sh);
  /** No descriptions */
    void setSasoaWorkDir(const string &swd);
  /** No descriptions */
    string getSasoaWorkDir();
  /** No descriptions */
    void clearDeliverableData();
  /** No descriptions */
    void copyDeliverableData(const string &dirname);
  /** No descriptions */
    void moveDeliverableData(const string &dirname);
  /** No descriptions */
    void showEnv();
  /** No descriptions */
    string getDeliveryDir();
  /** No descriptions */
    void setDeliveryDir(const string &dd);
  /** No descriptions */
    void setDefault();
  /** No descriptions */
    /** No descriptions */
    void createCurrentArchiveDir();
    /** No descriptions */
    void setArchiveRoot(const string &ar);
    /** No descriptions */
    string getArchiveRoot();
  /** No descriptions */
    void setArchiveDir(const string & ad);
    /** No descriptions */
    string  getTDSArchiveDir(double tstart, double tstop);
    /** No descriptions */
    string  getArchiveDir();
    void retrieveArchiveDir(const string &ad);
    /** No descriptions */
    void moveFile(const string &infile, const string &outdir);
  /** No descriptions */
    string getFormattedStringNumber(int n);
    /** No descriptions */
    string getFormattedStringNumber(int n, int dir_len);
  /** save on a text file the data directories used at the moment in the processing */
  void saveDataDirs();
  /** retrieve the used data directories defaults, saved in the text file updated recently */
  void retrieveDataDirs();
  /** No descriptions */
  void setDataDirs();
  /** find the L1 cor files needed by the Orbit Rebuilder stage */
  void findL1Cor(const string &cnts);
  /** No descriptions */
  string getCurrentL1CorFileName();
  /** No descriptions */
  void retrieveAllFileNames();
  /** No descriptions */
  string getSAL1Orb_FileName();
  /** No descriptions */
  string getDefaultOutputDir();
  /** No descriptions */
  string getDefaultOutputDir(SATask st);
  /** No descriptions */
    void clearDefaultData();
  /** No descriptions */
    void rmTempFiles();
  /** No descriptions */
    void rmTempInputFiles();
  /** No descriptions */
    void rmTempOutputFiles();
  /** No descriptions */
  void clearIROS();
  /** No descriptions */
  void clearProducts();
  /** No descriptions */
  /** No descriptions */
  void clear_OLD_L1_Data();
  /** No descriptions */
    string getAttitudeDir();
  /** No descriptions */
    string getExposureDir();
  /** No descriptions */
    string getSagaDir();
  /** No descriptions */
    void loadOrbit(int orbnum);
  /** No descriptions */
    void loadContact(int contnum);
  /** No descriptions */
    void setDefaultContactsDir(const string& cd);
  /** No descriptions */
    string getDefaultContactsDir();
  /** No descriptions */
    string  getLoaded3905FileName();
  /** No descriptions */
    string  getLoadedCor3905FileName();    
  /** No descriptions */
    string  getLoaded3914FileName();
  /** No descriptions */
    string  getLoaded3916FileName();
  /** No descriptions */
    int getCurrentContactNumber();
  /** No descriptions */
    string getCurrentSagaGTI_FileName();
  /** No descriptions */
    string getCurrentExposureGTI_FileName();
  /** No descriptions */
    void clear_L1_Data();
  /** No descriptions */
    void clearTempData();
  /** No descriptions */
    string getHundredContactsDir(int contactnum);
  /** No descriptions */
    string getIASFContactInputDir(int contactnum);
  /** No descriptions */
	void loadContactSSH(const string &thishost, const string &remotehost, int contactnum);
  /** No descriptions */
    string getUserHome();
  /** No descriptions */
    string getDefaultInputDir(int contactnum);
  /** No descriptions */
    string getCurrentSOE_Name();
  /** No descriptions */
    void setAttitudeDir(const string &attdir);
  /** No descriptions */
    void setEphemeridesDir(const string &ephdir);
  /** No descriptions */
    string getEphemeridesDir();
  /** No descriptions */
    void deliveryIrosProducts(const string &prefix);
  /** No descriptions */
 
  /** gives a list of filename for the input runid */
//  vector<string> files getFilenames(int runid);
 SAFileNamer filenamer;

 string curcont;
 
 protected:

  /** No descriptions */
 string SASOA_WORK_DIR; // is the root of SASOA environment
  /** No descriptions */
 string SASOA_HOME; // is where sasoa is installed
  /** No descriptions */
 string DELIVERY_DIR; // is where data are temporary delivered
  /** No descriptions */
 string ARCHIVE_ROOT; // the root dir where data are finally stored
  /** No descriptions */
 string ARCHIVE_DIR; // the current dir where data are finally stored
  /** No descriptions */
 string CONTACTS_DIR;// directory where contacts telemetry data (FITS) are stored
  /** No descriptions */
 string ATTITUDE_DIR; // the dir where are attitude processing source files 
  /** No descriptions */
 string EXPOSURE_DIR; // the dir where are exposure processing source files
  /** No descriptions */
 string SAGA_DIR; // the dir where are saga processing source files

  /** No descriptions */
 string SAL1Cor_Dir;
  /** No descriptions */
 string SAL1Orb_Dir;
  /** No descriptions */
 string L1_Dir;
  /** No descriptions */
 string L19_Dir;
  /** No descriptions */
 string L2_Dir;
  /** No descriptions */
 string L3_Dir;
 
  /** No descriptions */
 string DefaultDir;

  /** No descriptions */
 string SAL1Cor_filename;
  /** No descriptions */
 string SAL1Orb_filename;
  /** No descriptions */
 string Irosmap_filename;
  /** No descriptions */
 string L19_filename;
  /** No descriptions */
 string L2_filename;
  /** No descriptions */
 string L3_filename;
  /** No descriptions */
 string ExposureGTI_filename;
  /** No descriptions */
 string SagaGTI_filename;

  /** No descriptions */
 string ephemerides_dir;
  /** No descriptions */
 string attitude_dir;

  /** No descriptions */
 ArchiveHandler *arc;

/** saves the total length in char of the archive dir -- i.e. containing the orbit number -- */
 int arc_dir_len;
   
};
}
#endif
