/***************************************************************************
                          processkiller.h  -  description
                             -------------------
    begin                : Wed Oct 18 2006
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

#ifndef PROCESSKILLER_H
#define PROCESSKILLER_H

#include "hertagbase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


/**
  *@author Francesco Lazzarotto
  */

class ProcessKiller : public HertagBase {
public: 
	ProcessKiller();
	ProcessKiller(const string &pn);  
	~ProcessKiller();
  /** No descriptions */
  string getProcessName();
  /** No descriptions */
  vector<int> getPIDs();
  /** No descriptions */
  void test();
  /** No descriptions */
  void killProcess(int a);
  /** No descriptions */
  void killall();
  /** No descriptions */
  void setProcessName(const string &pn);
  /** No descriptions */
  void killProcs();

  protected:
  string pname;
  vector<int> pids;
  
};

#endif
