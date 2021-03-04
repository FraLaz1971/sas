/***************************************************************************
                          safitshandler.cpp  -  description
                             -------------------
    begin                : Tue Sep 19 2006
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

#include "safitshandler.h"
namespace SApipeline{

SAFitsHandler::SAFitsHandler(bool testflag){
  init();
}    
SAFitsHandler::SAFitsHandler(){
    SAFitsHandler::init();
  // default execution;
}

SAFitsHandler::SAFitsHandler(const string &infile){
  init();
  if (verbose) cout << "SAFitsHandler::SAFitsHandler() constructor with input filename argument" << endl;
   status = 0;
   hdus.resize(2);
   hdus[0] = "PACKETS";
   hdus[1] = "EVENTS";
   infilename = infile;
   //  outfilename = "";
   //  remove(outfilename.c_str());       // Delete old file if it already exists
   if (verbose) cout << "SAFitsHandler::SAFitsHandler() end constructor !"<< endl;
}

SAFitsHandler::SAFitsHandler(const string &infile, const string &outfile){
  init();
  infilename = infile;
  outfilename = outfile;
}

SAFitsHandler::~SAFitsHandler(){
     if (verbose) cout << "SAFitsHandler::SAFitsHandler() start destruction" << endl;
     if (in_open) closeInputFile();
     if (out_open) closeOutputFile();
     if (verbose) cout << "SAFitsHandler::SAFitsHandler() destroyed" << endl;
}
/** No descriptions */
void SAFitsHandler::setInputFileName(const string &ifn){
  infilename = ifn;
}
/** No descriptions */
void SAFitsHandler::setOutputFileName(const string &ofn){
  outfilename = ofn;
}
/** No descriptions */
int SAFitsHandler::process(){
    status = 0;
    if (verbose) cout << "SAFitsHandler::process() start" << endl;
    try {
      openInputFile();
     } catch (const exception &e){
       cerr << "is not possible to open the input file : "<< e.what() << endl;
       status = 1;
     } catch (const SAexception &se){
       cerr << "is not possible to open the input file : "<< se.getMsg() << endl;
       status = 1;
     } catch (...){
       cerr << "is not possible to open the input file : "<<  endl;
       status = 1;
     }
         
    if (verbose) cout << "SAFitsHandler::process() input file opened " << endl;

    try{
      openOutputFile();
    if (verbose) cout << "SAFitsHandler::process() output file opened " << endl;
    } catch (const exception &c){
       cerr << "is not possible to open output file:"<< c.what() << endl;
       status = 1;
     }
     
     if (in_open&&out_open){
          try{

          poutFile->setVerboseMode(false);
          
          if (verbose) cout << pinFile->extension(hdus[0]) << endl;
          if (verbose) cout << pinFile->extension(hdus[1]) << endl;

          //  copy extension by number...
            poutFile->copy(pinFile->extension(1));
            poutFile->copy(pinFile->extension(2));

        } catch(CCfits::FitsException& c){
            cerr << "SAFitsHandler::process() FITS exception occurred! " << endl;
    	    status = 1;
        } catch(const exception &e){
            cerr << "SAFitsHandler::process()  exception occurred!  :" << e.what() << endl;
	    status = 1;
        }
     }
        cout << "SAFitsHandler::process() End !"<< endl;

	return status;
}
/** No descriptions */
void SAFitsHandler::openInputFile(){
  if (verbose) cout << "SAFitsHandler::openInputFile() opening "<< infilename <<  endl;
  tempstring = "null filename";  se.setMsg(tempstring );
  i =  infilename.size();
  if (verbose) cerr << "SAFitsHandler::openInputFile() infilename size =  "<< i << endl;
  if (in_open) delete pinFile;
  if (i == 0) throw se;
  try{
  pinFile = new FITS(infilename,Read);
  in_open = true;
  } catch(CCfits::FitsException& c){
     cerr << "SAFitsHandler::openInputFile() error in creating the inputfile "<< endl;
     cerr << "perhaps the input file doesn't exist? "<< endl;     
     in_open = false;
     throw e;
  }  
}
/** No descriptions */
void SAFitsHandler::closeInputFile(){
  cout << "SAFitsHandler::closeInputFile() End!"<< endl;
  if (verbose) cout << "input file pointer value = "<< pinFile << endl;
  if(in_open){
    try{
      pinFile->destroy();
    } catch (exception &e){
      cerr << "error in deleting intput file pointer : "<< e.what() << endl;
    }
  }
}
/** No descriptions */
void SAFitsHandler::openOutputFile(){
  if (verbose) cout << "SAFitsHandler::openOutputFile() opening "<< outfilename << endl;
  tempstring = "null output filename";  
  se.setMsg(tempstring);
  i =  outfilename.size();
  if (verbose) cerr << "SAFitsHandler::openOutputFile() outfilename size =  "<< i << endl;
  if (i == 0) throw se;
  if (verbose) cout << "SAFitsHandler::openOutputFile() controlling if it's open ... "<< endl;   
  if (out_open) {
    cerr << "SAFitsHandler::openOutputFile() outfile open yet deleting before!"<< endl;
    delete poutFile;
    //throw se;
  }
  if ((in_open)&&(!out_open)) {
    try{
      cout << "SAFitsHandler::openOutputFile() going to create new FITS object, filename is "<< outfilename << endl;
      poutFile = new FITS(outfilename,*pinFile);
    } catch(CCfits::FitsException& c){
      cerr << "SAFitsHandler::openOutputFile() error in creating the outputfile "<< endl;
      cerr << "does the file exist yet? "<< endl;
      cerr << "have you the right permissions to write? "<< endl;      
      tempstring = "ls -lht "+outfilename;
      system(tempstring.c_str());     
    } catch(const exception &e){
      cerr << "caught exception "<< e.what() << endl;      
    }
    out_open = true;
    if (verbose) cout << "now the file is open "  << endl;      
    
    } else {
      string msg("source file not open");
      runtime_error c(msg);
      throw c;
      cerr << "impossible to copy the header from the source file!"<< endl;
    }
}
/** No descriptions */
void SAFitsHandler::closeOutputFile(){
  if (verbose) cout << "SAFitsHandler::closeOutputFile() End!"<< endl;
  if (verbose) cout << "output file pointer value = "<< poutFile << endl;
    if(out_open){
      try{
             poutFile->destroy();
             out_open = false;
      } catch (exception &e){
        cerr << "error in deleting output file pointer : "<< e.what() << endl;
      }
    }
}
/** No descriptions */
void SAFitsHandler::readInputFile(){
}
/** No descriptions */
void SAFitsHandler::saveOutputFile(){
}
/** No descriptions */
void SAFitsHandler::report(){
	  verbose = true;
          cout << "SAFitsHandler::report() "<< endl;
          cout << "SAFitsHandler::report() giving general information about handled FITS file "<< endl;
	  //std::auto_ptr<FITS> pinFile(new FITS(infilename,Read,true));
	  kn.push_back("TSTART");//
	  kn.push_back("TSTOP");//
	  cout << "SAFitsHandler::report() going to read n. of keys " << kn.size() << endl;
          PHDU& p = pinFile->pHDU(); 
	  std::valarray<unsigned long>  contents;
        // read all user-specifed, coordinate, and checksum keys in the image
	  try{
		pinFile->setVerboseMode(true);
		//string s("EVENTS"); 
		//readHeader(s);
		p.readKeys(kn, kv);
		/*
		double tempd = 0.;
		string ff("TSTART");
		Keyword &mykey = p.keyWord (ff);
		
		if (verbose) cout << "SADataCorrector::process() read keyword keyword --->" << mykey.name()<< endl;
		if (verbose) cout << "SADataCorrector::process() that has comment --->" << mykey.comment()<< endl;
		if (verbose) cout << "SADataCorrector::process() name was --->" << ff << endl;
		if (verbose) cout << "SADataCorrector::process() complete string --->" << mykey << endl;
		if (verbose) cout << "SADataCorrector::process() keyword value = " << mykey.value(tempd) << endl;
                //pinFile->pHDU().readAllKeys();
		*/
                cout << "SAFitsHandler::report() read keywords "<< endl;
	
		cout << "SAFitsHandler::report() now reading single double keyword from PHDU "<< endl;
		string h("TSTART");
		tempstring2 = getPHDUKeyWord(h, 82);
		cout << "read keyword " << h << " value " << tempstring2 << endl;  
                
		h = "TSTOP"; 
		tempstring2 = getPHDUKeyWord(h, 82);
		cout << "read keyword " << h << " value " << tempstring2 << endl;  
		//p.read(contents);
		tempstring = "SAFitsHandler::report() primary table"; showAlert(2, tempstring);
		std::cout << pinFile->pHDU() << std::endl;
		tempstring = "SAFitsHandler::report() first HDU"; showAlert(2, tempstring);
		std::cout << pinFile->extension(hdus[0]) << std::endl;
		tempstring = "SAFitsHandler::report() second HDU"; showAlert(2, tempstring);
		std::cout << pinFile->extension(hdus[1]) << std::endl;
          // copy extension by number...
	  if ((in_open) && (out_open)) { 
                poutFile->setVerboseMode(true);
		poutFile->copy(pinFile->extension(1));
		poutFile->copy(pinFile->extension(2));
          }

        } catch(CCfits::FitsException& c){
            cerr << "SAFitsHandler::report() exception occurred! " << endl;
            //cerr << c.what() << endl;
        } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in opening input file" << se.getMsg() << endl;
        } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in opening input file" << e.what() << endl;
        } catch (...){
		cerr << "SADataCorrector::Correct() error in opening input file" <<  endl;
        }
        cout << "SAFitsHandler::report() End!"<< endl;
}

}
/** No descriptions */
void SApipeline::SAFitsHandler::setVerbose(bool mode){
        cout << "SAFitsHandler::setVerbose() executed"<< endl;
        if (in_open) pinFile->setVerboseMode(mode);
        if (out_open) poutFile->setVerboseMode(mode);
        verbose = mode;            
}
/** No descriptions */
void SApipeline::SAFitsHandler::init(){
  if (verbose) cout << "executing SAFitsHandler::init() "<< endl;
  /** extract only the filenames -without the directories path-*/  
   verbose = false;
   hdus.resize(2);
   hdus[0] = "PACKETS";
   hdus[1] = "EVENTS";
  in_open = false;
  out_open = false;
  if (verbose) cout << "executed SAFitsHandler::init() "<< endl;
  /** set output filename */
  
}
/** create the relative filenames dividing the directory path from the filename*/
void SApipeline::SAFitsHandler::setRelativeFileNames(){   
  rel_infilename =  infilename.substr(infilename.find_last_of( "/")+1);
  rel_outfilename =  outfilename.substr(outfilename.find_last_of( "/")+1);
 if (verbose) cout << "rel_infilename = "<< rel_infilename << endl;
 if (verbose) cout << "rel_outfilename = "<< rel_outfilename << endl;
}
/** No descriptions */
void SApipeline::SAFitsHandler::show(){
 cout << "infilename = "<< infilename << endl;
 cout << "outfilename = "<<  outfilename << endl;
 cout << "rel_infilename = "<< rel_infilename << endl;
 cout << "rel_outfilename = "<< rel_outfilename << endl;
 if (in_open) cout << "the input file is open!"<< endl;
 else cout << "the input file was not open!"<< endl;
 if (out_open) cout << "the output file is open!"<< endl;
 else  cout << "the output file was not open!"<< endl;
}
/** No descriptions */
void SApipeline::SAFitsHandler::removeOldOutfile(){
  cout << "SAFitsHandler::removeOldOutfile()"<< endl;
  tempstring = "rm "+outfilename;
  try{
    cout << "going to remove file "<< outfilename << endl;
    system(tempstring.c_str());  
  } catch (exception &e){
    cerr << "SAFitsHandler::removeOldOutfile() error in removing the old output file"<< endl;
  }
}
/** set an environment variable with a given name (oev) where to write the OK file to trigger the following(s) application(s)
 */
