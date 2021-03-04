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
#ifndef SAMONITOR_H
#define SAMONITOR_H

#include "hertagbase.h"
#include "systemconnector.h"
#include <math.h>
/**
	@author superagile team account <agile@nibbio>
*/

using namespace System;

class SAMonitor: public HertagBase {
public:
    SAMonitor();

    ~SAMonitor();
    void createSpectraMonitor();
    void createDetImageMonitor();
    void createLightCurveMonitor();
    void createSkyImageMonitor();
    void init();
    void createPlotMonitor(int nplot, vector<string> plots, ostream &os);
    void openOutputFile(const string &fn);
    void closeOutputFile();
    void printPageHead(ostream &os);
    void printPageTail(ostream &os);
    void printPageBody(ostream &os);
    void createChipSpectrumMonitor();
    void printStringOnPage(const string &s, ostream &os);
    void createPlotCell(string pn, ostream &os);
    void setPlotNumber(int pnn);
    void setPageName(const string &pna);
    void setPlotList(const string &pln);
    int extractPlotsNumber(const string &pnl);
    void createInputList(const string &dirnam, const string &title);
    void createPlotMonitor();
    void createImagingPlotsMonitor(const string &ipd);
    void setDir(const string &dir);
    void setPlotName(const string &pn);
    void prepare(const string &mdir, const string &mtype, const string &mpagefn);
    void createPlotMonitor(const string &mdir, const string &mtype,  const string &mpagefn);
    void createSAImagesIndex();
    void printImgIndexBody(ostream &os, const string &ts);
    string getContact();
    void retrieveContact();
    void setContact(const string &st);
    void setSA(bool val);

	protected:

	string hist0fn;
	string hist1fn;
	string hist2fn;
	string hist3fn;
	ofstream myos;

	int myplotn; // number of plots in the page
	vector<string> myplotv; // vector of plot file references
	string pagefn; // web page file name
	string plotname; // generic name of the plot in the page
	string Dir;
	SystemConnector syscon;
	string contact;
	string WebBaseDir;
	bool sapm;
};

#endif
