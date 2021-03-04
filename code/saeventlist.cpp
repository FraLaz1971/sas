/***************************************************************************
                          saeventlist.cpp  -  description
                             -------------------
    begin                : Mon Jun 19 2006
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

#include "saeventlist.h"
namespace SAdata{

SAEventlist::SAEventlist(){
  init();
}

SAEventlist::~SAEventlist(){
}
void SAEventlist::setDefault(){}
void SAEventlist::init(){
    verbose = false;
	if (verbose) cout << "executing SAEventlist::init()" << endl;
	plot_term = "post";
    debug = false;
	exposure = 0.;
	success = false;
	products_dir = "";
}
}/** No descriptions */
void SAdata::SAEventlist::read(const string &infilename){
	if (verbose) cout << "reading eventlist file " << infilename << endl;
	sfh = new SAFitsHandler(infilename);
	sfh->openInputFile();
/*
try
{
         const string EVENTS("EVENTS");

         // read a particular HDU within the file. This call reads just the header
         // information from EVENTS

         std::auto_ptr<FITS> pInfile(new FITS(infilename,Read,EVENTS));

         // define a reference for clarity.

         ExtHDU& table = pInfile->extension(EVENTS);

         // read all the keywords, excluding those associated with columns.

         table.readAllKeys();
         // print the result.

         std::cout << table << std::endl;
 }
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAEventlist::read() function \n" ;
}
*/
}
/** No descriptions */
void SAdata::SAEventlist::save(const string &outfilename){
}
/** No descriptions */
unsigned long int SAdata::SAEventlist::getDim(){
return dim;
}
/** No descriptions */
void SAdata::SAEventlist::setDim(unsigned long int dm){
  dim = dm;
}
/** No descriptions */
void SAdata::SAEventlist::setVerbose(bool val){
  verbose = val;
}
/** No descriptions */
void SAdata::SAEventlist::setDebug(bool bval){
  debug = bval;
}


/*!
    \fn SAdata::SAEventlist::setTstart(double tst)
 */
void SAdata::SAEventlist::setTstart(double tst)
{
	tstart = tst;
}


/*!
    \fn SAdata::SAEventlist::setTstop(double tsp)
 */
void SAdata::SAEventlist::setTstop(double tsp)
{
    tstop = tsp;
}

/*!
    \fn SAdata::SAEventlist::getTstart()
 */
double SAdata::SAEventlist::getTstart()
{
    return tstart;
}

/*!
    \fn SAdata::SAEventlist::getTstop()
 */
double SAdata::SAEventlist::getTstop(){
	return tstop;
}


/*!
    \fn SAdata::SAEventlist::readHeader()
 */
void SAdata::SAEventlist::readHeader()
{

        fitsfile * in;	   int mystatus = 0;
         
         // This call reads just the header 
	FITS *pInfile;
	const char * b = infile.c_str(); 
		
		if (verbose) cout << "SAEventlist::readHeader() reading the header of the file " << infile << endl;   
		if (fits_open_file(&in, b, READONLY, &mystatus)) printerror(mystatus);

      try{
  			//pInfile = new FITS(infile,Read);
 			//fitsfile * in = (fitsfile*) new fitsfile[1];
   	   		// if(fits_open_file(&in, b, READONLY, &mystatus)) printerror(mystatus);
        	 // define a reference for clarity. (std::auto_ptr<T>::get returns a pointer
	  } catch(CCfits::FitsException& c){
    	 	cerr << "SAEventlist::readHeader() error in opening the inputfile "<< endl;
     		cerr << "perhaps the input file doesn't exist? "<< endl;     
			exit(1);
		}
/**/
//      char *komm;  
	char komm[80];	char s[32]; 
      double mytstart; double mytstop;
      mytstart = 0.; mytstop = 0.;
		int nkeys;

      char val[256];
      char card[256];

       //if (fits_get_hdrspace(in, &nkeys, NULL, &mystatus)) printerror(mystatus);
	if(fits_get_hdrspace(in, &nkeys, NULL, &mystatus)) printerror(mystatus);

	fits_read_key(in, TDOUBLE, (char *)"TSTART",
                  &mytstart, komm, &mystatus);
     if (verbose)    cout << "SAEventlist::readHeader()  read TSTART = " << mytstart << endl;

	setTstart(mytstart);

	if(fits_read_key(in, TDOUBLE, (char *)"TSTOP",
                  &mytstop, komm, &mystatus))printerror(mystatus);
      if (verbose)   cout << "SAEventlist::readHeader() : read TSTOP = " << mytstop << endl;
	setTstop(mytstop);
/*
	if(fits_read_key(in, TSTRING, (char *)"TELESCOP",
                  &s, komm, &mystatus))printerror(mystatus);
      if (verbose)   cout << "SAEventlist::readHeader() : read TELESCOP = " << s << endl;
*/
}
void SAdata::SAEventlist::printerror( int status)
{
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/
    if (status)
    {
       fits_report_error(stderr, status);
       exit( status );    
    }
    return;
}


/*!
    \fn SAdata::SAEventlist::getExposure()
 */
float SAdata::SAEventlist::getExposure()
{
   return exposure;
}


/*!
    \fn SAdata::SAEventlist::setExposure(float exp)
 */
void SAdata::SAEventlist::setExposure(float exp)
{
    exposure = exp;
}

void SAdata::SAEventlist::setArchiveHandler(ArchiveHandler *ah){
	  arc = ah;
}

/*!
    \fn SAdata::SAEventlist::isSaveFiltered()
 */
bool SAdata::SAEventlist::isSaveFiltered()
{
    return savefiltered;
}


/*!
    \fn SAdata::SAEventlist::setSaveFiltered(bool val)
 */
void SAdata::SAEventlist::setSaveFiltered(bool val)
{
    savefiltered = val;

}



/*!
    \fn SAdata::SAEventlist::setFilterTarget(string ft)
 */
void SAdata::SAEventlist::setFilterTarget(const string &ft)
{
    filtertarget = ft;
}


/*!
    \fn SAdata::SAEventlist::getFilterTarget()
 */
string SAdata::SAEventlist::getFilterTarget()
{
    return filtertarget;
}


/*!
    \fn SAdata::SAEventlist::setPlotTerm(const string &pt)
 */
void SAdata::SAEventlist::setPlotTerm(const string &pt)
{
   plot_term = pt;
}


/*!
    \fn SAdata::SAEventlist::getPlotTerm()
 */
string SAdata::SAEventlist::getPlotTerm()
{
    return plot_term;
}


/*!
    \fn SAdata::SAEventlist::setProductsDir(const string &pd)
 */
void SAdata::SAEventlist::setProductsDir(const string &pd)
{
    products_dir = pd; 
}


/*!
    \fn SAdata::SAEventlist::getProductsDir()
 */
string SAdata::SAEventlist::getProductsDir()
{
    return products_dir;
}


/*!
    \fn SAdata::SAEventlist::retrieveTstart()
 */
void SAdata::SAEventlist::retrieveTstart()
{
    /// @todo implement me
}


/*!
    \fn SAdata::SAEventlist::retrieveTstop()
 */
void SAdata::SAEventlist::retrieveTstop()
{
    /// @todo implement me
}


/*!
    \fn SAdata::SAEventlist::printTimeRange( ostream &o)
 */
void SAdata::SAEventlist::printTimeRange( ostream &o)
{
    o << tstart << " " << tstop << endl;
}


/*!
    \fn SAdata::SAEventlist::setInputFileName(const string &ifn)
 */
void SAdata::SAEventlist::setInputFileName(const string &ifn)
{
    infile = ifn;
}
