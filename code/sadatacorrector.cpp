/***************************************************************************
                          sadatacorrector.cpp  -  description
                             -------------------
    begin                : Mon Oct 22 2007
    copyright            : (C) 2007 by guest
    email                : guest@spirit
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "sadatacorrector.h"
namespace DataCorrection{

SADataCorrector::SADataCorrector(){
  if (verbose) cout << "I'm SADataCorrector()" << endl;
      SAFitsHandler::setVerbose(false);
      cout << "SAFitsHandler::verbose = " << SAFitsHandler::verbose << endl;
      verbose = bool(SAFitsHandler::verbose);
      sdt.setVerbose(false);
}

SADataCorrector::SADataCorrector(const string &fn, const string &ofn){
  if (verbose) cout << "I'm SADataCorrector()" << endl;
}

SADataCorrector::~SADataCorrector(){
	//Corrector::~Corrector();
}

void SADataCorrector::Correct(const string &fn, const string &ofn, double tstart, double tstop){
	cout << "SAFitsHandler::verbose = " << SAFitsHandler::verbose << endl;
        cout << "SADataCorrector::Correct() SADataCorrector::verbose = " << verbose << endl;
	if (verbose) cout << "executing SADataCorrector::Correct() - verbose output -" << endl;
	if (verbose) cout << "executing SADataCorrector::Correct() infile = " << fn << endl;
	if (verbose) cout << "executing SADataCorrector::Correct() outfile = " << ofn << endl;
	if (verbose) cout << "executing SADataCorrector::Correct() tstart = " << tstart << endl;
	if (verbose) cout << "executing SADataCorrector::Correct() tstop = " << tstop << endl;

	string th(""); string ns("default");
	SAFitsHandler::setInputFileName(fn);
	SAFitsHandler::setOutputFileName(ofn);
	SAFitsHandler::openInputFile();
	stringstream myss;myss.setf(ios::fixed,ios::floatfield);
	mfi = 53005.;	 mff = 0.00075444444444444;	 tz = 0.;
		/* MUST initialize status */        
	status = 0;	 nkeys = 0;	remove(ofn.c_str());            // Delete old file if it already exists 
	char komm[80]; 	double mytstart; double mytstop;
      	mytstart = 0.; mytstop = 0.;
        char *val;        char *card;
        double timezero_sec;        timezero_sec = -756950400.;
        int nkeys, keypos;   

	char * k;
try{
  pinFile = new FITS(fn,Read);
  in_open = true;
  } catch(CCfits::FitsException& c){
     cerr << "SADataCorrector::Correct() error in opening the inputfile "<< endl;
     cerr << "perhaps the input file doesn't exist? "<< endl;     

  }

		float t; double d;	PHDU *pp; ExtHDU *hh; string c("");
		vector<string>::iterator jt;	vector<double>::iterator it;	vector<int>::iterator ii ; vector<string>::iterator ic ;
		vector<string>::iterator jt2;	vector<double>::iterator it2;	vector<int>::iterator ii2 ; vector<string>::iterator ic2 ;
			
		
		int mykeytype = TDOUBLE; 
		vector<string>::iterator svt;
		vector<string>::iterator svt2;
 		
		sdt.setVerbose(true);
		int yy ;
		int hdunum = 1;
		if(hdunum==1){
		  pp = &pinFile->pHDU();
		} else{
		  hh = &pinFile->extension(hdus[hdunum]);
		}

try{
		//if(fits_get_hdrspace(outfptr, &nkeys, NULL, &status)) printerror(status);
		string mykeyname, mykeyval, mykeycomment;
		string tempstring2;
		mykeyname = "TSTART"; 
		myss.str("");myss<<tstart; mykeyval = myss.str();
		mykeycomment = "start time";
		 
		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);sv.push_back(ns);
		
		if (verbose) cout << "SADataCorrector::Correct() keyval = "<< mykeyval << endl;
		if (verbose) cout << "SADataCorrector::Correct() keytype = "<< mykeytype << endl;
		if (verbose) cout << "SADataCorrector::Correct() keycomment = "<< mykeycomment << endl;
		//pp->readKeys(kn, kv);
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);sv.push_back(ns);

		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
			if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				
				//cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
			ii++; jt++;ic++;it++;svt++;
		}

//		setKeyword(1, mykeyname, TDOUBLE, mykeyval);
		if (verbose) cout << "SADataCorrector::Correct() set key 1 TSTART to value " << mykeyval << endl;

		mykeyname = "TSTOP"; 
		myss.str("");myss<<tstop; mykeyval = myss.str();

		mykeycomment = "stop time";

		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);sv.push_back(ns);svt = sv.begin();

		if (verbose) cout << "SADataCorrector::Correct() keyval = "<< mykeyval << endl;
		if (verbose) cout << "SADataCorrector::Correct() keytype = "<< mykeytype << endl;
		if (verbose) cout << "SADataCorrector::Correct() keycomment = "<< mykeycomment << endl; 
		//pp->readKeys(kn, kv);
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);sv.push_back(ns);

		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
	/*
		if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;

				//cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
	*/
			ii++; jt++;ic++;it++;svt++;
		}

		//setKeyword(1, mykeyname, TDOUBLE, mykeyval);
		if (verbose) cout << "SADataCorrector::Correct() set key 2 TSTOP"<< endl;


		mykeyname = "DATE-OBS";
		mykeytype = TSTRING; 
		myss.str("");myss<<sdt.getDateTime(); mykeyval = myss.str();

		mykeycomment = "date-time of observation start";

		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);
		if (verbose) cout << "SADataCorrector::Correct() keyval = "<< mykeyval << endl;
		if (verbose) cout << "SADataCorrector::Correct() keytype = "<< mykeytype << endl;
		if (verbose) cout << "SADataCorrector::Correct() keycomment = "<< mykeycomment << endl; 
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);sv.push_back(ns);
		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
/*	
		if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *svt << " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;

				//cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
*/
			ii++; jt++;ic++;it++;svt++;
		}
		if (verbose) cout << "SADataCorrector::Correct() set key 3 DATE-OBS"<< endl;
		
		mykeyname = "DATE-END"; 
		mykeytype = TSTRING; 
		myss.str("");myss<<sdt.getDateTime(); mykeyval = myss.str();

		mykeycomment = "date-time of observation end";
		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);
		if (verbose) cout << "SADataCorrector::Correct() keyval = "<< mykeyval << endl;
		if (verbose) cout << "SADataCorrector::Correct() keytype = "<< mykeytype << endl;
		if (verbose) cout << "SADataCorrector::Correct() keycomment = "<< mykeycomment << endl; 
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);

		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
/*
			if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *svt << " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;

				//cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
*/
			ii++; jt++;ic++;it++;svt++;
		}
		if (verbose) cout << "SADataCorrector::Correct() set key 3 DATE-END"<< endl;
		
		
	fitsfile *infptr;      // pointer to the FITS file, defined in fitsio.h 
	fitsfile *outfptr;     // pointer to the new FITS file      

