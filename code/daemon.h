/***************************************************************************
                          daemon.h  -  description
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

#ifndef DAEMON_H
#define DAEMON_H

#include "pipelinemodule.h"
#include <dirent.h>
#include "sasoahandler.h"
#include <exception>
#include <string>
#include "hertagbase.h"
#include "agilefilename.h"
#include <unistd.h>
#include "orbitrebuilder.h"

/**generic daemon utilities for experimental data processing pipelines
  *@author Francesco Lazzarotto
  */


namespace SApipeline {

using namespace SApipeline;
using namespace SAarchive;
using namespace std;

class Daemon : public PipelineModule  {
public: 
	Daemon();
	~Daemon();
};
}
#endif
