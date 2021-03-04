/***************************************************************************
                          systemconnector.h  -  description
                             -------------------
    begin                : Fri Mar 30 2007
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

#ifndef SYSTEMCONNECTOR_H
#define SYSTEMCONNECTOR_H

#include <connector.h>
#include <stdio.h>
#include "stdlib.h"
#include <unistd.h>
#include "timer.h"
#include <iostream>



/**
  *@author Francesco Lazzarotto
  */
namespace System {
  using namespace std;
  
class SystemConnector : public Connector  {
public: 
	SystemConnector();
	~SystemConnector();
  /** No descriptions */
  string getEnvVar(const string &evn);

  void setEnvVar(const string & evn, const string &vv, int ow);

  void exportEnvVar(const string & evn, const string &vv);
  /** No descriptions */
  void test();
  /** No descriptions */
  void setShellMode(bool sm);
  /** No descriptions */
  string retrieveEnvVar();
  /** No descriptions */                                                      
  void saveEnvVar(const string &evn);
  /** No descriptions */
  void execCommand(const string &c);
  /** exec system (i.e. unix shell)  command and return as result an array of strings */
  vector<string> dumpCommand(const string &c);
  /** No descriptions */
  vector<string> getCommandResult(const string & dumpfile);
  /** No descriptions */
  void saveCommandResult(const string &command, const string & dumpfile);
  /** No descriptions */
  void testCommand();
  
  protected:

  const char *t ;
  
  char *ee;

  bool shell;

  vector<string> results, results1;

};
}
#endif