try{
	try{			

    if ( fits_open_file(&infptr, fn.c_str(), READONLY, &status) )   printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in opening input file" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in opening input file" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in opening input file" <<  endl;
       }
       
	hdutype = 0; morekeys = 0;
	mfi = 53005.;
	mff = 0.00075444444444444;
	tz = 0.;
	status = 0;	 nkeys = 0;

	// Processing primary HDU

	try{			
    if (fits_create_file(&outfptr, ofn.c_str(), &status)) // create FITS file
         printerror( status );           // call printerror if error occurs 
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in creating file" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in creating file" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in creating file" <<  endl;
       }
		
    try{
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in copying HDU" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in copying HDU" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in copying HDU" <<  endl;
       }

	 
try{	 
       k = (char *)"TIMEZERO";
      if ( fits_delete_key(outfptr, k,  &status)) {
        printerror(status);
        throw e;
       };
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }

     try{
     k = (char *)"TIMESYS";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       };                   
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }

       
       	
    try{
	k = (char *)"MJDREF";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       }; 
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }
	
       
        k = (char *)"TT";
        if (fits_write_key(outfptr, TSTRING, (char *)"TIMESYS",
        k, (char *)"this is a comment", &status)) printerror( status );

        if (fits_write_key(outfptr, TDOUBLE, (char *)"TIMEZERO",
        &tz, (char *)"this is a comment", &status)) printerror( status );

        k = (char *)"V_0_1_0";
        if (fits_write_key(outfptr, TSTRING, (char *)"COR_VERS",
        k, (char *)" version of SA data correction software", &status)) printerror( status );


        if (fits_write_key(outfptr, TDOUBLE, (char *)"MJDREFF",
        &mff, (char *)"this is a comment", &status)) printerror( status );

                   
        if (fits_write_key(outfptr, TDOUBLE, (char *)"MJDREFI",
        &mfi, (char *)"this is a comment", &status)) printerror( status );

	float t; double d;
	vector<string>::iterator si = kn.begin();
	vector<double>::iterator di = kv.begin();
	vector<int>::iterator ii = kt.begin();
	vector<string>::iterator ic = kc.begin();
	svt = sv.begin();
	// Processing second (Packet extension)  HDU
	 if (verbose) cout << "SADataCorrector::Correct() Processing second (Packet extension)  HDU" << endl;

    if ( fits_movabs_hdu(infptr, 2, &hdutype, &status) )
         printerror( status );

    // copy 3rd HDU from the input file to the output file (to 2nd HDU) ??
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );

   try{	 
       k = (char *)"TIMEZERO";
      if ( fits_delete_key(outfptr, k,  &status)) {
        printerror(status);
        throw e;
       };
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }
       
    try{
     k = (char *)"TIMESYS";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       };                   
             } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }
        
   try{    
	k = (char *)"MJDREF";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       }; 
    } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }
    try{        
	k = (char *)"TT";
        if (fits_write_key(outfptr, TSTRING, (char *)"TIMESYS",
        k, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }

try{
        if (fits_write_key(outfptr, TDOUBLE, (char *)"TIMEZERO",
        &tz, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }


try{        k = (char *)"V_0_1_0";
        if (fits_write_key(outfptr, TSTRING, (char *)"COR_VERS",
        k, (char *)" version of SA data correction software", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }



try{
        if (fits_write_key(outfptr, TDOUBLE, (char *)"MJDREFF",
        &mff, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }


try{                   
        if (fits_write_key(outfptr, TDOUBLE, (char *)"MJDREFI",
        &mfi, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }


 	svt = sv.begin();

	while (si<kn.end()){
	//t = atof(tempstring2.c_str());
		//if (verbose) cout << "keyname = " << kn[] << "keyvalue = " << << "keycomment = " << endl;
		d = *di;
		tempstring = *si;
		tempstring2 = *ic; 
	if (*ii == TDOUBLE){
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
	}
	else {
	if ( verbose) cout << "FITS data type code = "<< *ii << endl;
	if (*ii == TSTRING) {
	th = *svt;
	if ( verbose) cout << "1 scrivo una stringa ! = " << th << endl;
	}
	if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        (char *)th.c_str(), (char *)tempstring2.c_str(), &status) ) printerror( status );
	
	}
		si++; di++; ii++; ic++;svt++;
	}
	 si = kn.begin();di = kv.begin();ii = kt.begin();ic = kc.begin();svt = sv.begin();


	 
	// correct time column in 2nd HDU (PACKETS)
	long int nrows = 0;	long int ij=0;
        int hdunum,  nfound, anynull;
        int frow, felem, nelem, longnull;
        float floatnull;        double Doublenull;
	 
   	fits_get_num_rows(infptr, &nrows, &status);


    if (verbose) cout << "SADataCorrector::Correct() correct time column in 2nd HDU (PACKETS) number of rows " << nrows << endl;
	// correct time
      frow      = 1; felem     = 1;       nelem     = nrows;
      longnull  = 0;      floatnull = 0.;      Doublenull = 0.;
      timezero_sec = -756950400.;

     double *loc_time = new double[nrows];
     memset((void *)loc_time , 0, nrows*sizeof(double));

     try{
     if(fits_read_col(infptr, TDOUBLE, 20, frow, felem, nelem, &anynull,  loc_time,
                    &anynull, &status)) printerror(status);
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in reading column" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in reading column" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in reading column" <<  endl;
       }

		    
     for (ij = 0; ij < nrows; ij++){

//      list[ii]->setPaktnumb((unsigned long int)loc_paktnumb[ij]);
      if ((verbose)&&(ij<10)) cout << "SADataCorrector::Correct() correcting time column in 2nd HDU (PACKETS) old time =  " << loc_time[ij] << endl;
	loc_time[ij] = (loc_time[ij]/1000000) + timezero_sec;
      if ((verbose)&&(ij<10)) cout << "SADataCorrector::Correct() correcting time column in 2nd HDU (PACKETS) corrected time =  " << loc_time[ij] << endl;

     }

	double temps;
	double newtstart, newtstop;
	
  	sdt.setVerbose(true);
	temps = loc_time[0];  sdt.setAGILETime(temps+sdt.getTTOffset());
	sdt.show();
        if (verbose) cout << "DATE-OBS (TT) = " << sdt.AGILETimeToUTC(temps+sdt.getTTOffset())<< endl;
	svt[2] = sdt.getDateTime();
     
	temps = loc_time[nrows -1 ];	sdt.setAGILETime(temps+sdt.getTTOffset());
     
	sdt.show();
        if (verbose) cout << "DATE-END (TT) = " << sdt.AGILETimeToUTC(temps+sdt.getTTOffset())<< endl;
	svt[3] = sdt.getDateTime();
	
	//cout <<  sdt.setDoy(1)<< endl;	
	//cout << "doy = "<< sdt.getDoy()<< endl;
	//	string ms("1");	
	//	sdt.setHour(ms);	
	//	cout << "doy = "<< sdt.getHour()<< endl;
     try{
           if(fits_write_col(outfptr, TDOUBLE, 20, frow, felem, (long)nrows, loc_time, &status))
            printerror(status);
	 } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing column" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing column" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing column" <<  endl;
       }
		
		while (si<kn.end()){
	//t = atof(tempstring2.c_str());
		//if (verbose) cout << "keyname = " << kn[] << "keyvalue = " << << "keycomment = " << endl;
		d = *di;
		tempstring = *si;
		tempstring2 = *ic; 
	if (*ii == TDOUBLE){
		try{
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
		 } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating keyword" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating keyword" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating keyword" <<  endl;
       }
	}
	
	else {
	if (verbose) cout << "FITS data type code = "<< *ii << endl;
	if (*ii == TSTRING) {
	th = *svt;
	if (verbose) cout << "1 scrivo una stringa ! = " << th << endl;
	}
	try{
	if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        (char *)th.c_str(), (char *)tempstring2.c_str(), &status) ) printerror( status );
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
		 } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating keyword" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating keyword" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating keyword" <<  endl;
       }	
	}
		si++; di++; ii++; ic++;svt++;
	}

	 si = kn.begin(); di = kv.begin(); ii = kt.begin(); ic = kc.begin(); svt = sv.begin();
	 //sv = svt.begin();
	 
			 	
	// Processing third (events/images extension)  HDU
	 if (verbose) cout << "SADataCorrector::Correct() Processing third HDU (Events extension)" << endl;
   try{
    if ( fits_movabs_hdu(infptr, 3, &hdutype, &status) )
         printerror( status );
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
		 } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in moving to HDU 3" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in moving to HDU 3" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in in moving to HDU 3" <<  endl;
       }
   try{
    // copy 3rd HDU from the input file to the output file (to 2nd HDU) 
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );
    	 } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in copying the HDU 3" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in copying the HDU 3" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in copying the HDU 3" <<  endl;
       }
       
    try{
	k = (char *)"TIMEZERO";
	if ( fits_delete_key(outfptr, k,  &status)) {
		printerror(status);
		throw e;
	};	
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }
       
    try{
     k = (char *)"TIMESYS";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       };
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }
       
     try{                          
	k = (char *)"MJDREF";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       }; 
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in deleting key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in deleting key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in deleting key" <<  endl;
       }
       
     try{	         
	k = (char *)"TT";
        if (fits_write_key(outfptr, TSTRING, (char *)"TIMESYS",
        k, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }
      
      try{	         
        if (fits_write_key(outfptr, TDOUBLE, (char *)"TIMEZERO",
        &tz, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }

      try{	         
        k = (char *)"V_0_1_0";
        if (fits_write_key(outfptr, TSTRING, (char *)"COR_VERS",
        k, (char *)" version of SA data correction software", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }


      try{	         
        if (fits_write_key(outfptr, TDOUBLE, (char *)"MJDREFF",
        &mff, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }

                   
      try{	         
        if (fits_write_key(outfptr, TDOUBLE, (char *)"MJDREFI",
        &mfi, (char *)"this is a comment", &status)) printerror( status );
       } catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing key" <<  endl;
       }


		while (si<kn.end()){
	//t = atof(tempstring2.c_str());
		//if (verbose) cout << "keyname = " << kn[] << "keyvalue = " << << "keycomment = " << endl;
		d = *di;
		tempstring = *si;
		tempstring2 = *ic; 
	if (*ii == TDOUBLE){
	try{
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
	} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating key" <<  endl;
       }
	}
	else {
	if (verbose) cout << "SADataCorrector::Correct() FITS data type code = "<< *ii << endl;
	if (*ii == TSTRING) {
	th = *svt;
	if (verbose) cout << "SADataCorrector::Correct() 1 scrivo una stringa ! = " << th << endl;
	}
	try{
	if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        (char *)th.c_str(), (char *)tempstring2.c_str(), &status) ) printerror( status );
	} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating key" <<  endl;
       }
	
	}
		si++; di++; ii++; ic++;svt++;
	}
	
	
	 si = kn.begin(); di = kv.begin(); ii = kt.begin(); ic = kc.begin(); svt = sv.begin();

	 
	 // correct time of events (3d HDU)
	    	
		fits_get_num_rows(infptr, &nrows, &status);

    if (verbose) cout << "SADataCorrector::Correct() correcting time of events (3d HDU) number of rows " << nrows << "column n. 14" << endl;
	// correct time
      frow      = 1; felem     = 1;       nelem     = nrows;
      longnull  = 0;      floatnull = 0.;      Doublenull = 0.;
      timezero_sec = -756950400.;
      
	double *loc_timeev = new double[nrows];
     	memset((void *)loc_timeev , 0, nrows*sizeof(double));
    
    if (verbose) cout << "SADataCorrector::Correct() reading time of events (3d HDU) number of rows " << nrows << "column n. 14"<< endl;
     
     try{    
     if(fits_read_col(infptr, TDOUBLE, 14, frow, felem, nelem, &anynull,  loc_timeev,
                    &anynull, &status)) printerror(status);
	} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in reading time column" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in reading time column" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in reading time column" <<  endl;
       }
		    
     for (ij = 0; ij < nrows; ij++){

//      list[ii]->setPaktnumb((unsigned long int)loc_paktnumb[ij]);

    if ((verbose)&&(ij<10)) cout << "SADataCorrector::Correct() performing correction of time of events (3d HDU) number of rows " << nrows << " column n. 14" << endl;
 
      if ((verbose)&&(ij<10)) cout << "SADataCorrector::Correct()  old time =  " << loc_timeev[ij] << endl;
	loc_timeev[ij] = double(loc_timeev[ij]/1000.0) + timezero_sec;
      if ((verbose)&&(ij<10)) cout << "SADataCorrector::Correct()  corrected time =  " << loc_timeev[ij] << endl;
     }

	temps = 0.0;

	temps = loc_timeev[0];  sdt.setAGILETime(temps+sdt.getTTOffset());
	if (verbose) sdt.show();
	newtstart = temps;
	if (verbose) cout << "SADataCorrector::Correct()  going to update first hdu tstart with " << newtstart << endl;
        if (verbose) cout << "DATE-OBS (TT) = " << sdt.AGILETimeToUTC(temps+sdt.getTTOffset())<< endl;
	svt[2] = sdt.getDateTime();
     
	temps = loc_timeev[nrows -1 ];	sdt.setAGILETime(temps+sdt.getTTOffset());
        newtstop = temps;
	if (verbose) cout << "SADataCorrector::Correct() going to update first hdu tstart with " << newtstop << endl;
	if (verbose) sdt.show();
        if (verbose) cout << "DATE-END (TT) = " << sdt.AGILETimeToUTC(temps+sdt.getTTOffset())<< endl;
	svt[3] = sdt.getDateTime();
	

         if (verbose) cout << "SADataCorrector::Correct() writing time of events (3d HDU) number of rows " << nrows << endl;
   
	 try{
	 
         if(fits_write_col(outfptr, TDOUBLE, 14, frow, felem, (long)nrows, loc_timeev, &status))
            printerror(status);
	    
	} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in writing column" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in writing column" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in writing column" <<  endl;
       }
	    		while (si<kn.end()){
	//t = atof(tempstring2.c_str());
		//if (verbose) cout << "keyname = " << kn[] << "keyvalue = " << << "keycomment = " << endl;
		d = *di;
		tempstring = *si;
		tempstring2 = *ic; 
	if (*ii == TDOUBLE){
	try{
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
		} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating key" <<  endl;
       }
	}
	else {
	if (verbose) cout << "SADataCorrector::Correct() FITS data type code = "<< *ii << endl;
	if (*ii == TSTRING) {
	th = *svt;
	if (verbose) cout << "SADataCorrector::Correct() 1 scrivo una stringa ! = " << th << endl;
	}
	try{
	if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        (char *)th.c_str(), (char *)tempstring2.c_str(), &status) ) printerror( status );
	} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating key" <<  endl;
       }	
	}
		si++; di++; ii++; ic++;svt++;
	}

	 si = kn.begin(); di = kv.begin(); ii = kt.begin(); ic = kc.begin(); svt = sv.begin();
	    
	 // return to first HDU

    if ( fits_movabs_hdu(outfptr, 1, &hdutype, &status) )
         printerror( status );

	    /* copy all the user keywords (not the structural keywords) */
    fits_get_hdrspace(outfptr, &nkeys, NULL, &status); 
    /*
    	vector<string>::iterator jt;	vector<double>::iterator it;	vector<int>::iterator ii ; vector<string>::iterator ic ;
	vector<string>::iterator jt2;	vector<double>::iterator it2;	vector<int>::iterator ii2 ; vector<string>::iterator ic2 ;
		
	vector<string>::iterator si = kn.begin();
	vector<double>::iterator di = kv.begin();
	vector<int>::iterator ii = kt.begin();
	
    */
    

    
    ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
    ii2 = kt.begin(); jt2 = kn.begin();it2 = kv.begin(); ic2 = kc.begin(); svt2 = sv.begin();	
    	
		while(jt < kn.end()){
			
			if (*jt == "TSTART")         {
				jt2 = kn.erase(jt);
				ii2 = kt.erase(ii); 
				ic2 = kc.erase(ic);
				it2 = kv.erase(it);
 				svt2 = sv.erase(svt);
			}
			
			if (*jt == "TSTOP")         {
				jt2 = kn.erase(jt);
				ii2 = kt.erase(ii); 
				ic2 = kc.erase(ic);
				it2 = kv.erase(it);
 				svt2 = sv.erase(svt);
			}

			ii++; jt++;ic++;it++;svt++;
		}
    
    		mykeytype = TDOUBLE;
    		mykeyname = "TSTART"; 
		myss.str("");myss<< min(newtstart, tstart) ; mykeyval = myss.str();
		mykeycomment = "start time";
		 
		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);sv.push_back(ns);
		
		if (verbose) cout << "SADataCorrector::Correct() keyval = "<< mykeyval << endl;
		if (verbose) cout << "SADataCorrector::Correct() keytype = "<< mykeytype << endl;
		if (verbose) cout << "SADataCorrector::Correct() keycomment = "<< mykeycomment << endl;
		//pp->readKeys(kn, kv);
		d = atof(mykeyval.c_str());//d = double(t);
