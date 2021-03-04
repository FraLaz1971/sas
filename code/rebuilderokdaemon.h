/***************************************************************************
                          rebuilderokdaemon.h  -  description
                             -------------------
    begin                : Tue Apr 3 2007
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

#ifndef REBUILDEROKDAEMON_H
#define REBUILDEROKDAEMON_H

#include "okdaemon.h"


/**
  *@author Francesco Lazzarotto
  */
namespace SApipeline{
using namespace SApipeline;
class RebuilderOKDaemon : public OKDaemon  {
public: 
	RebuilderOKDaemon();
	~RebuilderOKDaemon();
  /** returns the contact number reading it from the filename of the arrived okfile */
  string getContactNumber();
};
}
#endif
