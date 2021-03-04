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
#include "sal1coreventlist.h"

namespace SAdata {

SAL1CorEventlist::SAL1CorEventlist()
 : SAEventlist()
{
}

SAL1CorEventlist::SAL1CorEventlist(const string &filename)
 : SAEventlist()
{
	infile = filename;
}

SAL1CorEventlist::~SAL1CorEventlist()
{
}


}


/*!
    \fn SAdata::SAL1CorEventlist::readPacketHDUHeader()
 */
void SAdata::SAL1CorEventlist::readPacketsHDUHeader()
{
    /// @todo implement me
}


/*!
    \fn SAdata::SAL1CorEventlist::readEventsHDUHeader()
 */
void SAdata::SAL1CorEventlist::readEventsHDUHeader()
{
    /// @todo implement me
}
