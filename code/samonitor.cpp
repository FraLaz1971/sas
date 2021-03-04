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
#include "samonitor.h"

SAMonitor::SAMonitor()
{
	init();
}


SAMonitor::~SAMonitor()
{
}




/*!
    \fn SAMonitor::createSpectraMonitor()
 */
void SAMonitor::createSpectraMonitor()
{
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
outfile.open ("SAMonitor.php", ofstream::out | ofstream::trunc);
outfile << tempstring << endl;

outfile << " <!--<!DOCTYPE HTML PUBLIC \"-//w3c//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">-->" << endl;

outfile << "<HTML>" << endl;
outfile << "<HEAD>" << endl;
outfile << "</HEAD>" << endl;
outfile << "<BODY>" << endl;

outfile << "<div align=\"center\"><h3>SAMonitor</h3></div>" << endl;
outfile << "<?php echo \"esempio php\n \";  " << endl;
outfile << "?>" << endl;
outfile << "<TABLE frame=\"above\" align=\"center\" cellpadding=\"10%\" border=\"2%\" cellspacing=\"2\" width=\"80%\">" << endl;
outfile << "<tbody>" << endl;
outfile << "<tr>" << endl;
outfile << "      <td><A href=\""<<hist0fn<<"\"><IMG src=\""<<hist0fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Detector Image</A></td> \" "<< endl;
outfile << "      <td><A href=\""<<hist1fn<<"\"><IMG src=\""<<hist1fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Detector Image</A></td> \" "<< endl;
outfile << "</tr>" << endl;
outfile << "<tr>" << endl;
outfile << "      <td><A href=\""<<hist2fn<<"\"><IMG src=\""<<hist2fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Detector Image</A></td> \" "<< endl;
outfile << "      <td><A href=\""<<hist3fn<<"\"><IMG src=\""<<hist3fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Detector Image</A></td> \" "<< endl;
outfile << "</tr>" << endl;
outfile << "</tbody>" << endl;
outfile << "</TABLE>" << endl;
outfile << "</BODY>" << endl;
outfile << "</HTML>" << endl;

outfile <<  endl;
outfile.close();  
}


/*!
    \fn SAMonitor::createLightCurveMonitor()
 */
void SAMonitor::createLightCurveMonitor()
{
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
outfile.open ("SAMonitor.php", ofstream::out | ofstream::trunc);
outfile << tempstring << endl;

outfile << " <!--<!DOCTYPE HTML PUBLIC \"-//w3c//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">-->" << endl;

outfile << "<HTML>" << endl;
outfile << "<HEAD>" << endl;
outfile << "</HEAD>" << endl;
outfile << "<BODY>" << endl;

outfile << "<div align=\"center\"><h3>SAMonitor</h3></div>" << endl;
outfile << "<?php echo \"esempio php\n \";  " << endl;
outfile << "?>" << endl;
outfile << "<TABLE frame=\"above\" align=\"center\" cellpadding=\"4\" border=\"2%\" cellspacing=\"2\" width=\"800%\">\"" << endl;
outfile << "<tbody>" << endl;
outfile << "<tr>" << endl;
outfile << "      <td><A href=\""<<hist0fn<<"\"><IMG src=\""<<hist0fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Light Curve</A></td> \" "<< endl;
outfile << "      <td><A href=\""<<hist1fn<<"\"><IMG src=\""<<hist1fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 1 Light Curve</A></td> \" "<< endl;
outfile << "</tr>" << endl;
outfile << "<tr>" << endl;
outfile << "      <td><A href=\""<<hist2fn<<"\"><IMG src=\""<<hist2fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 2 Light Curve</A></td> \" "<< endl;
outfile << "      <td><A href=\""<<hist3fn<<"\"><IMG src=\""<<hist3fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 3 Light Curve</A></td> \" "<< endl;
outfile << "</tr>" << endl;
outfile << "</tbody>" << endl;
outfile << "</TABLE>" << endl;
outfile << "</BODY>" << endl;
outfile << "</HTML>" << endl;
outfile <<  endl;
outfile.close();  
}


/*!
    \fn SAMonitor::createDetImageMonitor()
 */
