/***************************************************************************
                          datareducer.h  -  description
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

#ifndef DATAREDUCER_H
#define DATAREDUCER_H



#include "l1_9eventlist.h"
//#include "sadp_global.h"
#include "pipelinemodule.h"
#include "type1exception.h"
#include "type2exception.h"
#include "saexception.h"
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include "pipelinemodule.h"
/** \namespace SApipeline includes all modules needed to SA pipeline elaborations
*/
using namespace SApipeline;
using namespace SAExceptions;
using namespace std;
namespace SApipeline{

  /**
Class DataReducer implements the object performing data reduction operations on SA data
  *@author Francesco Lazzarotto
  */
class DataReducer : public PipelineModule {
public: 
	DataReducer();
	~DataReducer();
  /** No descriptions */
  int setParameters(char * parfilename);
  /** No descriptions */
  int setL1Data(char * datafilename);
  /** returns a L1_9 eventlist object */
  //L1_9Eventlist * getL1_9(int mode );
  int getL1_9_Batch(int mode);
  /** specific sadp module initialization */
  int init();
  /** No descriptions */
  void setDescription();
  /** No descriptions */
  void start();
  /** No descriptions */
  int executeOp2(int operand1, int operand2);
  /** No descriptions */
  int executeOp1(int operand1, int operand2);
  /** No descriptions */
  int executeInnerOp(int operand1, int operand2);
  /** launch stage0 via idl batch */
  void launchIDL_Batch();
  /** No descriptions */
  void launch(string & infile, string & outfile, vector<int> params);
  /** No descriptions */
  void setInputFilename(const string &fname, const string &mode);
  /** No descriptions */
  void setOutputDir(const string &od);  
  /** No descriptions */
  string getOutputDir();
  /** No descriptions */
  void createLaunchBatchScript();
  /** No descriptions */
  string getInputDataPath();
  /** No descriptions */
  void passOutputFile(const string &toutdir);
  /** No descriptions */
//  string getDefaultInputDir() ;
  /** No descriptions */
  string getInputFileName() ;
  /** No descriptions */
  void rmTempInputFiles();
  /** No descriptions */
  void announceDelivery();
  /** No descriptions */
  void prepareInputFile();
    /** No descriptions */
  void setInputDataPath(const string &idp);
  /** No descriptions */
  string getOldModeInputFileName();
  /** No descriptions */  
  void setOldModeInputFileName(const string &ifn);

  protected:
    
  string inputdatapath;
  
  string oldmodeinfile;
    
  private:

  
  public:
  
  SAexception e;
  
  Type1Exception e1;
  
  Type2Exception e2;
  
};
}
#endif
