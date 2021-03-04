/***************************************************************************
                          saimageplotter.h  -  description
                             -------------------
    begin                : Wed Jun 21 2006
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

#ifndef SAIMAGEPLOTTER_H
#define SAIMAGEPLOTTER_H

#include "saplotter.h"
#include "gnuplot_base.h"
#include "gnuplot_pipe.h"
#include "gnuplot_tmpfile.h"

#include <string>
#include <vector>


/**
  *@author Francesco Lazzarotto
  */
using namespace std;
namespace Graphics  {
using namespace Graphics;

class SAImagePlotter: public  SAPlotter {
public: 
	SAImagePlotter();
	~SAImagePlotter();
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
  /** No descriptions */
  void setImageType(int imt);
  /** No descriptions */
  int getImageType();
    void print(const string &plotdir);

  private:

  unsigned int imgdim;

  int imgtype;

};
}
#endif