void SApipeline::SAFitsHandler::setOutTrigFileEnvVar(const string &oev, const string &vv){
  setVerbose(true);
  try{
    char *ovv;
    setEnvVar(oev, vv, 0);
    ovv = getenv(oev.c_str());    string tempstring3(ovv);
    if (verbose) cout << "the old env var read from outside = "<< tempstring3 << endl;
    setEnvVar(oev, vv, 1);
    if (verbose) cout << "now value is "<< getenv(oev.c_str())<< endl;
  } catch (exception &e){
    cerr << "SAFitsHandler::createOutOKFileEnvVar error in creating and exporting the environment variable"<< endl;
  }
  setVerbose(false);
}
/** retrieve the I/O dir strings from yet present information*/
void SApipeline::SAFitsHandler::retrieveIODataDirs(){
  try{
    inputfiledir =  infilename.substr(0, infilename.find_last_of( "/"));
    if (verbose) cout << "SAFitsHandler::retrieveIODataDirs() "<< inputfiledir << endl;
    outputfiledir =  outfilename.substr(0, outfilename.find_last_of( "/"));
    if (verbose) cout << "SAFitsHandler::retrieveIODataDirs() "<< outputfiledir << endl;    
  } catch (const exception &e){
    cerr << "SAFitsHandler::retrieveIODataDirs() error in extracting the events data I/O dirs"<< e.what() << endl;      
  }

}

