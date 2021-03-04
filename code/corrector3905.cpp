/***************************************************************************
                          corrector3905.cpp  -  description
                             -------------------
    begin                : Fri Dec 14 2007
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

#include "corrector3905.h"
namespace DataCorrection{
Corrector3905::Corrector3905(){
}
Corrector3905::Corrector3905(const string &fn, const string &ofn){
     asdcflag = false;     processed = false;
     tstart = 0.;     tstop = 0.; 
     SAFitsHandler(fn, ofn);
     infilename = fn;
     outfilename = ofn;
     init();
}
Corrector3905::~Corrector3905(){
}
/*
void Corrector3905::prepare(){
  setVerbose(true);
  if (verbose) cout << "Corrector3905::prepare() the output directory where write trigger file will be " << afilename.getTriggerFileName() << endl;
  afilename.setAbsoluteFileName(infilename);
  afilename.update();
  afilename.setTrigBase("cnt");
  afilename.setCorrectorVersion("001");
  afilename.setTriggerExtension("ok");
  afilename.updateTrigger();
  afilename.show();
  string tt; tt = retrieveTrigEnvVar();
  CORR_INDIR =  tt;
  if (verbose) cout << "I will write the OK trigger filename in the directory " << CORR_INDIR << endl;
  if (verbose) cout << "Corrector3905::prepare() the OK file name will be " << afilename.getTriggerFileName() << endl;
  afilename.showTrigger();
  //removeOldOutfile();
  //openInputFile();
  //openOutputFile();
  //setVerbose(false);  
}
*/


}


/*!
    \fn DataCorrection::Corrector3905::Correct3905()
 */
void DataCorrection::Corrector3905::Correct3905(const string &fn, const string &ofn, double tstart, double tstop)
{
	verbose = true;
	if (verbose) cout << "executing Corrector3905::Correct3905() - verbose output -" << endl;
	if (verbose) cout << "executing Corrector3905::Correct3905() infile = " << fn<< endl;
	if (verbose) cout << "executing Corrector3905::Correct3905() outfile = " << ofn<< endl;
	if (verbose) cout << "executing Corrector3905::Correct3905() tstart = " << tstart << endl;
	if (verbose) cout << "executing Corrector3905::Correct3905() tstop = " << tstop << endl;

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
     cerr << "Corrector3905::Correct3905() error in opening the inputfile "<< endl;
     cerr << "perhaps the input file doesn't exist? "<< endl;     

  }

		float t; double d;	PHDU *pp; ExtHDU *hh; string c("");
		vector<string>::iterator jt;	vector<double>::iterator it;	vector<int>::iterator ii ; vector<string>::iterator ic ;
		int mykeytype = TDOUBLE;SADateTime sdt; vector<string>::iterator svt;

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
		
		if (verbose) cout << "Corrector3905::Correct3905() keyval = "<< mykeyval << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keytype = "<< mykeytype << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keycomment = "<< mykeycomment << endl;
		//pp->readKeys(kn, kv);
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);sv.push_back(ns);

		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
			if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				
				//cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
			ii++; jt++;ic++;it++;svt++;
		}

