/***************************************************************************
                          sadetimageplotter.h  -  description
                             -------------------
    begin                : Wed Jul 26 2006
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

#ifndef SADETIMAGEPLOTTER_H
#define SADETIMAGEPLOTTER_H

#include <saplotter.h>

/**
  *@author Francesco Lazzarotto
  */
namespace Graphics{
  using namespace Graphics;
class SADetImagePlotter : public SAPlotter  {
public: 
	SADetImagePlotter();
	~SADetImagePlotter();
};
}
#endif
