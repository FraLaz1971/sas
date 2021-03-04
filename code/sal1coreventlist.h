/***************************************************************************
                          sal1coreventlist  -  description
                             -------------------
    begin                : mer giu 20 2007
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
#ifndef SADATASAL1COREVENTLIST_H
#define SADATASAL1COREVENTLIST_H

#include "saeventlist.h"

namespace SAdata {

/**
	@author Francesco Lazzarotto <lazza@rm.iasf.cnr.it>
*/
class SAL1CorEventlist : public SAEventlist
{
public:
    SAL1CorEventlist();

    SAL1CorEventlist(const string &filename);

    ~SAL1CorEventlist();

    void readPacketsHDUHeader();

    void readEventsHDUHeader();

};

}

#endif