//		d = newtstart;
		kv.push_back(d);sv.push_back(ns);
		cout << "d = " << d << endl;
		cout << "tstart = " << newtstart << endl;

		vector<double>::iterator ajt;
		ajt = kv.begin();
		cout << "vector size = " << kv.size()  << endl;	
		
		while (ajt != kv.end() ) {
			cout << ajt - kv.begin() << " " << *ajt << endl;
//			if (*ajt == "seconda") kv.erase(ajt);
			ajt++;
		}
		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
			if (verbose){
				if (*ii == TDOUBLE){ 
				if (verbose) cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				if (verbose) cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				
				//cout << "SADataCorrector::Correct() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
			ii++; jt++;ic++;it++;svt++;
		}

//		setKeyword(1, mykeyname, TDOUBLE, mykeyval);
		if (verbose) cout << "SADataCorrector::Correct() set key 1 TSTART to value " << mykeyval << endl;
    		
		mykeytype =  TDOUBLE;
		mykeyname = "TSTOP"; 
		myss.str("");myss<<max(newtstop, tstop); mykeyval = myss.str();
		
		mykeycomment = "stop time";

		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);sv.push_back(ns);svt = sv.begin();

		if (verbose) cout << "SADataCorrector::Correct() keyval = "<< mykeyval << endl;
		if (verbose) cout << "SADataCorrector::Correct() keytype = "<< mykeytype << endl;
		if (verbose) cout << "SADataCorrector::Correct() keycomment = "<< mykeycomment << endl; 
		//pp->readKeys(kn, kv);
		d = atof(mykeyval.c_str());//d = double(t);
		
		//d = newtstop;
		cout << "d = " << d << endl;
		cout << "tstop = " << newtstop << endl;
		kv.push_back(d);sv.push_back(ns);

		ajt = kv.begin();
		cout << "vector size = " << kv.size()  << endl;	
		
		while (ajt != kv.end() ) {
			cout << ajt - kv.begin() << " " << *ajt << endl;
//			if (*ajt == "seconda") kv.erase(ajt);
			ajt++;
		}
	

		//setKeyword(1, mykeyname, TDOUBLE, mykeyval);
		if (verbose) cout << "SADataCorrector::Correct() set key 2 TSTOP final "<< endl;

		//ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin(); si = kn.begin();
    	        si = kn.begin(); di = kv.begin(); ii = kt.begin(); ic = kc.begin(); svt = sv.begin();

	while (si<kn.end()){
		d = *di;
		tempstring = *si;
		tempstring2 = *ic; 
		
	if (*ii == TDOUBLE){
	try{
	        cout << "SADataCorrector::Correct() double "  << tempstring << " " << tempstring2 << " writing " << d << endl;
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
	} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating key" <<  endl;
       }
	}
	else {
	if (*ii == TSTRING) {
	th = *svt;
	
	try{
            if (verbose) cout << "SADataCorrector::Correct() string "  << tempstring << " " << tempstring2 << " writing " << th << endl;
	if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        (char *)th.c_str(), (char *)tempstring2.c_str(), &status) ) printerror( status );
	
	} catch (const SAexception &se){
		cerr << "SADataCorrector::Correct() error in updating key" << se.getMsg() << endl;
       } catch (const exception &e){
		cerr << "SADataCorrector::Correct() error in updating key" << e.what() << endl;
       } catch (...){
		cerr << "SADataCorrector::Correct() error in updating key" <<  endl;
       }
       }
       
	}
		si++; di++; ii++; ic++;svt++;
	}
	
		// read events table dimension
			
	if (fits_close_file(infptr, &status)) printerror(status);
        if (fits_close_file(outfptr, &status)) printerror(status);
	
} catch(CCfits::FitsException& c){
     cerr << "SADataCorrector::Correct()  error in saving the outputfile "<< endl;
  }

} catch(CCfits::FitsException& c){
     cerr << "SADataCorrector::Correct() FITS  error in correcting the file "<< endl;
  } 
