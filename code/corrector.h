/***************************************************************************
                          corrector.h  -  description
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

#ifndef CORRECTOR_H
#define CORRECTOR_H

#include "safitshandler.h"
#include "pipelinemodule.h"

/**Generic table data corrector
  *@author Francesco Lazzarotto
  */
using namespace SApipeline;
namespace DataCorrection{

class Corrector : public PipelineModule  {
public: 
	Corrector();
	~Corrector();
    void writeTriggerFile();
    void prepare();
    string retrieveTrigEnvVar();
    void setASDC(bool val);
    protected:
    string CORR_INDIR;
    bool asdcflag;
    bool processed; 
};
}
#endif