void SAMonitor::createDetImageMonitor()
{
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
outfile.open ("SAMonitor.php", ofstream::out | ofstream::trunc);
outfile << tempstring << endl;

outfile << " <!--<!DOCTYPE HTML PUBLIC \"-//w3c//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">-->" << endl;

outfile << "<HTML>" << endl;
outfile << "<HEAD>" << endl;
outfile << "</HEAD>" << endl;
outfile << "<BODY>" << endl;

outfile << "<div align=\"center\"><h3>SAMonitor " << contact << "</h3></div>" << endl;
outfile << "<?php echo \"esempio php\n \";  " << endl;
outfile << "?>" << endl;
outfile << "<TABLE frame=\"above\" align=\"center\" cellpadding=\"4\" border=\"2%\" cellspacing=\"2\" width=\"800%\">\"" << endl;
outfile << "<tbody>" << endl;
outfile << "<tr>" << endl;
outfile << "      <td><A href=\""<<hist0fn<<"\"><IMG src=\""<<hist0fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Detector Image</A></td> \" "<< endl;
outfile << "      <td><A href=\""<<hist1fn<<"\"><IMG src=\""<<hist1fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 1 Detector Image</A></td> \" "<< endl;
outfile << "</tr>" << endl;
outfile << "<tr>" << endl;
outfile << "      <td><A href=\""<<hist2fn<<"\"><IMG src=\""<<hist2fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 2 Detector Image</A></td> \" "<< endl;
outfile << "      <td><A href=\""<<hist3fn<<"\"><IMG src=\""<<hist3fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 3 Detector Image</A></td> \" "<< endl;
outfile << "</tr>" << endl;
outfile << "</tbody>" << endl;
outfile << "</TABLE>" << endl;
outfile << "</BODY>" << endl;
outfile << "</HTML>" << endl;
outfile <<  endl;
outfile.close();  
}


/*!
    \fn SAMonitor::createSkyImageMonitor()
 */
void SAMonitor::createSkyImageMonitor()
{
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
outfile.open ("SAMonitor.php", ofstream::out | ofstream::trunc);
outfile << tempstring << endl;

outfile << " <!--<!DOCTYPE HTML PUBLIC \"-//w3c//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">-->" << endl;

outfile << "<HTML>" << endl;
outfile << "<HEAD>" << endl;
outfile << "</HEAD>" << endl;
outfile << "<BODY>" << endl;

outfile << "<div align=\"center\"><h3>SAMonitor</h3></div>" << endl;
outfile << "<?php echo \"esempio php\n \";  " << endl;
outfile << "?>" << endl;
outfile << "<TABLE frame=\"above\" align=\"center\" cellpadding=\"4\" border=\"2%\" cellspacing=\"2\" width=\"80%\">\"" << endl;
outfile << "<tbody>" << endl;
outfile << "<tr>" << endl;
outfile << "      <td><A href=\""<<hist0fn<<"\"><IMG src=\""<<hist0fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Sky Image</A></td> \" "<< endl;
outfile << "      <td><A href=\""<<hist1fn<<"\"><IMG src=\""<<hist1fn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">Det 0 Sky Image</A></td> \" "<< endl;
outfile << "</tbody>" << endl;
outfile << "</TABLE>" << endl;
outfile << "</BODY>" << endl;
outfile << "</HTML>" << endl;

outfile <<  endl;
outfile.close();  
}


/*!
    \fn SAMonitor::init()
 */
void SAMonitor::init()
{
	hist0fn = "spettroD0_X_7.png";
	hist1fn = "spettroD0_X_7.png";
	hist2fn = "spettroD0_X_7.png";
	hist3fn = "spettroD0_X_7.png";
	myplotn = 4;
	pagefn = "contact_histograms.html";
	Dir = "";
	WebBaseDir = "/home/agile/public_html";
	sapm = false;
}


/*!
    \fn SAMonitor::createPlotMonitor(int nplot, vector<string> plots, ostream &os)
 */