//		setKeyword(1, mykeyname, TDOUBLE, mykeyval);
		if (verbose) cout << "Corrector3905::Correct3905() set key 1 TSTART"<< endl;

		mykeyname = "TSTOP"; 
		myss.str("");myss<<tstop; mykeyval = myss.str();

		mykeycomment = "stop time";

		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);sv.push_back(ns);svt = sv.begin();

		if (verbose) cout << "Corrector3905::Correct3905() keyval = "<< mykeyval << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keytype = "<< mykeytype << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keycomment = "<< mykeycomment << endl; 
		//pp->readKeys(kn, kv);
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);sv.push_back(ns);

		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
			if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;

				//cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
			ii++; jt++;ic++;it++;svt++;
		}

		//setKeyword(1, mykeyname, TDOUBLE, mykeyval);
		if (verbose) cout << "Corrector3905::Correct3905() set key 2 TSTOP"<< endl;

		mykeyname = "DATE-OBS";
		mykeytype = TSTRING; 
		myss.str("");myss<<sdt.getDateTime(); mykeyval = myss.str();

		mykeycomment = "date-time of observation start";

		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);
		if (verbose) cout << "Corrector3905::Correct3905() keyval = "<< mykeyval << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keytype = "<< mykeytype << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keycomment = "<< mykeycomment << endl; 
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);sv.push_back(ns);
		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
			if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *svt << " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;

				//cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
			ii++; jt++;ic++;it++;svt++;
		}
		if (verbose) cout << "Corrector3905::Correct3905() set key 3 DATE-OBS"<< endl;
		
		mykeyname = "DATE-END"; 
		mykeytype = TSTRING; 
		myss.str("");myss<<sdt.getDateTime(); mykeyval = myss.str();

		mykeycomment = "date-time of observation end";
		kn.push_back(mykeyname);kt.push_back(mykeytype);kc.push_back(mykeycomment);
		if (verbose) cout << "Corrector3905::Correct3905() keyval = "<< mykeyval << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keytype = "<< mykeytype << endl;
		if (verbose) cout << "Corrector3905::Correct3905() keycomment = "<< mykeycomment << endl; 
		d = atof(mykeyval.c_str());//d = double(t);
		kv.push_back(d);

		ii = kt.begin(); jt = kn.begin();it = kv.begin(); ic = kc.begin(); svt = sv.begin();
		
		while(jt < kn.end()){
			if (verbose){
				if (*ii == TDOUBLE){ 
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;
				} else {
				if (*ii == TSTRING) {
				cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())<< "] = " << *jt << " ; keyvalue[" << (it-kv.begin())<< "] = " << *svt << " ; keycomment[" << (it-kv.begin())<< "] = " << *ic<<endl;

				//cout << "Corrector3905::Correct3905() keyname[" << (jt-kn.begin())-1<< "] = " << *jt << " ; keyvalue[" << (svt-kv.begin())-1<< "] = " << *it<< " ; keycomment[" << (it-kv.begin())-1<< "] = " << *ic<<endl;
				}
				}
				}
			ii++; jt++;ic++;it++;svt++;
		}
		if (verbose) cout << "Corrector3905::Correct3905() set key 3 DATE-END"<< endl;
		
		
	fitsfile *infptr;      // pointer to the FITS file, defined in fitsio.h 
	fitsfile *outfptr;     // pointer to the new FITS file      
