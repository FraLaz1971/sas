/***************************************************************************
                          samdimageplotter.h  -  description
                             -------------------
    begin                : Tue Aug 1 2006
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

#ifndef SAMDIMAGEPLOTTER_H
#define SAMDIMAGEPLOTTER_H

#include <saplotter.h>

/**Plot the SA Multi Detector Image
  *@author Francesco Lazzarotto
  */
namespace Graphics {
class SAMDImagePlotter : public SAPlotter  {
public: 
	SAMDImagePlotter();
	~SAMDImagePlotter();
  /** No descriptions */
  void setAxes();
  /** No descriptions */
  void save();
  /** No descriptions */
  void print();
  /** No descriptions */
  void plotLoaded();
  /** No descriptions */
  void plot(int regnum);
  /** No descriptions */
  void init();
  /** No descriptions */
  void stop();
  /** No descriptions */
  void start();
  /** No descriptions */
  void showData();
//  /** No descriptions */
//  void setData();
  /** No descriptions */
  void plotAll();
  /** No descriptions */
  void setDescription(const string &dsc);
  protected:

//  vector<>
};
}
#endif