//		save(fn, ofn);	
 
	if (verbose) cout << "SADataCorrector::Correct() bench 6 end of the method!"<< endl;

}

void SADataCorrector::process(const string &fn, const string &ofn){
setInputFileName(fn);
setOutputFileName(ofn);
openInputFile();	
//openOutputFile();	

    //    fitsfile * in;	   
	int mystatus = 0;
         
         // This call reads just the header 
	FITS *poutFile2;

	
	const char * b = fn.c_str(); 
		
		
		if (verbose) cout << pinFile->pHDU() << endl;
 		if (verbose) cout << "SADataCorrector::process() printed primary HDU" << endl;
		PHDU *pp;
		pp = &pinFile->pHDU();
		//PHDU pp(pinFile->pHDU());
		//pp = pinFile->pHDU();
   	    if (verbose) cout << *pp << endl;
 		if (verbose) cout << "SADataCorrector::process() stampata la primary HDU" << endl;
   	    	//if (verbose) cout << pinFile->extension(hdus[0]) << endl;
		//if (verbose) cout << "stampata HDU[0]" << endl;
		//if (verbose) cout << pinFile->extension(hdus[1]) << endl;
		//if (verbose) cout << "stampata HDU[1]" << endl;
		
		

 	vector<string> kn; //keyword names
	/** */
	vector<double> kv;  //keyword values
	  char komm[256];	char s[32]; 
      double mytstart; double mytstop;
      mytstart = 0.; mytstop = 0.;
		int nkeys;

      char val[256];
      char card[256];


         vector<string> pk;
         const string GLOBAL("");
//         std::auto_ptr<FITS> pInfile;
//         ExtHDU = &inFile.pHDU() ;


try
{
	
         //std::auto_ptr<FITS> pInfile(new FITS(infile,Read,true ));
         //FITS inFile(infile);
         //PHDU& phdu = inFile.pHDU();
kn.push_back("TELESCOP");
kn.push_back("INSTRUME");//= 'PDHU    '           / Instrument of the telescope (OGIP/93-013)
kn.push_back("DETNAM");//  = 'GPS     '           / Detector of the instrument (OGIP/93-013)
kn.push_back("OBS_ID");//  =                 2001 / Observation ID (OGIP/94-001)
kn.push_back("OBS_MODE");//=                      / TBD - Observation mode (OGIP/94-001)
kn.push_back("DATAMODE");//=                      / TBD - Detector Operating Mode (OGIP/94-001)
kn.push_back("APID");//    =                  767 / Application Process ID
kn.push_back("PKTTYPE");// =                   39 / Packet Type
kn.push_back("PKTSTYPE");//=                   16 / Packet Sub-Type
kn.push_back("CONTNUMB");//=                 2001 / Contact Number (progressive within a contact)
kn.push_back("CENTURY");// =                   32 / Valid Century value
kn.push_back("MODEL");//   = 'Satellite'          / Model of the DETNAM (GTB)
kn.push_back("TESTLEVE");//= 'GS      '           / Test level of the MODEL (GTB)
kn.push_back("TE_NAME");// = 'PDHU_FUMO_TE'       / Name of the Test Equipment used (GTB)
kn.push_back("CAMPAIGN");//= 'BO      '           / Campaign (location) of the acquisition (GTB)
kn.push_back("PERIOD");//  = 'Oct_2006'           / Period of the campaign (GTB)
kn.push_back("CREATOR");// = 'Processor 39.16 (INAF/IASF Bologna) - 1.2.1' / Program that created t
kn.push_back("CREAT_ID");//= '3916    '           / Unique ID of the creator
kn.push_back("FILENAME");//= '/data/gs/commiss_001/temp_arch/LV1/002001/PKP002001_1_3916_000.lv1'
kn.push_back("FILEVER");// = '5       '           / File version (GTB)
kn.push_back("DATE");//    = '2007-09-12T05:05:07' / FITS File creation date (GTB)
kn.push_back("TM_ID");//   = '39.16 - GPS Data Report' / Telemetry identifier (GTB)
kn.push_back("DATE-OBS");//= '2001-03-27T16:23:29' / Date and time of observation start (GTB)
kn.push_back("DATE-END");//= '2001-03-27T18:20:46' / Date and time of observation stop (GTB)
kn.push_back("TIMESYS");// = 'UTC     '           / Time System
kn.push_back("CLOCKAPP");//=                    F / Time corrected for clock drift?
kn.push_back("MJDREF");//  =               53005. / MJD 01 Jan 2004 00:00:00
kn.push_back("TIMEZERO");//=          -756950400.
kn.push_back("TIMEUNIT");//= 's       '           / Time unit
kn.push_back("TSTART");//  =     873602341.552704 / Start time
kn.push_back("TSTOP");//   =     873608102.560032 / Stop time
kn.push_back("ORIGIN");//  = 'IASF-BO '           / Source of the FITS file
kn.push_back("BUILDVER");//= 'TMPPS009'           / Build version of the system
kn.push_back("AGILECON");//= '-1      '           / AGILE On-Board configuration ID
kn.push_back("CHECKSUM");//
kn.push_back("DATASUM");//
kn.push_back("TSTART");//
kn.push_back("TSTOP");//
kn.push_back("DATE-OBS");//
kn.push_back("DATE-END");//
//kv.reserve(kn.size());

	pp->readKeys(kn, kv);
		
		double tempd = 0.;
	
		string ff("TSTART");
		Keyword &mykey = pp->keyWord (ff);
		if (verbose) cout << "SADataCorrector::process() read keyword keyword " << mykey.name()<< endl;
		if (verbose) cout << "SADataCorrector::process() that has comment " << mykey.comment()<< endl;
		if (verbose) cout << "SADataCorrector::process() name was " << ff << endl;
		if (verbose) cout << "SADataCorrector::process() complete string " << mykey << endl;
		if (verbose) cout << "SADataCorrector::process() value = " << mykey.value(tempd) << endl;
		
		vector<string>::iterator jt = kn.begin();
		vector<double>::iterator it = kv.begin();
		while(it != kv.end()){
			if (verbose) cout << "kn[" << (jt-kn.begin())-1<< "] = " << *jt++ << " kv[" << (it-kv.begin())-1<< "] = " << *it++<< endl;
		}
		double timezero_sec;
		timezero_sec = -756950400.;
		tempd += timezero_sec;

		mykey.setValue(tempd);
		
//#- Reorganized and improved keyword modification functions in HDU and
//#Keyword classes.  This includes new HDU addKey, copyAllKeys, and
//#keywordCategories functions, and the removal of HDU::setKeyWord.  
//#Also fully implemented the Keyword value set function, with template
//#specialization similar to the value get function, and added doc
//#descriptions for both of these. (01/08)

		//#### NB TO BE CORRECTED for the new version of ccfits
		//		pp->setKeyWord (ff, mykey);
//		mykey = pp->keyWord (ff);
		

		ff = "TSTOP";
		Keyword &mykey2 = pp->keyWord (ff);
		

		tempd += timezero_sec;

		mykey2.setValue(tempd);
		//#### NB TO BE CORRECTED for the new version of ccfits
		//pp->setKeyWord (ff, mykey2);
		mykey2 = pp->keyWord (ff);


	 try{
      if (verbose) cout << "SAFitsHandler::openOutputFile() going to create new FITS object, filename is "<< ofn << endl;
    	poutFile2 = new FITS(ofn,Write); 
    } catch(CCfits::FitsException& c){
      cerr << "SAFitsHandler::openOutputFile() error in creating the outputfile "<< endl;
      cerr << "does the file exist yet? "<< endl;
      cerr << "have you the right permissions to write? "<< endl;      
      tempstring = "ls -lht "+ofn;
      system(tempstring.c_str());     
    } catch(const exception &e){
      cerr << "caught exception "<< e.what() << endl;      
    }

		PHDU *opp;
	
		opp = &poutFile2->pHDU();

		ss.setf(ios::fixed,ios::floatfield);
		ff = "TSTART"; string c("start time"); 
		ss.str(""); ss << mykey.value(tempd); tempstring = ss.str();
		opp->addKey(ff, tempstring, c);
		ff = "TSTOP"; c = "stop time"; 
		ss.str(""); ss << mykey2.value(tempd); tempstring = ss.str();
		opp->addKey(ff, tempstring, c);

		//BinTable ext1(pinFile, 0);
		ExtHDU &ext1 =  pinFile->extension(hdus[0]) ;
		//ext1.initRead ();
		ext1.makeThisCurrent();
		ext1.readKeys(kn, kv);
		string hff("TSTART");
		Keyword &mykey4 = ext1.keyWord(hff);
		tempd = 1.1111;
		mykey4.setValue(tempd);
		//#### NB TO BE CORRECTED for the new version of ccfits
//		ext1.setKeyWord (hff, mykey4);
		
		fitsfile* inPtr = pp->fitsPointer();
		char * outf = "outtest.fits";
		   if (fits_create_file(&outfptr, outf, &status)) // create FITS file
         printerror( status );           // call printerror if error occurs 


		poutFile2->copy (ext1);
		
		poutFile2->destroy();
		exit(0);
	
}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << "SADataCorrector::process() I can't get the primary HDU (header) \n" ;
       std::cerr << "SADataCorrector::process() Perhaps you don't have opened the fitsfile! \n" ;
       
} catch (const exception &e){
	cerr << "SADataCorrector::process() error in processing FITS file "<< e.what() << endl;
}


 }
 
 	void SADataCorrector::addKeyword(const string &keyname, int keytype, string keyval){
	}
	
	void SADataCorrector::setKeyword(int hdunum, const string &keyname, int keytype, string keyval){
		float t; double d;	PHDU *pp; ExtHDU *hh; string c("");
		vector<string>::iterator jt ;
		vector<double>::iterator it ;

		if(hdunum==1){
		  pp = &pinFile->pHDU();
		} else{
		  hh = &pinFile->extension(hdus[hdunum]);
		}
		switch (keytype) {
		case 1:
		break;
		case 31:
		break;
		case 82:
		kn.clear();kt.clear();kv.clear();	
		kn.push_back(keyname);
    		kt.push_back(keytype);
		if (verbose) cout << "SADataCorrector::process() keyval = "<< keyval << endl;
		//pp->readKeys(kn, kv);
		d = atof(keyval.c_str());//d = double(t);
		kv.push_back(d);

		jt = kn.begin();
		it = kv.begin(); int yy ;
		while(jt < kn.end()){
			yy = (jt-kn.begin())-1;
			if (verbose) cout << "kn[" << (jt-kn.begin())-1<< "] = " << *jt++ << " kv[" << (it-kv.begin())-1<< "] = " << *it++<< endl;
		}
		
		break;
		default:
		break;			
		}

	}
		
	void SADataCorrector::deleteKeyword(const string &keyname, int keytype){
	}
		
	string SADataCorrector::getKeyValue(const string &keyname, int keytype){
		//keyvec.push_back();
	

	if (verbose) cout << "SADataCorrector::process() executing SADataCorrector::getKeyValue()" << endl;

            fitsfile *infptr;      /* pointer to the FITS file, defined in fitsio.h */
            fitsfile *outfptr;                 /* pointer to the new FITS file      */

   
      char komm[80]; 
      double mytstart; double mytstop;
      mytstart = 0.; mytstop = 0.;

      char *val;
      char *card;
      double timezero_sec;
      timezero_sec = -756950400.;
        int nkeys, keypos, ii;  /* MUST initialize status */   
	int status = 0;
	if (verbose) cout << "SADataCorrector::getKeyValue() going to open " << infile << endl;
    if ( fits_open_file(&infptr, infile.c_str(), READONLY, &status) )
         printerror( status );

	if (verbose) cout << "SADataCorrector::getKeyValue() infile is open " << endl;
/*
  int fits_read_key_[log, lng, flt, dbl, cmp, dblcmp] / ffgky[ljedcm]
      (fitsfile *fptr, char *keyname, > DTYPE *numval, char *comment,
       int *status)
*/

    if (fits_read_key(infptr, TDOUBLE, (char *)keyname.c_str(), &mytstart, komm, &status)) 
		printerror( status );


	if (verbose) cout << "komment = " << komm << endl;
	if (verbose) cout << "value = " << mytstart << endl;
	
	stringstream ss ; ss.str("");ss << mytstart; 
	
	mystring = ss.str();

	 if (fits_close_file(infptr, &status)) printerror(status);
	
	return mystring;
	}
	

	void SADataCorrector::save(const string &fn, const string &ofn){
try{
    if ( fits_open_file(&infptr, fn.c_str(), READONLY, &status) )
         printerror( status );
	hdutype = 0; morekeys = 0;
	mfi = 53005.;
	 mff = 0.00075444444444444;
	 tz = 0.;
	status = 0;	 nkeys = 0;
		
    if (fits_create_file(&outfptr, ofn.c_str(), &status)) // create FITS file
         printerror( status );           // call printerror if error occurs 
		
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );
	
	float t; double d;
	vector<string>::iterator si = kn.begin();
	vector<double>::iterator di = kv.begin();
	vector<int>::iterator ii = kt.begin();
	
	vector<string>::iterator si2 = kn.begin();
	vector<double>::iterator di2 = kv.begin();
	vector<int>::iterator ii2 = kt.begin();
	
	while (si<kn.end()){
		//t = atof(tempstring2.c_str());
		d = *di;
		tempstring = *si;
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)"start time", &status) ) printerror( status );
		si++; di++; ii++;
	}
	
	 si = kn.begin();
	 di = kv.begin();
	 ii = kt.begin();