void SAMonitor::createPlotMonitor(int nplot, vector<string> plots, ostream &os)
{

	double side = ceil(sqrt(double(nplot)));
	os << "<TABLE frame=\"above\" align=\"center\" cellpadding=\"4\" border=\"2%\" cellspacing=\"2\" width=\"100%\">" << endl;
	os << "<tbody>" << endl;
    
	 for(k=0; k<side; k++){
		os << "<tr>" << endl;

		// print row
			for(j=0; j<side; j++){
		os << "<td>" << endl;
				// print raw cell
		if (((k*side)+j)<nplot) createPlotCell(plots[(k*side)+j], os);
//		os << plots[(k*side)+j];

		os << "</td>" << endl;
				
			}
		os << "</tr>" << endl;

	 }
	// print last raws
	/*	int nnp = side*side;
		side = floor(sqrt(nplot-nnp));
		for(j=side*side; j<nplot; j++){
			os << "<td>" << endl;
				// print raw cell
			createPlotCell(plots[j], os);

			os << "</td>" << endl;
				
			}*/

	os << "</tbody>" << endl;
	os << "</TABLE>" << endl;
}


/*!
    \fn SAMonitor::openOutputFile()
 */
void SAMonitor::openOutputFile(const string &fn)
{
	myos.setf(ios::fixed,ios::floatfield);
	myos.open (fn.c_str(), ofstream::out | ofstream::trunc);
	myos << tempstring << endl;
}


/*!
    \fn SAMonitor::closeOutputFile()
 */
void SAMonitor::closeOutputFile()
{
 myos <<  endl;
 myos.close();  
}


/*!
    \fn SAMonitor::printPageHead()
 */
void SAMonitor::printPageHead(ostream &os)
{
  os << " <!--<!DOCTYPE HTML PUBLIC \"-//w3c//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">-->" << endl;

os << "<HTML>" << endl;
os << "<HEAD>" << endl;
os << "</HEAD>" << endl;
}


/*!
    \fn SAMonitor::printPageTail()
 */
void SAMonitor::printPageTail(ostream &os)
{
  os << "</HTML>" << endl;
}


/*!
    \fn SAMonitor::printPageBody(ostream &os)
 */
void SAMonitor::printPageBody(ostream &os)
{
  os << "<BODY>" << endl;
  os << "<div align=\"center\"><h3>SAMonitor " << contact << "</h3></div>" << endl;
  createPlotMonitor(myplotn, myplotv, os);
  os << "</BODY>" << endl;
}


/*!
    \fn SAMonitor::createChipSpectrumMonitor()
 */
void SAMonitor::createChipSpectrumMonitor()
{
	ofstream outfile;
	outfile.setf(ios::fixed,ios::floatfield);
	try{
		outfile.open (pagefn.c_str() , ofstream::out | ofstream::trunc);
		printPageHead(outfile);
		printPageBody(outfile);
		printPageTail(outfile);
		outfile.close();
	} catch (const exception &e){
		cerr << "error in creating the web page "<< e.what() << endl;
	}
}


/*!
    \fn SAMonitor::printStringOnPage(const string &s)
 */
void SAMonitor::printStringOnPage(const string &s, ostream &os)
{
	os << s << endl;
}

/*!
    \fn SAMonitor::createPlotCell(string pn, ostream &os)
 */
void SAMonitor::createPlotCell(string pn, ostream &os)
{
    os << "<A href=\""<<pn<<"\"><IMG src=\""<<pn<<"\" alter = \"img1\" width=\"80%\" align=\"left\" border=\"0\">"<<pn<<"</A>";
}


/*!
    \fn SAMonitor::setPageName(const string &pna)
 */
void SAMonitor::setPageName(const string &pna)
{
    pagefn = pna;
}


/*!
    \fn SAMonitor::setPlotNumber(int pnn)
 */
void SAMonitor::setPlotNumber(int pnn)
{
    myplotn = pnn;
}


/*!
    \fn SAMonitor::setPlotList()
	set the list of plot files to be inserted in the monitor web page
 */
void SAMonitor::setPlotList(const string &pln)
{
    ifstream ninfile;   tempstring = "";
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (pln.c_str(), ifstream::in);
        while(!ninfile.eof()){
		   ninfile >> tempstring;	
           cout << "SAMonitor::setPlotList() read " << tempstring << endl;
		   myplotv.push_back(tempstring);
        }
      } // close try
      catch (ifstream::failure e) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      }

}


/*!
    \fn SAMonitor::extractPlotsNumber()
 */
