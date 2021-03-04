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
#include "archivescanner.h"

namespace SAarchive {

ArchiveScanner::ArchiveScanner()
 : ArchiveHandler()
{
	myfilen = 0;
	norbits = 0;
}


ArchiveScanner::~ArchiveScanner()
{
}


}


/*!
    \fn SAarchive::ArchiveScanner::process()
 */
int SAarchive::ArchiveScanner::process()
{
   if (verbose) cout << "do something" << endl;
   return status;
}


/*!
    \fn SAarchive::ArchiveScanner::setBaseDir(const string &bd)
 */
void SAarchive::ArchiveScanner::setBaseDir(const string &bd)
{
    basedir = bd;
}


/*!
    \fn SAarchive::ArchiveScanner::setOrbitInterval(int startorbit, endorbit)
 */
void SAarchive::ArchiveScanner::setOrbitInterval(int startorbit, int endorbit)
{
    norbits = endorbit - startorbit;
}


/*!
    \fn SAarchive::ArchiveScanner::update()
 */
void SAarchive::ArchiveScanner::update()
{
    norbits = Events.size(); 
}


/*!
    \fn SAarchive::ArchiveScanner::retrieveDataCoverage(int startorbi, int endorbit)
 */
void SAarchive::ArchiveScanner::retrieveDataCoverage(int startorbi, int endorbit)
{
    /// @todo implement me
}


/*!
    \fn SAarchive::ArchiveScanner::readEventsCoverage(const string & evfname)
 */
void SAarchive::ArchiveScanner::readEventsCoverage(const string & evcovfname)
{
    ifstream ninfile;
	tempstring = "";
	norbits = 0;	Events.clear();
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (evcovfname.c_str(), ifstream::in);
        while(!ninfile.eof()){
 		   ninfile >> tempstring;			   
		   tempstring = tempstring.substr(tempstring.find_last_of("/")+1);filenamer.setFileName(tempstring);
           cout << "read " << tempstring << " " << myfilen++ << " extracted contact " << filenamer.getContact() << " " << filenamer.getContactNumber() << endl;
       cout << "read " << tempstring << " " << myfilen++ << endl;
		}
		} catch (const exception &e){
			cerr << "exception in reading Events coverage file (L2 data 3905 TM)" << e.what() << endl;
		}
}


/*!
    \fn SAarchive::ArchiveScanner::retrieveEphCoverage(const string & ephcovfname)
 */
void SAarchive::ArchiveScanner::readEphCoverage(const string & ephcovfname)
{
    ifstream ninfile;
	tempstring = "";
	norbits = 0;	Ephemeridies.clear();
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (ephcovfname.c_str(), ifstream::in);
        	while(!ninfile.eof()){
 		   ninfile >> tempstring;			   
			tempstring = tempstring.substr(tempstring.find_last_of("/")+1);filenamer.setFileName(tempstring); 
           cout << "read " << tempstring << " " << myfilen++ << " extracted contact " << filenamer.getContact() << " " << filenamer.getContactNumber() << endl;
           		cout << "read " << tempstring << " " << myfilen++ << endl;
			}
		} catch (const exception &e){
			cerr << "exception in reading Ephemeridies coverage file (3916 TM)" << e.what() << endl;
		}

}

/*!
    \fn SAarchive::ArchiveScanner::retrieveAttCoverage(const string & ephcovfname)
 */
void SAarchive::ArchiveScanner::readAttCoverage(const string & attcovfname)
{
    ifstream ninfile;
	tempstring = "";
	norbits = 0;	Attitudes.clear();
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (attcovfname.c_str(), ifstream::in);
        while(!ninfile.eof()){
 		   ninfile >> tempstring;			   
		   tempstring = tempstring.substr(tempstring.find_last_of("/")+1);filenamer.setFileName(tempstring);	
           cout << "read " << tempstring << " " << myfilen++ << " extracted contact " << filenamer.getContact() << " " << filenamer.getContactNumber() <<  endl;
	  }
		} catch (const exception &e){
			cerr << "exception in reading Ephemeridies coverage file (3916 TM)" << e.what() << endl;
		}
}
