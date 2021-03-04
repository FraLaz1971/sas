/***************************************************************************
                          sourcesextractor.h  -  description
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

#ifndef SOURCESEXTRACTOR_H
#define SOURCESEXTRACTOR_H


/**
  *@author Francesco Lazzarotto
  */
#include "pipelinemodule.h"
#include "agiledbconnector.h"
#include "filelist.h"
#include "sal3eventlist.h"
#include "orbitrebuilder.h"
#include "irospilot.h"
#include "irosmap.h"
#include <string>
#include <vector>


namespace SApipeline{
using namespace SApipeline;
using namespace SAExceptions;
using namespace DB;
using namespace std;
using namespace SAdata;
using namespace System;

class SourcesExtractor : public PipelineModule{
 friend class SasoaUserInterface;
public: 
	SourcesExtractor();
	~SourcesExtractor();

  /** No descriptions */
  int init();
    /** No descriptions */
  void setDescription();
  /** No descriptions */
  void start();
  /** No descriptions */
  void launch(string & infile, string & outfile, vector<int> params);
  /** No descriptions */
  void launchIDL_Batch();
  /** No descriptions */
  void deliverProducts();
  /** No descriptions */
  void announceDelivery();
  /** No descriptions */
  void launchAttitudeCorrection();
  /** No descriptions */
  void createLaunchBatchScript();
  /** No descriptions */
  void createAttitudeBatchScript();
  /** No descriptions */
  void passOutputFile(const string &toutdir);
  /** No descriptions */
  void setDefaultOutputDir();
  /** No descriptions */
  void setOutputDir(const string &od);
  /** No descriptions */
  string getProductPath();
  /** No descriptions */
  void setProductPath(const string &prodp);
  /** No descriptions */
  void launchIrosMapBuilder();
  /** No descriptions */
  void launchIros();
  /** No descriptions */
 void launchAttitudeCorrection(int cmin, int cmax);
  /** No descriptions */
 void launchAttitudeCorrection(double tstart, double tstop);
  /** No descriptions */
  void createIrosBatch(byte det);
  /** No descriptions */
  void createPointingBatch();
  /** No descriptions */
  void rmTempInputFiles();
  /** No descriptions */
  void launchIros(int det);
  /** No descriptions */
  void saveIrosMap();
  /** No descriptions */
  string getAbsoluteInputFileName();
  /** No descriptions */
  void setIrosMapFileName(const string &fn);
  /** No descriptions */
  string getIrosMapFileName();
  /** No descriptions */
  void showIrosBatch();
  /** No descriptions */
  void showPointingBatch();
  /** No descriptions */
  void printIrosBatch(ostream &os);
  /** No descriptions */
  void printPointingBatch(ostream &os);
  /** No descriptions */
  void createIrosIDLBatch(const string &fn);
  /** No descriptions */
  void setIROS_IDLBatchFileName(const string &fn);
  /** No descriptions */
  string getIROS_IDLBatchFileName();
  /** No descriptions */
  string getIrosLogFileName();
  /** No descriptions */
  string retrieveIrosMapFilename();
  /** No descriptions */
  void createPointingBatch(const string &templ3);
  /** No descriptions */
  void setIrosBaseDir(const string &ibd);
  /** No descriptions */
  string getIrosBaseDir();
  /** No descriptions */
  void setDefault();
  /** No descriptions */
  void passIrosMap();
  /** No descriptions */
  string getDefaultInputDir();
  /** No descriptions */
  string getInputFileName();
  /** No descriptions */
  void launchIros(const string &l3file, const string &mapfilename);
  /** No descriptions */
  void launchIros(const string &mapfilename);
  /** No descriptions */
  void launchIrosMDMapBuilder();
  /** No descriptions */
  void createExposureIDLBatch(const string &batchfilename, const string &cardfilename);
 /** No descriptions */
  void createIrosMapBuilder(const string & inL3file, const string &outMDfile, const string &gtifile, int emin, int emax);
 /** No descriptions */
  void createDefaultAttitudeDatacard(const string &l2f, const string &atf, const string &l3f);
  /** No descriptions */
  void launchIros(const string &mapdir, const string &pilotfilename, const string & pointpilotfilename);
  /** No descriptions */
  void launchIrosMapBuilder(bool debug);
  /** No descriptions */
  void createExposureBatch();
  /** No descriptions */
  void createAttitudeDatacard(const string &dcfn, const string &l2f, const string &atf);
  /** No descriptions */
  void	launchIrosV4(const string &inputL2Filename, const string &inputAttFilename, const string &outputL3Filename);
  /** No descriptions */
  void createExposureDatacard();
  /** No descriptions */
  void createAttitudeDatacard(const string &eidatacard, const string &l2filename, int cmin, int cmax);
  /** No descriptions */
  void launchExposureIDLBatch();
  /** No descriptions */
  void launchExposure();
  /** No descriptions */
  void launchSaga();
  /** No descriptions */
  void createSagaBatch();
  /** No descriptions */
  void createSapoiLaunchBatch();
  /** No descriptions */
  void launchSapoiCreator();
  /** No descriptions */
  void createSapoiDatacard();
  /** No descriptions */
  void createSagaIDLBatch();
  /** No descriptions */
  void createAttitudeDatacard();
  /** No descriptions */
  void createAttitudeDatacard(const string &dcfn, const string &l2f, const string &atf, const string &l3fn);
  /** No descriptions */
  void filterAllGTI(const string &gtifn);
  /** No descriptions */
  void createFilteredL3List();
  /** No descriptions */
  void deliverDetImages();
  /** No descriptions */
  void createIrosBatch(byte det, const string &batchname, const string &mdinputfile);
  /** No descriptions */
  void passIrosMap(const string &mapfilename, const string &destdir);
  /** No descriptions */
  void createExposureDatacard(const string &cardoutfilename, const string &sapoifilename, const string &ephfilename);
  /** No descriptions */
  void launchAttitude(const string &inputL2Filename, const string &inputAttFilename, const string &outputL3Filename);
  /** No descriptions */
  void createSapoiDatacard(const string &cardoutfilename, const string &sapoifilename,int cmin, int cmax);
    string getAttitudeFileName();
  /** */
  IrosPilot irospilot;  
  protected:
  /** No descriptions */
  SAL3Eventlist sal3;
  /** No descriptions */
    /** No descriptions */
  string fitsfilename;
  /** No descriptions */
  stringstream ss;
  /** No descriptions */
  IrosMap *im;  
   /** */
  string imf1;
   /** */
  string imf2;
   /** */
  string irosmapfilename;
   /** */
  string iroslogfilename;  
   /** */
  string iros_idl_batch_fn;
  /** */
  string iros_base_dir;
    /** */
  string attitude_base_dir;
    /** */
  FileList *outfilelist;   
};
}
#endif