try{
    if ( fits_open_file(&infptr, fn.c_str(), READONLY, &status) )
         printerror( status );
	hdutype = 0; morekeys = 0;
	mfi = 53005.;
	mff = 0.00075444444444444;
	tz = 0.;
	status = 0;	 nkeys = 0;

	// Processing primary HDU
			
    if (fits_create_file(&outfptr, ofn.c_str(), &status)) // create FITS file
         printerror( status );           // call printerror if error occurs 
		
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );
	 
	 
       k = (char *)"TIMEZERO";
      if ( fits_delete_key(outfptr, k,  &status)) {
        printerror(status);
        throw e;
       };

     k = (char *)"TIMESYS";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       };                   
	k = (char *)"MJDREF";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       }; 
	
       
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
	 
    if ( fits_movabs_hdu(infptr, 2, &hdutype, &status) )
         printerror( status );

    // copy 3rd HDU from the input file to the output file (to 2nd HDU) 
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );

	 
       k = (char *)"TIMEZERO";
      if ( fits_delete_key(outfptr, k,  &status)) {
        printerror(status);
        throw e;
       };

     k = (char *)"TIMESYS";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       };                   
	k = (char *)"MJDREF";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       }; 
	         
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


	 
	// correct time column
	long int nrows = 0;	long int ij=0;
        int hdunum,  nfound, anynull;
        int frow, felem, nelem, longnull;
        float floatnull;        double Doublenull;
	 
   	fits_get_num_rows(infptr, &nrows, &status);


    if (verbose) cout << "Corrector3905::Correct3905()  number of rows " << nrows << endl;
	// correct time
      frow      = 1; felem     = 1;       nelem     = nrows;
      longnull  = 0;      floatnull = 0.;      Doublenull = 0.;
      timezero_sec = -756950400.;

     double *loc_time = new double[nrows];
     memset((void *)loc_time , 0, nrows*sizeof(double));

     if(fits_read_col(infptr, TDOUBLE, 20, frow, felem, nelem, &anynull,  loc_time,
                    &anynull, &status)) printerror(status);
     for (ij = 0; ij < nrows; ij++){

//      list[ii]->setPaktnumb((unsigned long int)loc_paktnumb[ij]);
      if ((verbose)&&(ij<10)) cout << "Corrector3905::Correct3905()  old time =  " << loc_time[ij] << endl;
	loc_time[ij] = loc_time[ij] + timezero_sec;
      if ((verbose)&&(ij<10)) cout << "Corrector3905::Correct3905()  corrected time =  " << loc_time[ij] << endl;

     }

  double temps;

  
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
     
   if(fits_write_col(outfptr, TDOUBLE, 20, frow, felem, (long)nrows, loc_time, &status))
            printerror(status);
	
		
		
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
	cout << "FITS data type code = "<< *ii << endl;
	if (*ii == TSTRING) {
	th = *svt;
	cout << "1 scrivo una stringa ! = " << th << endl;
	}
	if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        (char *)th.c_str(), (char *)tempstring2.c_str(), &status) ) printerror( status );
	
	}
		si++; di++; ii++; ic++;svt++;
	}

	 si = kn.begin(); di = kv.begin(); ii = kt.begin(); ic = kc.begin(); svt = sv.begin();
	 //sv = svt.begin();
	 

			 	
	// Processing third (events/images extension)  HDU

    if ( fits_movabs_hdu(infptr, 3, &hdutype, &status) )
         printerror( status );

    // copy 3rd HDU from the input file to the output file (to 2nd HDU) 
    if ( fits_copy_hdu(infptr, outfptr, morekeys, &status) )
         printerror( status );

       k = (char *)"TIMEZERO";
      if ( fits_delete_key(outfptr, k,  &status)) {
        printerror(status);
        throw e;
       };

     k = (char *)"TIMESYS";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       };                   
	k = (char *)"MJDREF";
     if ( fits_delete_key(outfptr, k,  &status)) {
       printerror(status);
       throw e;
       }; 
	         
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

    if ( fits_movabs_hdu(outfptr, 1, &hdutype, &status) )
         printerror( status );

	    /* copy all the user keywords (not the structural keywords) */
    fits_get_hdrspace(outfptr, &nkeys, NULL, &status); 


	while (si<kn.end()){
		d = *di;
		tempstring = *si;
		tempstring2 = *ic; 
	if (*ii == TDOUBLE){
		if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        &d, (char *)tempstring2.c_str(), &status) ) printerror( status );
	}
	else {
	if (*ii == TSTRING) {
	th = *svt;
	}
	if (fits_update_key(outfptr, *ii, (char *)tempstring.c_str(),
        (char *)th.c_str(), (char *)tempstring2.c_str(), &status) ) printerror( status );
	
	}
		si++; di++; ii++; ic++;svt++;
	}
	
		// read events table dimension

	 si = kn.begin(); di = kv.begin(); ii = kt.begin(); ic = kc.begin(); svt = sv.begin();

			
	if (fits_close_file(infptr, &status)) printerror(status);
        if (fits_close_file(outfptr, &status)) printerror(status);
} catch(CCfits::FitsException& c){
     cerr << "Corrector3905::Correct3905()  error in saving the outputfile "<< endl;
  }

} catch(CCfits::FitsException& c){
     cerr << "Corrector3905::Correct3905() FITS  error in correcting the file "<< endl;
  } 
//		save(fn, ofn);	
 
	if (verbose) cout << "Corrector3905::Correct3905() bench 6"<< endl;

}
