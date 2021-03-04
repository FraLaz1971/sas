/***************************************************************************
                          photonlistbuilder.h  -  description
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

#ifndef PHOTONLISTBUILDER_H
#define PHOTONLISTBUILDER_H


#include "pipelinemodule.h"

namespace SApipeline{

using namespace SApipeline;
/**
  class implementing the photonlist building stage of the SA pipeline
  *@author Francesco Lazzarotto
  */
class PhotonListBuilder : public PipelineModule {
/**
  class implementing the photonlist building stage of the SA pipeline
  *@author Francesco Lazzarotto
  */

  public: 
	PhotonListBuilder();
	~PhotonListBuilder();
  /** No descriptions */
  int init();
  /** No descriptions */
  void setDescription();
  /** No descriptions */
  void start();
  /** No descriptions */
  void launchIDL_Batch();
  /** No descriptions */
  void launch(string & infile, string & outfile, vector<int> params);
  /** No descriptions */
  void createLaunchBatchScript();
  /** No descriptions */
  void rmTempInputFiles();
    /** No descriptions */
  void passOutputFile(const string &toutdir);
  /** No descriptions */
  string getDefaultOutputDir();
  /** No descriptions */
  void announceDelivery();
  /** No descriptions */
  string getOutputFileName();
  /** No descriptions */
  //string getInputDataPath();
};
}
#endif