try {
	if (verbose) cout << "SADataCorrector::save() going to copying extension 2" << endl;

    if ( fits_movabs_hdu(infptr, 2, &hdutype, &status) )
         printerror( status );

    // copy 3rd HDU from the input file to the output file (to 2nd HDU) 
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );

	while (si<kn.end()){
		//t = atof(tempstring2.c_str());
		d = *di;
		tempstring = *si;
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)"start time", &status) ) printerror( status );
		si++; di++; ii++;
	}

	 si = kn.begin();
	 di = kv.begin();
	 ii = kt.begin();

	if (verbose) cout << "SADataCorrector::save() extension 2 copied" << endl;
} catch(CCfits::FitsException& c){
     cerr << "SAFitsHandler::openInputFile() error in saving the 2d extension "<< endl;
}
	if (verbose) cout << "SADataCorrector::save() going to copy extension 3" << endl;

try{
    if ( fits_movabs_hdu(infptr, 3, &hdutype, &status) )
         printerror( status );

    // copy 3rd HDU from the input file to the output file (to 2nd HDU) 
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );

	while (si<kn.end()){
		//t = atof(tempstring2.c_str());
		d = *di;
		tempstring = *si;
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)"start time", &status) ) printerror( status );
		si++; di++; ii++;
	}

	 si = kn.begin();
	 di = kv.begin();
	 ii = kt.begin();
} catch(CCfits::FitsException& c){
     cerr << "SAFitsHandler::openInputFile() error in saving the 3d extension "<< endl;
} catch(const exception &e){
	cerr << "error in copying the 2rd extension" << e.what() << endl;
}

	if (verbose)	cout << "SADataCorrector::save() extension 3 copied" << endl;

	if (verbose) cout << "going to close input & output files"  << endl;

	if (fits_close_file(infptr, &status)) printerror(status);
    if (fits_close_file(outfptr, &status)) printerror(status);

	if (verbose) cout << "corrected file copied and saved"  << endl;

} catch(CCfits::FitsException& c){
     cerr << "SAFitsHandler::openInputFile() error in saving the outputfile "<< endl;
  }  
	}

