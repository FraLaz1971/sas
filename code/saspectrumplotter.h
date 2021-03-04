/***************************************************************************
                          saspectrumplotter.h  -  description
                             -------------------
    begin                : Wed May 17 2006
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

#ifndef SASPECTRUMPLOTTER_H
#define SASPECTRUMPLOTTER_H


/**
  *@author Francesco Lazzarotto
  */
#include "saplotter.h"
#include "gnuplot_base.h"
#include "gnuplot_pipe.h"
#include "gnuplot_tmpfile.h"

#include <string>
#include <vector>

using namespace std;
namespace Graphics  {
  using namespace Graphics;

class SASpectrumPlotter: public SAPlotter {
public: 
	SASpectrumPlotter();
	~SASpectrumPlotter();
  /** No descriptions */
  void print();
  /** No descriptions */
  void plot();
  /** No descriptions */
  void read(string filename);
  /** No descriptions */
  void createDefault();
  /** No descriptions */
  void stop();
  /** No descriptions */
  void start();
  /** No descriptions */
  void setDescription(const string &dsc);
  private:
};
}
#endif