void SApipeline::SAFitsHandler::retrieveInputDataDir(){
  try{
    inputfiledir =  infilename.substr(infilename.find_last_of( "/"), -1);
    if (verbose) cout << "SAFitsHandler::retrieveIODataDirs() "<< inputfiledir << endl;
  } catch (const exception &e){
    cerr << "SAFitsHandler::retrieveIODataDirs() error in extracting the Input data dir"<< e.what() << endl;
  }

}


/*!
    \fn SApipeline::SAFitsHandler::processSafe()
 */
int SApipeline::SAFitsHandler::processSafe()
{
  setVerbose(true);
  status = 1;
  if (process() == 0) cout << "SAFitsHandler::processSafe() correctly prcessed" << endl;
  status = 0;
  setVerbose(false);
  return status;
}

void SApipeline::SAFitsHandler::printerror( int status)
{
    /*****************************************************/
    /* Print out cfitsio error messages and exit program */
    /*****************************************************/

    if (status)
    {
       fits_report_error(stderr, status);
	string m;
	stringstream ss; ss << stderr << endl << "SAFitsHandler::printerror() err. num. " << status << endl;
	m = ss.str();
	se.setMsg(m);
	throw(se);
        //exit( status );    
    }
    return;
}


/*!
    \fn SApipeline::SAFitsHandler::getKeyWord(const string &keyname)
 */
