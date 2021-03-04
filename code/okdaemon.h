/***************************************************************************
                          okdaemon.h  -  description
                             -------------------
    begin                : Tue Oct 10 2006
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

#ifndef OKDAEMON_H
#define OKDAEMON_H

#include <dirent.h>
#include "pipelinemodule.h"
#include "sasoahandler.h"
#include <exception>
#include <string>
#include "hertagbase.h"
#include "agilefilename.h"
#include <unistd.h>
#include "orbitrebuilder.h"

/**class that waits until on OK file
is present in a fixed directory
  *@author Francesco Lazzarotto
  */
namespace SApipeline {

using namespace SApipeline;
using namespace SAarchive;
using namespace std;

class OKDaemon: public PipelineModule {

public: 
	OKDaemon();
	~OKDaemon();
  /** No descriptions */
  void start();
  /** No descriptions */
  void setPipelineModule(PipelineModule *pipmod);
  /** No descriptions */
  bool okpresent();
  /** No descriptions */
  void testsetting();
  /** No descriptions */
  void setOKFileDir(const string &okdir);
  /** No descriptions */
  bool triggerPresent();
  /** No descriptions */
  bool isErrorFile(const string &ifn);
  /** No descriptions */
  bool isWarningFile(const string &ifn);
  /** No descriptions */
  bool isOKFile(const string &ifn);
  /** No descriptions */
  void setTriggerFileName(const string &tfn);
  /** No descriptions */
  void test();
  /** No descriptions */
  string getContactString(const string &oks);
  /** No descriptions */
  string getNewFileName();
  /** No descriptions */
  void setSasoaHandler(SasoaHandler *sh);
  /** No descriptions */
    void newtest();
  /** No descriptions */
    void syncRemoteOKfileDir();
  /** No descriptions */
    void asdc_test();
  /** No descriptions */
    void emiloop();
  /** No descriptions */
  
  protected:

  string okfiledir;

  string okfilename;

  PipelineModule pipemodule;
  
  PipelineModule *pipe;

  SasoaHandler *pipepointer;

  AGILEFileName afname;


  private:

  bool bval, b;

  exception e;
};
}
#endif