int SAMonitor::extractPlotsNumber(const string &pnl)
{
    ifstream ninfile;
    //char buf[256]; // read lines of maximun 256 characters
    //int mlinelen = 256;
	tempstring = "";
	myplotn = 0;	myplotv.clear();
    ninfile.exceptions (ifstream::eofbit | ifstream::failbit | ifstream::badbit );
      try {
        ninfile.open (pnl.c_str(), ifstream::in);
        while(!ninfile.eof()){
 		   ninfile >> tempstring;	
           cout << "read " << tempstring << " " << myplotn++ << endl;
			string sb("/");
     	   string h = tempstring.substr(tempstring.find_last_of(sb)+1, tempstring.size()-tempstring.find_last_of(sb));
			if (!sapm) {
				h = Dir+"/"+h;
			} else {
//				h = tempstring;
			} 
		   myplotv.push_back(h);
        }
      } // close try
      catch (ifstream::failure e) {
         if (verbose) cout << "Exception opening/writing file"<< endl;
      }
	return myplotn;
}


/*!
    \fn SAMonitor::createInputList()
 */
void SAMonitor::createInputList(const string &dirnam, const string &title)
{
    tempstring = "./prepare_input.sh "+dirnam+" "+title;
	syscon.execCommand(tempstring);
}


/*!
    \fn SAMonitor::createPlotMonitor(const string &type)
 */
void SAMonitor::createPlotMonitor()
{
	ofstream outfile;
	outfile.setf(ios::fixed,ios::floatfield);
	try{
		outfile.open (pagefn.c_str() , ofstream::out | ofstream::trunc);
		printPageHead(outfile);
		printPageBody(outfile);
		printPageTail(outfile);
		outfile.close();
	} catch (const exception &e){
		cerr << "error in creating the web page "<< e.what() << endl;
	}
}


/*!
    \fn SAMonitor::createImagingPlotsMonitor()
 */
void SAMonitor::createImagingPlotsMonitor(const string &ipd)
{	
	setDir(ipd);
	retrieveContact();
//	string t = "/home/agile/public_html/"+contact;
//	string h = "mkdir "+t; 
//	cout << "string = " << h << endl;
//	system(h.c_str()); 
	tempstring2 = "DetImg";
	tempstring3 = tempstring2 + ".html";
	tempstring = ipd+ "/"+tempstring2; //	//
	prepare(tempstring, tempstring2, tempstring3);
    createPlotMonitor();
	tempstring2 = "MDImg";
	tempstring3 = tempstring2 + ".html";
	tempstring = ipd+ "/"+tempstring2; //	//
	prepare(tempstring, tempstring2, tempstring3);
    createPlotMonitor();
	tempstring2 = "Pointing";
	tempstring3 = tempstring2 + ".html";
	tempstring = ipd+ "/"+tempstring2; //	//
	prepare(tempstring, tempstring2, tempstring3);
    createPlotMonitor();
	//
}


/*!
    \fn SAMonitor::setDir(const string &dir)
 */
void SAMonitor::setDir(const string &dir)
{
    Dir = dir;
}


/*!
    \fn SAMonitor::setPlotName(const string &pn)
 */
void SAMonitor::setPlotName(const string &pn)
{
    plotname = pn;
}


/*!
    \fn SAMonitor::prepare(const string &dir, const string &type, const string &pagefn)
 */
void SAMonitor::prepare(const string &mdir, const string &mtype, const string &mpagefn)
{
try{
 string dir(mdir); // directory name to scan
 string plotname(mtype); //
 string str = dir+"_"+plotname+".txt";
 string pagename = dir+"/"+mpagefn; 
 createInputList(dir, plotname);
 cout << "SAMonitor::prepare() reading file "<< str << endl;
 int pl = extractPlotsNumber(str);
 setPageName(pagename);
 setPlotNumber(pl);
} 	catch(const SAexception &se){
	cerr << "SAexception " << se.getMsg() << endl;
}	catch(const exception &e){
	cerr << "std::exception " << e.what() << endl;
}	catch(...){
	cerr << "generic exception "  << endl;
}
}


/*!
    \fn SAMonitor::createPlotMonitor(const string &dir, const string &type,  const string &pagefn)
 */
void SAMonitor::createPlotMonitor(const string &mdir, const string &mtype,  const string &mpagefn)
{
	prepare(mdir, mtype, mpagefn);
	createPlotMonitor();
}