void SADataCorrector::process2(const string &fn, const string &ofn){
setInputFileName(fn);
setOutputFileName(ofn);
openInputFile();	
//openOutputFile();	

    //    fitsfile * in;	   
	int mystatus = 0;
         
         // This call reads just the header 
	FITS *poutFile2;

	
	const char * b = fn.c_str(); 
		
		
		if (verbose) cout << pinFile->pHDU() << endl;
 		if (verbose) cout << "stampata la primary HDU" << endl;
		PHDU *pp;
		pp = &pinFile->pHDU();
		//PHDU pp(pinFile->pHDU());
		//pp = pinFile->pHDU();
   	    if (verbose) cout << *pp << endl;
 		if (verbose) cout << "stampata la primary HDU" << endl;
   	    //if (verbose) cout << pinFile->extension(hdus[0]) << endl;
		//if (verbose) cout << "stampata HDU[0]" << endl;
		//if (verbose) cout << pinFile->extension(hdus[1]) << endl;
		//if (verbose) cout << "stampata HDU[1]" << endl;
		
		

 	vector<string> kn; //keyword names
	/** */
	vector<double> kv;  //keyword values
	  char komm[256];	char s[32]; 
      double mytstart; double mytstop;
      mytstart = 0.; mytstop = 0.;
		int nkeys;

      char val[256];
      char card[256];


         vector<string> pk;
         const string GLOBAL("");
//         std::auto_ptr<FITS> pInfile;
//         ExtHDU = &inFile.pHDU() ;


try
{
	
	
	
	
         //std::auto_ptr<FITS> pInfile(new FITS(infile,Read,true ));
         //FITS inFile(infile);
         //PHDU& phdu = inFile.pHDU();
kn.push_back("TELESCOP");
kn.push_back("INSTRUME");//= 'PDHU    '           / Instrument of the telescope (OGIP/93-013)
kn.push_back("DETNAM");//  = 'GPS     '           / Detector of the instrument (OGIP/93-013)
kn.push_back("OBS_ID");//  =                 2001 / Observation ID (OGIP/94-001)
kn.push_back("OBS_MODE");//=                      / TBD - Observation mode (OGIP/94-001)
kn.push_back("DATAMODE");//=                      / TBD - Detector Operating Mode (OGIP/94-001)
kn.push_back("APID");//    =                  767 / Application Process ID
kn.push_back("PKTTYPE");// =                   39 / Packet Type
kn.push_back("PKTSTYPE");//=                   16 / Packet Sub-Type
kn.push_back("CONTNUMB");//=                 2001 / Contact Number (progressive within a contact)
kn.push_back("CENTURY");// =                   32 / Valid Century value
kn.push_back("MODEL");//   = 'Satellite'          / Model of the DETNAM (GTB)
kn.push_back("TESTLEVE");//= 'GS      '           / Test level of the MODEL (GTB)
kn.push_back("TE_NAME");// = 'PDHU_FUMO_TE'       / Name of the Test Equipment used (GTB)
kn.push_back("CAMPAIGN");//= 'BO      '           / Campaign (location) of the acquisition (GTB)
kn.push_back("PERIOD");//  = 'Oct_2006'           / Period of the campaign (GTB)
kn.push_back("CREATOR");// = 'Processor 39.16 (INAF/IASF Bologna) - 1.2.1' / Program that created t
kn.push_back("CREAT_ID");//= '3916    '           / Unique ID of the creator
kn.push_back("FILENAME");//= '/data/gs/commiss_001/temp_arch/LV1/002001/PKP002001_1_3916_000.lv1'
kn.push_back("FILEVER");// = '5       '           / File version (GTB)
kn.push_back("DATE");//    = '2007-09-12T05:05:07' / FITS File creation date (GTB)
kn.push_back("TM_ID");//   = '39.16 - GPS Data Report' / Telemetry identifier (GTB)
kn.push_back("DATE-OBS");//= '2001-03-27T16:23:29' / Date and time of observation start (GTB)
kn.push_back("DATE-END");//= '2001-03-27T18:20:46' / Date and time of observation stop (GTB)
kn.push_back("TIMESYS");// = 'UTC     '           / Time System
kn.push_back("CLOCKAPP");//=                    F / Time corrected for clock drift?
kn.push_back("MJDREF");//  =               53005. / MJD 01 Jan 2004 00:00:00
kn.push_back("TIMEZERO");//=          -756950400.
kn.push_back("TIMEUNIT");//= 's       '           / Time unit
kn.push_back("TSTART");//  =     873602341.552704 / Start time
kn.push_back("TSTOP");//   =     873608102.560032 / Stop time
kn.push_back("ORIGIN");//  = 'IASF-BO '           / Source of the FITS file
kn.push_back("BUILDVER");//= 'TMPPS009'           / Build version of the system
kn.push_back("AGILECON");//= '-1      '           / AGILE On-Board configuration ID
kn.push_back("CHECKSUM");//
kn.push_back("DATASUM");//
kn.push_back("TSTART");//
kn.push_back("TSTOP");//
//kv.reserve(kn.size());

	pp->readKeys(kn, kv);
		
		double tempd = 0.;
	
		string ff("TSTART");
		Keyword &mykey = pp->keyWord (ff);
		if (verbose) cout << "ho letto la keyword " << mykey.name()<< endl;
		if (verbose) cout << "che ha commento " << mykey.comment()<< endl;
		if (verbose) cout << "il suo nome era " << ff << endl;
		if (verbose) cout << "stringa completa " << mykey << endl;
		if (verbose) cout << "il suo valore " << mykey.value(tempd) << endl;
		vector<string>::iterator jt = kn.begin();
		vector<double>::iterator it = kv.begin();
		while(it != kv.end()){
			if (verbose) cout << "kn[" << (jt-kn.begin())-1<< "] = " << *jt++ << " kv[" << (it-kv.begin())-1<< "] = " << *it++<< endl;
		}


}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " I can't get the primary HDU (header) \n" ;
       std::cerr << " Perhaps you don't have opened the fitsfile! \n" ;
       
} catch (const exception &e){
	cerr << "error in processing FITS file "<< e.what() << endl;
}

}