string SApipeline::SAFitsHandler::getPHDUKeyWord(const string &keyname, int keytype)
{
	string tempstring = "";
	kn.clear(); kv.clear();
	kn.push_back(keyname);
	PHDU& p = pinFile->pHDU(); 	  
	p.readKeys(kn, kv);	
	/*
	double tempd = 0.0;
	string ff(keyname);
	Keyword &mykey = p.keyWord (ff);
	if (verbose) cout << "SAFitsHandler::getPHDUKeyWord() read keyword keyword --->" << mykey.name()<< endl;
	if (verbose) cout << "SAFitsHandler::getPHDUKeyWord() that has comment --->" << mykey.comment()<< endl;
	if (verbose) cout << "SAFitsHandler::getPHDUKeyWord() name was --->" << ff << endl;
	if (verbose) cout << "SAFitsHandler::getPHDUKeyWord() complete string --->" << mykey << endl;
	if (verbose) cout << "SAFitsHandler::getPHDUKeyWord() keyword value = " << mykey.value(tempd) << endl;
	if (verbose) cout << "SAFitsHandler::getPHDUKeyWord() kn[0] = "<< kn[0] << " kv[0] = " << kv[0] << endl;
	*/
	ss.str(""); ss << fixed << setprecision(6) << kv[0]; tempstring = ss.str();
	return tempstring;
}

/*!
    \fn SApipeline::SAFitsHandler::getKeyWord(const string &keyname)
 */
string SApipeline::SAFitsHandler::getKeyWord(const string &keyname, int keytype, int hdunum)
{
	kn.clear(); kv.clear();
	kn.push_back(keyname);
	PHDU& p = pinFile->pHDU(); 	  
	p.readKeys(kn, kv);	  
	return tempstring;
}


/*!
    \fn SApipeline::SAFitsHandler::readHeader(const string &hduname)
 */
void SApipeline::SAFitsHandler::readHeader(const string &hduname)
{
    try
{
         const string EVENTS(hduname);

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
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::readHeader() function \n" ;
}

}


/*!
    \fn SApipeline::SAFitsHandler::getDataDuration()
 */
double SApipeline::SAFitsHandler::getDataDuration()
{
    duration = (getTstop() - getTstart());
    return duration;
}


/*!
    \fn SApipeline::SAFitsHandler::getTstart()
 */
double SApipeline::SAFitsHandler::getTstart()
{
    string h = "TSTART"; 
    tstart = atof(getPHDUKeyWord(h, 82).c_str());
    return tstart;
}


/*!
    \fn SApipeline::SAFitsHandler::getTstop()
 */
double SApipeline::SAFitsHandler::getTstop()
{
    string h = "TSTOP"; 
    tstop = atof(getPHDUKeyWord(h, 82).c_str());
    return tstop ;
}



