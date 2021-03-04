/***************************************************************************
 *   Copyright (C) 2007 by superagile team account   *
 *   agile@nibbio   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SAARCHIVEARCHIVESCANNER_H
#define SAARCHIVEARCHIVESCANNER_H


#include "archivehandler.h"
#include <map>
#include "math.h"

namespace SAarchive {

/**
	@author superagile team account <agile@nibbio.iasf-roma.inaf.it>
*/

using namespace std;

class ArchiveScanner : public ArchiveHandler
{
public:
    ArchiveScanner();
    ~ArchiveScanner();
    int process();
    void setBaseDir(const string &bd);
    void setOrbitInterval(int startorbit, int endorbit);
    void update();
    void retrieveDataCoverage(int startorbi, int endorbit);
    void readEventsCoverage(const string & evcovfname);
    void readEphCoverage(const string & ephcovfname);
    void readAttCoverage(const string & attcovfname);

protected:

	map<int, bool> Events; // 3905 L2 data files
	map<int, bool> Ephemeridies; // 3916 data files
	map<int, bool> Attitudes;// 3914 L2 data files
	int norbits; // n. of retrieved orbits for the given dataset
    int myfilen;
	string basedir;

};

}

#endif