void SADataCorrector::process3(const string &fn, const string &ofn){
		 if (verbose) cout << "executing process3"<< endl;
         const string EXTNAME("PACKETS");
         
         // read a particular HDU within the file. This call reads just the header 
         // information from SPECTRUM
         
         std::auto_ptr<FITS> pInfile(new FITS(fn.c_str(),Read,EXTNAME));
         
         // define a reference for clarity.
         
         //ExtHDU& table = pInfile->extension(EXTNAME);
         
         // read all the keywords, excluding those associated with columns.
         
         //table.readAllKeys();

}
	
/*!
    \fn SADataCorrector::setInputFileName(const string &fn)
 */
void SADataCorrector::setInputFileName(const string &fn)
{
    infile = fn;
}


/*!
    \fn SADataCorrector::getTstart()
 */
double SADataCorrector::getTstart()
{

		//keyvec.push_back();
	string keyname("TSTART");
	

	if (verbose) cout << "executing SADataCorrector::getKeyValue()" << endl;

            fitsfile *infptr;      /* pointer to the FITS file, defined in fitsio.h */
            fitsfile *outfptr;                 /* pointer to the new FITS file      */

   
      char komm[80]; 
      double mytstart; double mytstop;
      mytstart = 0.; mytstop = 0.;

      char *val;
      char *card;
      double timezero_sec;
      timezero_sec = -756950400.;
        int nkeys, keypos, ii;  /* MUST initialize status */   
	int status = 0;
	if (verbose) cout << "SADataCorrector::getKeyValue() going to open " << infile<< endl;
    if ( fits_open_file(&infptr, infile.c_str(), READONLY, &status) )
         printerror( status );

	if (verbose) cout << "SADataCorrector::getKeyValue() infile is open " << endl;
/*
  int fits_read_key_[log, lng, flt, dbl, cmp, dblcmp] / ffgky[ljedcm]
      (fitsfile *fptr, char *keyname, > DTYPE *numval, char *comment,
       int *status)
*/

    if (fits_read_key(infptr, TDOUBLE, (char *)keyname.c_str(), &mytstart, komm, &status)) 
		printerror( status );


	if (verbose) cout << "komment = " << komm << endl;
	if (verbose) cout << "value = " << mytstart << endl;
	


	 if (fits_close_file(infptr, &status)) printerror(status);
	
	return mytstart;

}