/*!
    \fn SAMonitor::createSAImagesIndex()
 */
void SAMonitor::createSAImagesIndex()
{
	string pagefn = Dir+"/index.html"; string hh = "";
	cout << "page index "<< pagefn << endl;
	ofstream outfile;
	outfile.setf(ios::fixed,ios::floatfield);
	try{
		outfile.open (pagefn.c_str() , ofstream::out | ofstream::trunc);
		printPageHead(outfile);
		printImgIndexBody(outfile, hh);
		printPageTail(outfile);
		outfile.close();
	} catch (const exception &e){
		cerr << "error in creating the web page "<< e.what() << endl;
	}}


/*!
    \fn SAMonitor::printImgIndexBody()
 */
void SAMonitor::printImgIndexBody(ostream &os, const string &ts)
{
  //string ts1 = ts;
  string ts1;
  os << "<BODY>" << endl;
  os << "<div align=\"center\"><h3>SA Image Monitor contact "<<contact<<"</h3></div>" << endl;
  os << "<div align=\"center\">" << endl;
		os << "<p>" << endl;

	os << "<TABLE frame=\"above\" align=\"center\" cellpadding=\"4\" border=\"2%\" cellspacing=\"2\" width=\"70%\">" << endl;
	os << "<tbody>" << endl;
		os << "<tr>" << endl;
		os << "</tr>" << endl;

		os << "<tr>" << endl;
 		os << "<td align=\"center\">" << endl;
		   ts1 = "DetImg";

    	os << "<A href=\""<<ts1<<"/"<<"DetImg.html\"> Detector Images  </A>"<< endl;
	
		os << "</tr>" << endl;
 		os << "</td>" << endl;


	os << "<tr>" << endl;
 		os << "<td align=\"center\" >" << endl;
       ts1 = "MDImg";
       os << "<A href=\""<<ts1<<"/"<<"MDImg.html\"> Multi Detector Images  </A>";
		os << "</td>" << endl;
		os << "</tr>" << endl;
	os << "<tr>" << endl;
		os << "<td align=\"center\" >" << endl;
  		ts1 = "Pointing";
    	os << "<A href=\""<<ts1<<"/"<<"Pointing.html\"> Pointing Histograms  </A>";
		os << "</td>" << endl;

		os << "<tr>" << endl;
		os << "</tr>" << endl;
		os << "</tbody>" << endl;
		os << "</TABLE>" << endl; 
  //createPlotMonitor(myplotn, myplotv, os);
  os << "</div>" << endl;
  os << "</BODY>" << endl;
}


/*!
    \fn SAMonitor::getContact()
 */
string SAMonitor::getContact()
{
	return contact;
}


/*!
    \fn SAMonitor::setContact()
 */
void SAMonitor::setContact(const string &st)
{
    contact = st;
}


/*!
    \fn SAMonitor::retrieveContact()
	retrieve contact number from directory name 
 */
void SAMonitor::retrieveContact()
{
	//int k = Dir.find_first_of("_");
	string p("_"); string sb("/");
	cout << "sta "<< Dir.find_last_of(sb) << endl;
	string h = Dir.substr(Dir.find_last_of(sb)+1, Dir.size()-Dir.find_last_of(sb));
	cout << "h ="<< h << endl;
	tempstring = h.substr(h.find_first_of(p)+1, h.size()-h.find_first_of(p));
	int i = tempstring.find_first_of(p);
    contact = h.substr(h.find_first_of(p)+1, i);
	cout << "SAMonitor::retrieveContact() contact = " << contact << endl;
}


/*!
    \fn SAMonitor::setSA(bool val)
 */
void SAMonitor::setSA(bool val)
{
    sapm = val;
}
/*	os << "<TABLE frame=\"above\" align=\"center\" cellpadding=\"4\" border=\"2%\" cellspacing=\"2\" width=\"100%\">" << endl;
	os << "<tbody>" << endl;
		os << "<tr>" << endl;

		os << "<td>" << endl;
//		os << plots[(k*side)+j];
		os << "</td>" << endl;
		os << "</tr>" << endl;
	os << "</tbody>" << endl;
	os << "</TABLE>" << endl;

*/