/*!
    \fn SADataCorrector::getTstop()
 */
double SADataCorrector::getTstop()
{
	
	string keyname("TSTOP");
	if (verbose) cout << "executing SADataCorrector::getKeyValue()" << endl;

            fitsfile *infptr;      /* pointer to the FITS file, defined in fitsio.h */
            fitsfile *outfptr;                 /* pointer to the new FITS file      */

   
      char komm[80]; 
      double mytstart; double mytstop;
      mytstart = 0.; mytstop = 0.;

      char *val;
      char *card;
      double timezero_sec;
      timezero_sec = -756950400.;
        int nkeys, keypos, ii;  /* MUST initialize status */   
	int status = 0;
	if (verbose) cout << "SADataCorrector::getKeyValue() going to open " << infile<< endl;
    if ( fits_open_file(&infptr, infile.c_str(), READONLY, &status) )
         printerror( status );

	if (verbose) cout << "SADataCorrector::getKeyValue() infile is open " << endl;

    if (fits_read_key(infptr, TDOUBLE, (char *)keyname.c_str(), &mytstart, komm, &status)) 
		printerror( status );


	if (verbose) cout << "komment = " << komm << endl;
	if (verbose) cout << "value = " << mytstart << endl;
	


	 if (fits_close_file(infptr, &status)) printerror(status);
	
	return mytstart;
}
}
/*
  int fits_read_key_[log, lng, flt, dbl, cmp, dblcmp] / ffgky[ljedcm]
      (fitsfile *fptr, char *keyname, > DTYPE *numval, char *comment,
       int *status)
*/


/*!
    \fn DataCorrection::SADataCorrector::CorrectTDS()
 */
void DataCorrection::SADataCorrector::CorrectTDS(const string &fn, const string &ofn, double tstart, double tstop)

{
	if (verbose) cout << "executing SADataCorrector::CorrectTDS() - verbose output -" << endl;
	if (verbose) cout << "executing SADataCorrector::CorrectTDS() infile = " << fn<< endl;
	if (verbose) cout << "executing SADataCorrector::CorrectTDS() outfile = " << ofn<< endl;
	if (verbose) cout << "executing SADataCorrector::CorrectTDS() tstart = " << tstart << endl;
	if (verbose) cout << "executing SADataCorrector::CorrectTDS() tstop = " << tstop << endl;

	string th(""); string ns("default");
	SAFitsHandler::setInputFileName(fn);
	SAFitsHandler::setOutputFileName(ofn);
	SAFitsHandler::openInputFile();
	stringstream myss;myss.setf(ios::fixed,ios::floatfield);
	mfi = 53005.;	 mff = 0.00075444444444444;	 tz = 0.;
	status = 0;	 nkeys = 0;	remove(ofn.c_str());            // Delete old file if it already exists 
	char komm[80]; 	double mytstart; double mytstop;
      	mytstart = 0.; mytstop = 0.;
        char *val;        char *card;
        double timezero_sec;        timezero_sec = -756950400.;
        int nkeys, keypos;   /* MUST initialize status */        char * k;
try{
  pinFile = new FITS(fn,Read);
  in_open = true;
  } catch(CCfits::FitsException& c){
     cerr << "SADataCorrector::CorrectTDS() error in opening the inputfile "<< endl;
     cerr << "SADataCorrector::CorrectTDS() perhaps the input file doesn't exist? "<< endl;     

  }

	 mfi = 53005.;
	 mff = 0.00075444444444444;
	 tz = 0.;
	 status = 0;	 nkeys = 0;
	 remove(ofn.c_str());            // Delete old file if it already exists 


		//if(fits_get_hdrspace(outfptr, &nkeys, NULL, &status)) printerror(status);
		string mykeyname, mykeyval;
		mykeyname = "TSTART"; 
		ss.str("");ss<<tstart; mykeyval = ss.str();

		setKeyword(1, mykeyname, TDOUBLE, mykeyval);

		mykeyname = "TSTOP"; 
		ss.str("");ss<<tstop; mykeyval = ss.str();

		setKeyword(1, mykeyname, TDOUBLE, mykeyval);

		if (verbose) cout << "SADataCorrector::CorrectTDS() executing SADataCorrector::Correct() going to save the output file " << endl;
try{
		save(fn, ofn);	

} catch(CCfits::FitsException& c){
     cerr << "SADataCorrector::CorrectTDS() error in copying and saving corrected file "<< endl;

  }
		SAFitsHandler::closeInputFile();

		SAFitsHandler::closeOutputFile();

		//SADataCorrector()::~SADataCorrector();

}
