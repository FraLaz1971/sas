/***************************************************************************
                          sal3eventlist.cpp  -  description
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
#include "sal3eventlist.h"
//SampleHistogram zz(0, 1535, 1);

using namespace SAdata;

namespace SAdata{

 using namespace CCfits;

SAL3Eventlist::SAL3Eventlist(){
 if (verbose) cout << "executing SAL3Eventlist() constructor "<< endl;
  definfile = "../stg_2/attitude/version_for_sasoa/bin/prova_outfile_L3.evt";
  infile.assign(definfile);
  outfile = "";
  init();
  fcntr = 0;
  xx_xg.resize(1024, 0);
  yy_xg.resize(1024, 0);
  xx_zg.resize(1024, 0);
  yy_zg.resize(1024), 0;  
}

SAL3Eventlist::SAL3Eventlist(const string &fn){
  definfile = fn;
  setInputFilename(fn);
  outfile = "";
  sapoint.setDefault();
  init();
  fcntr = 0;
  xx_xg.resize(1024, 0);
  yy_xg.resize(1024, 0);
  xx_zg.resize(1024, 0);
  yy_zg.resize(1024), 0;  
//  setDebug(false);
}

SAL3Eventlist::~SAL3Eventlist(){
}

/** No descriptions */
void SAdata::SAL3Eventlist::read(const string &infilename){
        tm.start();
       if (verbose) cout << "SAL3Eventlist::read() executing " << endl;
        fitsfile * in = (fitsfile*) new fitsfile[1];
       if (verbose) cout << "SAL3Eventlist::read() created input fitsfile object (cfitsio)" << endl;
         //verbose = false;
try
{
     // read a table and explicitly read selected columns. To read instead all the
     // data on construction, set the last argument of the FITS constructor
     // call to 'true'. This functionality was tested in the last release

     std::vector<string> hdus(2) ;

     std::vector<long int> pp;  

     std::vector<short int> ss;
          
     std::vector<long long int> ll;

     std::vector<unsigned char> bb;

     std::vector<float> ff;
     
     int k;
     int ncols;
     long nrows = 0;
     int colnum = 0;
     unsigned long long int * cftime;
     int status = 0;
     
     hdus[1] = "EVENTS" ;
     
     std::auto_ptr<FITS> pInfile(new FITS(infile,Read,hdus,false));

//     FITS *pInfile = new FITS(infile,Read,hdus,false);

     ExtHDU& table = pInfile->extension(hdus[1]) ;

    // fitsfile * input = (fitsfile*)&pInfile;

    fits_open_file(&in, infile.c_str(), READONLY, &status);
   if (verbose) cout << "SAL3Eventlist::read() fitsfile is open (cfitsio)" << endl;
    fits_movabs_hdu(in, 2, NULL, &status);
   if (verbose) cout << "SAL3Eventlist::read() reached extension 2 (cfitsio)" << endl;

   	fits_get_num_rows(in, &nrows, &status);
   if (verbose) cout << "SAL3Eventlist::read() number of rows " << nrows << endl;
	fits_get_num_cols(in, &ncols, &status);
   if (verbose) cout << "SAL3Eventlist::read() number of cols " << ncols << endl;
     dimension = nrows; // dimension of the external eventlist structure
    dim = nrows;  // dimension of the dim field of the eventlist
//

   try {
    
     table.column("COUNT").read(pp, 1, dimension ) ;
     unsigned int  i=0;
     while(i< dimension){
     if (verbose)      cout <<  "COUNT = " << pp[i] << endl;
       COUNT[i] = pp[i];
      i++ ;
     }
       if (verbose) cout << "read COUNT column " << endl;

     pp.resize(0);
     
     table.column("PHOTON_ID").read(pp, 1, dimension) ;
      i=0;
     while(i< dimension){
      if (verbose) cout <<  "PHOTON_ID = " << pp[i] << endl;
       PHOTON_ID[i] = pp[i];
      i++ ;
     }
       if (verbose) cout << "read PHOTON_ID column " << endl;

     pp.resize(0);
}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading photon_id) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in photon_id reading \n" ;

}     
try
{

///// REMEMBER TO TEST !!!

    cftime = new unsigned long long[ dimension];
    char * ts; ts = (char *)"TIME";

	fits_get_colnum(in, 1, ts, &colnum, &status);

    // table.column("TIME").read(ll, 1, dimension ) ;
     i=0;
    fits_read_col(in, TLONGLONG, colnum, 1, 1, nrows, NULL, cftime, NULL, &status);
     while(i< dimension){
         TIME[i] = cftime[i];
//         TIME[i] = ll[i];
      if (verbose) cout <<  "TIME = " << cftime[i] << endl;
        //if((i<10)||(i>614195))cout <<  "TIME = " << cftime[i] << endl;
      if (verbose) cout <<  "TIME = " << ll[i] << endl;

      i++ ;
     }
    if (verbose) cout << "read TIME column " << endl;
    //ll.resize(0);
    delete []cftime;

} catch (CCfits::Column::InvalidDataType) {
 if (verbose) cout << "exception thrown by CCfits \n"<< endl;
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading time) \n" ;
       
//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in time reading \n" ;
  
}


try
{
      table.column("AMPLITUDE").read(ff, 1, dimension ) ;
     i=0;
     while(i< dimension){
        AMPLITUDE[i] = ff[i];
      if (verbose) cout <<  "AMPLITUDE = " << ff[i] << endl;
      i++ ;
     }
    if (verbose) cout << "read AMPLITUDE column " << endl;
    ff.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading amplitude) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in amplitude reading \n" ;

}
    try{
      
     table.column("POS").read(ss, 1, dimension ) ;
     i=0;
     while(i< dimension){
       if (ss[i]==1540) ss[i]=0;
        POS[i] = ss[i];
      if (verbose) cout <<  "POS = " << ss[i] << endl;
      i++ ;
     }
    if (verbose) cout << "read POS column " << endl;
    ss.resize(0);
}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading position) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in position reading \n" ;

}

try{
     table.column("DETECTOR").read(bb, 1,  dimension );
     i=0;
     while(i< dimension){
       DETECTOR[i] = bb[i];
      k = (int)bb[i];
      if (verbose) cout <<  "DETECTOR = " << k << endl;
      i++ ;
     }
   if (verbose) cout << "read DETECTOR column " << endl;
     bb.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading detector) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in detector reading \n" ;

}

try{
     table.column("POS_SHIFT").read(ff, 1, dimension );
     i=0;
     while(i< dimension){
      if (verbose) cout <<  "POS_SHIFT = " << ff[i] << endl;
       POS_SHIFT[i] =ff[i];
      i++ ;
     }
     if (verbose) cout << "read POS_SHIFT column " << endl;
     ff.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading POS_SHIFT) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in POS_SHIFT reading \n" ;

}

try{
     table.column("SSID").read(bb, 1,  dimension) ;
     i=0;
     while(i< dimension){       
      k = (int)bb[i];
      if (verbose) cout <<  " = " << (int)bb[i] << endl;
       SSID[i] = bb[i];
      i++ ;
     }
     if (verbose) cout << "read SSID column " << endl;
      bb.resize(0);
  delete in;
  
}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << "Fits Exception Thrown by SAL3Eventlist::read() function (reading SSID) \n" ;
}
} catch (const exception &e){
       std::cerr << " error in SSID reading \n" ;

}

  tm.stop();
  tm.report();
  //
}
/** No descriptions */
void  SAdata::SAL3Eventlist::readHeaders(const string &hduname){
         readGlobalHeader();
//        if (verbose) cout << "going to read dimension " << getInputDimension() << endl;
}
}/** No descriptions */
void SAdata::SAL3Eventlist::passData(){
  std::cout << "SAL3Eventlist::passData() passing data to the global structure"<< endl;
    int  i=0;
     while(i<3){
      //prova_.count[i] =  COUNT[i];
      i++ ;
     } 
}
 /** No descriptions */
void SAdata::SAL3Eventlist::readGlobalHeader(){
		verbose = true;
        if (verbose) cout << "executing :SAL3Eventlist::readGlobalHeader()" << endl;
        if (verbose) cout << "SAL3Eventlist::readGlobalHeader() filename = " << infile << endl;
         
try
{
         vector<string> pk;
         const string GLOBAL("");
//         std::auto_ptr<FITS> pInfile;
//         ExtHDU = &inFile.pHDU() ;


try
{
         //std::auto_ptr<FITS> pInfile(new FITS(infile,Read,true ));
         FITS inFile(infile);
         PHDU& phdu = inFile.pHDU();
         phdu.readAllKeys();
        // std::cout << phdu << std::endl;
         /** save all the requested keyword information */

        /// compile the requested keyword string vector
        kn.push_back("SANOPOLA");
        kn.push_back("SANOPOLO");
        kn.push_back("SANOPORO");


        phdu.readKeys(kn, kv);  /// read the keyword values and put them in th sa nominal pointing object

        sapoint.setDelta(kv[0]);
        sapoint.setAlfa(kv[1]);
        sapoint.setRoll(kv[2]);

       if (verbose) cout << "SANOPOLA = "<< kv[0] << endl;
       if (verbose) cout << "SANOPOLO = "<< kv[1] << endl;
       if (verbose) cout << "SANOPORO = "<< kv[2] << endl;

        sapoint.write();     

}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " I can't get the primary HDU (header) \n" ;
       std::cerr << " Perhaps you don't have opened the fitsfile! \n" ;
       
}

//         PHDU& table = pInfile->pHDU();

        // read all user-specifed, coordinate, and checksum keys in the image

         // read a particular HDU within the file. This call reads just the header
         // information from NoName

         // define a reference for clarity. (std::auto_ptr<T>::get returns a pointer
//         ExtHDU& table = pInfile->extension(GLOBAL);
         // read all the keywords, excluding those associated with columns.

      tempstring = "NoName";
//      key =  &table.CCfits::HDU::keyWord (tempstring);

/*       string camera_type;
       CCfits::ExtHDU& silly = const_cast<CCfits::ExtHDU&> (table);
       silly.readKey(tempstring, camera_type);

     if (verbose) cout << "NAXIS2 = "<< camera_type << endl;
     */
      cur=metainfo.begin();
      while(cur!= metainfo.end()){
          cout << cur->first << "\t"<< cur->second << endl;
          cur++;
      }

         
  /*       for(cur=metainfo.begin(); cur!=metainfo.end(); cur++){
              //cout << cur->first() << " = " << curr->second()  << endl;
             tempstring = cur->first();
            if (verbose) cout << temsptring << " = " << endl;
         } */
}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::readGlobalHeader() function \n" ;
}
  
}
/** No descriptions */
void SAdata::SAL3Eventlist::readTableHeader(){
          if (verbose) cout << "executing :SAL3Eventlist::readHeader()" << endl;
try
{
         const string EVENTS("EVENTS");

         // read a particular HDU within the file. This call reads just the header
         // information from EVENTS

         std::auto_ptr<FITS> pInfile(new FITS(infile,Read,EVENTS));

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
/** No descriptions */
void SAdata::SAL3Eventlist::saveMDImage(){
   unsigned char detector; // saves detnum
   float amplitude;
   unsigned short int pos;
   unsigned long int rtime;

  if (verbose) cout << "going to process "<<  dimension << " events"<< endl;
   unsigned short int nevts = (unsigned short int) dimension;
   while(nevts--){     /// loop on the L3 data structure   
    switch(detector){
      case 0:
      break;
      case 1:
      break;
      case  2:
      break;
      case 3:
      break;
      default:
      break;      
    }
   if (verbose) cout << "processed event n. " << MAXDIMENSION - nevts << endl;
     
   }
   // end of loop on the L3 data structure

}                	
/** No descriptions */
void SAdata::SAL3Eventlist::setDefault(){

   dimension = MAXDIMENSION;
 if (verbose) cout << " dimension = "<<  dimension << endl;
  /// fill l3 data structure with random data
  i = 0;
  j=0;
  srand((unsigned int)time((time_t *)NULL));
  
  while(i< dimension){
    j = (rand()%20)+1;
     COUNT[i] = j;
     PHOTON_ID[i] = j+1;
     TIME[i] = j+2;
     AMPLITUDE[i] =j+3;
     POS[i] = j+4;
     DETECTOR[i] = (j+5)%4;
     POS_SHIFT[i] = j+6;
     SSID[i] = j+7;
    i++; 
  }
     N_regions = NREGVAL  ; Nchan =  NCHANVAL;   Hist_Size = HISTSIZVAL;
     PI = M_PI;
    if (verbose) cout << "PI = "<< PI << endl;

    if (verbose) cout << "number of regions = "<< N_regions << endl;
     /** index for the sky regions */

     for(w=0; w<N_regions; w++) C_Index[w] = w;

     /**Pointing histograms */
//       gPoint_Hist_x = new float[HISTSIZVAL] ;
//       gPoint_Hist_z = new float[HISTSIZVAL] ;
     
     for(w=0; w<Hist_Size; w++){
       gPoint_Hist_x[w] = 0.;
       gPoint_Hist_z[w] = 0.;       
     }
     
     /** conversion for detector coordinates from reference system */     
     
     D_Seq[0] = 2;
     D_Seq[1] = 3;
     D_Seq[2] = 0;
     D_Seq[3] = 1;

     /** */
     max_angle = 60.;     

     /** */     
    f_length = 14.14;

     /** */
    s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;
     
     /** */
     EnMax = 100.;
     /** */
     for(w=0; w<N_regions; w++){
	   C_Angles[w] = max_angle/N_regions*(2.*w-1.)/2.;
	   C_Coeffs[w] = delta_norm*(tan(C_Angles[w]*PI/180.)-tan((C_Angles[w]-1.)*PI/180.));
	   C_Coeffs[w] = C_Coeffs[w]*1.00/0.93;
     }
           /// setting default for C_Angles and C_Coeffs
            /// setting default for  pointing histogram

//   delete [] gPoint_Hist_x;
//
//   delete [] gPoint_Hist_z;
   
            /// setting default for the detimage structure

}
/** No descriptions */
void SAdata::SAL3Eventlist::plotDetImage(int n){
}
/** No descriptions */
void SAdata::SAL3Eventlist::init(){
  if (verbose) cout << "executing SAL3Eventlist::init() "<< endl;
  isfixpsd = false;
  SAEventlist::init();
  savefiltered = false;
   try{
     tempstring = "+4.649557100000";  sapoint.setAlfa(tempstring);
     tempstring = "-0.504981300000";  sapoint.setDelta(tempstring);
     tempstring = "-2.601173200000";  sapoint.setRoll(tempstring);
  }                                                            /// Make general !
  catch (const exception &e)
  {
    cerr << "thrown exception "<< e.what() << endl;
  }
  //  setDefault();
  sapoint.setDefault();
	exposure = 0;
}
/** No descriptions */
void SAdata::SAL3Eventlist::createMDImage(){
   /** */
//   float C_Angles[NREGVAL];
   /** */
//   float C_Coeffs[NREGVAL];
   /** */
   short int C_Shifts[NREGVAL];
   /** */
   short int C_Coords[NREGVAL];   
 if (verbose) cout << "SAL3Eventlist::createMDImage() start " << endl;
      float EnMin;    float EnMax;    short int N_regions;

    float maxangle;    float f_length;    float s_width;

    float delta_norm;    int dimss;    float  Tburst;

//    verbose = true;
      verbose = false;
     /** */
    char *starts = new char[55];
   /** */
    char *cfin_out = new char[64];
   /** */
    char *cfin_p = new char[64];

 if (verbose) cout << "executing SAL3Eventlist::createMDImage()"<< endl;
        system("rm test.dat");
 if (verbose) cout << "going to write following data" << endl;

          string ss("SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR");
          string fin_out("pippo1"); // name of the file
          string fin_p("plutone2");
          starts = (char *)ss.c_str();
          i_fn_length_0 = strlen(starts);
          if (verbose) cout << "startstring has lenght "<< i_fn_length_0 << endl;
          cfin_out = "pippo1";
          cfin_p = "plutone2";
          i_fn_length_1 = strlen(cfin_out);
          i_fn_length_2  = strlen(cfin_p);
          if (verbose) cout << "going to write the string "<< cfin_out << endl;
          if (verbose) cout << "that is  "<< i_fn_length_1 << " chars long" << endl;
          Tburst = (float)PI;

          D_Seq[0] = 2;           D_Seq[1] = 3;
          D_Seq[2] = 0;           D_Seq[3] = 1;

          N_regions =  NREGVAL;  Hist_Size = HISTSIZVAL;  Nchan = NCHANVAL;

          float *C_Angles = new float[N_regions];
          float *C_Coeffs = new float[N_regions];
          float *Point_Hist_x = new float[Hist_Size];
          float *Point_Hist_z = new float[Hist_Size];

          for(w=0; w<N_regions; w++) C_Index[w] = (short int)w;


            /// Setting default values

    /** */
     max_angle = 60.;

     /** */
    f_length = 14.14;

     /** */
    s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;     EnMax = 100.;

     if (verbose) cout << "writing pointing histogram " <<  endl;

     /** */
     for(w=0; w<N_regions; w++){
	   C_Angles[w] = max_angle/N_regions*(2.*w-1.)/2.;
	   C_Coeffs[w] = delta_norm*(tan(C_Angles[w]*PI/180.)-tan((C_Angles[w]-1.)*PI/180.));
	   C_Coeffs[w] = C_Coeffs[w]*1.00/0.93;
     }

///  pointing histogram creation
float Psi_s_z;
float Psi_s_x;

Psi_s_z = 0.;
Psi_s_x = 0.;

/// loop on all the events of the eventlist
    if (verbose) cout << "loop on all the events of the eventlist" << endl;

unsigned long int c;  c = 0;


while (c< dimension){

    ev = getEvent(c); /// get the temp event

   if (verbose) {
     if (verbose) cout << "events  n " << c << endl;
     ev.show();
   }
    iside 	= 0;

    if (ev.getPos() > 767) {
	     iside = 1;
          //	   ev.getPos() = ev.getPos() - 768;
          ev.setPos(ev.getPos() - 768);
	  }

        switch(ev.getDetector()){
          case 0:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		    C_Shifts[i] = -1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
		  }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
          break;
          case 1:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]	= Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 2:
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])] = Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 3:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = -1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		  Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])] = Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          default:    /// INSERT AN EXCEPTION
           if (verbose) cout << "wrong detector number !!!" << endl;
            throw e;
          break;
        }

        for(w=0; w<N_regions; w++){
            C_Coords[C_Index[i]] = C_Shifts[C_Index[i]] + ev.getPos();
        }



        for(w=0; w<N_regions; w++){ // loop on the sky region
            cond1 = (C_Coords[C_Index[w]] >= 0);
            cond2 = (C_Coords[C_Index[w]] <= 767);
            // cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
           if (cond1 && cond2) {
            //	          if (cond3) {
  		          MDImage[C_Index[w]] [ev.getDetector()][1+C_Coords[C_Index[w]]+iside*768] += 1;
            //	          }
	        }
         }



        
//        for(w=0; w<N_regions; w++){ // loop on the sky region
//        cond1 = (C_Coords[C_Index[i]] > 0);
//        cond2 = (C_Coords[C_Index[i]] < 767);
////        cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
//        if (cond1 && cond2) {
////	          if (cond3) {
//		          MDImage[C_Index[i]] [ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768] =  MDImage[C_Index[i]][ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768]+1;
////	          }
//	        }
//         }
         
  c++;
}

cout << "SAL3Eventlist::createMDImage() stop " << endl;

}
/** No descriptions */
void SAdata::SAL3Eventlist::saveIrosMap(const string &fn){
   /** */
//   float C_Angles[NREGVAL];
   /** */
//   float C_Coeffs[NREGVAL];
   /** */
   short int C_Shifts[NREGVAL];
   /** */
   short int C_Coords[NREGVAL];   
    float EnMin;

    float EnMax;

    short int N_regions;

    float maxangle;

    float f_length;

    float s_width;

    float delta_norm;

    int dimss;

    float  Tburst;

//    verbose = true;
      verbose = false;
     /** */
    char *starts = new char[55];
   /** */
    char *cfin_out = new char[64];
   /** */
    char *cfin_p = new char[64];

 if (verbose) cout << "executing SAL3Eventlist::saveIrosMap()"<< endl;
        system("rm ../stg_2/test*.dat");
 if (verbose) cout << "going to write following data" << endl;

          string ss("SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR");
          string fin_out("pippo1"); // name of the file
          string fin_p("plutone2");

//          startstring = (char *)"SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR";
           starts = (char *)ss.c_str();           _starts = (char *)ss.c_str();

           i_fn_length_0 = strlen(starts);
           _i_fn_length_0 = i_fn_length_0;

           if (verbose) cout << "startstring �lunga "<< i_fn_length_0 << endl;
           //cfin_out =  fin_out.c_str();
           //cfin_p =  fin_p.c_str();
           cfin_out = "pippo1";           _cfin_out = cfin_out;
           cfin_p = "plutone2";                     _cfin_p = cfin_p;

           i_fn_length_1 = strlen(cfin_out);  _i_fn_length_1 = strlen(cfin_out);

           i_fn_length_2  = strlen(cfin_p);    _i_fn_length_2  = strlen(cfin_p);

           if (verbose) cout << "going to write the string "<< cfin_out << endl;
           if (verbose) cout << "that is  "<< i_fn_length_1 << " chars long" << endl;


           D_Seq[0] = 2;           D_Seq[1] = 3;           D_Seq[2] = 0;           D_Seq[3] = 1;

           N_regions =  NREGVAL;            Hist_Size = HISTSIZVAL;            Nchan = NCHANVAL;

           _N_regions =  NREGVAL;         _Hist_Size = HISTSIZVAL;           _Nchan = NCHANVAL;

           _D_Seq[0] = 2;           _D_Seq[1] = 3;           _D_Seq[2] = 0;           _D_Seq[3] = 1;

            float *C_Angles = new float[N_regions];
            float *C_Coeffs = new float[N_regions];
            float *Point_Hist_x = new float[Hist_Size];
            float *Point_Hist_z = new float[Hist_Size];

            for(w=0; w<N_regions; w++) C_Index[w] = (short int)w;
                /** IrosMap object */
            for(w=0; w<N_regions; w++) _C_Index[w] = (short int)w;

            /// Setting default values
            for(w=0; w<Hist_Size; w++) {
                 Point_Hist_x[w] = 0.;
                 Point_Hist_z[w] = 0.;
            }


    /** */
     max_angle = 60.; _max_angle = 60.;

     /** */
    f_length = 14.14;    _f_length = 14.14;

     /** */
    s_width = 0.0121;    _s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;     _delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;     _EnMin = 15.;

     /** */
     EnMax = 100.;   _EnMax = 100.;

     /** */
     Tburst = 598.975; _Tburst = 598.975;

     if (verbose) cout << "writing pointing histogram " <<  endl;

     PI = M_PI;    if (verbose) cout << "PI = "<< PI << endl;

     /** */
     for(w=1; w<N_regions+1; w++){
	   C_Angles[w-1] = max_angle/N_regions*(2.*w-1.0)/2.;
	   C_Coeffs[w-1] = delta_norm*(tan(C_Angles[w-1]*PI/180.)-tan((C_Angles[w-1]-1.)*PI/180.));
	   C_Coeffs[w-1] = C_Coeffs[w-1]*1.00/0.93;
     }

     /** _C_Angles and _C_Coeffs for IrosMapObject */
    for(w=1; w<N_regions+1; w++){
	   _C_Angles[w-1] = _max_angle/_N_regions*(2.*w-1.0)/2.;
	   _C_Coeffs[w-1] = _delta_norm*(tan(_C_Angles[w-1]*PI/180.)-tan((_C_Angles[w-1]-1.)*PI/180.));
	   _C_Coeffs[w-1] = _C_Coeffs[w-1]*1.00/0.93;
     }

///  pointing histogram creation
float Psi_s_z;      float Psi_s_x;


/// loop on all the events of the eventlist
    if (verbose) cout << "loop on all the events of the eventlist" << endl;

unsigned long int c = 0;
int a=0;
/// ###### REMEMBER TO CHANGE
// dimension = 10;
/// ###### REMEMBER TO CHANGE
   if (verbose) cout << "saveIrosMap() number of events to fill in the histogram = "<<  dimension << endl;

while (c< dimension){
    ev = getEvent(c); /// get the temp event
   // verbose = true;

   if (verbose) {
     if (verbose) cout << "events  n " << c << endl;
     ev.show();
   }
    iside 	= 0;

    if (ev.getPos() > 767) {
	     iside = 1;
          //	   ev.getPos() = ev.getPos() - 768;
          ev.setPos(ev.getPos() - 768);
	  }

        switch(ev.getDetector()){
          case 0:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<_N_regions){
		    C_Shifts[i] = -1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
		    _C_Shifts[i] = -1.*(Psi_s_z)/ PI*180.*_C_Coeffs[i];

            i++;
		  }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
		  _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])]	= _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          case 1:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<_N_regions){
		   C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
		   _C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*_C_Coeffs[i];
            i++;
          }
		Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]	= Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]+1.;
		_Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])]	= _Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          case 2:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<_N_regions){
		   C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
		   _C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*_C_Coeffs[i];
            i++;
          }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])] = Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
		  _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])] = _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          case 3:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<_N_regions){
		   _C_Shifts[i] = -1.*(Psi_s_x)/ PI*180.*_C_Coeffs[i];
            i++;
          }
		  Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])] = Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]+1.;
		  _Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])] = _Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          default:    /// INSERT AN EXCEPTION
           if (verbose) cout << "wrong detector number !!!" << endl;
          break;
        }

        for(w=0; w<N_regions; w++){
            C_Coords[C_Index[w]] = C_Shifts[C_Index[w]] + ev.getPos();
        }

        for(w=0; w<_N_regions; w++){
            _C_Coords[_C_Index[w]] = _C_Shifts[_C_Index[w]] + ev.getPos();
        }

        for(w=0; w<N_regions; w++){ // loop on the sky region
            cond1 = (C_Coords[C_Index[w]] >= 0);
            cond2 = (C_Coords[C_Index[w]] <= 767);
            // cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
           if (cond1 && cond2) {
            //	          if (cond3) {
  		          MDImage[C_Index[w]] [ev.getDetector()][1+C_Coords[C_Index[w]]+iside*768] += 1;
            //	          }
	        }
         }

        for(w=0; w<_N_regions; w++){ // loop on the sky region
            cond1 = (_C_Coords[_C_Index[w]] >= 0);
            cond2 = (_C_Coords[_C_Index[w]] <= 767);
            // cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
           if (cond1 && cond2) {
            //	          if (cond3) {
  		          _MDImage[_C_Index[w]] [ev.getDetector()][1+_C_Coords[_C_Index[w]]+iside*768] += 1;
            //	          }
	        }
         }

  c++;
}


        for(int i=0; i<1024; i++) {
          xx_xg[i] = (int)i;
          if (Point_Hist_x[i]>=0){
            yy_xg[i] = (unsigned long int)Point_Hist_x[i];
          } else yy_xg[i]=0;
        }

        for(int i=0; i<1024; i++) {
          xx_zg[i] = (int)i;
          if (Point_Hist_z[i]>=0){
            yy_zg[i] = (unsigned long int)Point_Hist_z[i];
          } else yy_zg[i] = 0;
        }

  
 if (verbose) cout << "out of the loop on events: counter  = " << c << endl;
// coordinates calculation !
///  Multi Detector Image structure filled !!

         if (verbose) cout << "N_regions = "<< N_regions << endl;
         if (verbose) cout << "N of det = "<< 4 << endl;
         if (verbose) cout << "Nchan = "<< Nchan << endl;


         if (verbose) cout << "size of  Nchan "<< sizeof(short int) << endl;
         if (verbose) cout << "size of  Hist_Size "<< sizeof(short int) << endl;

          try {
                // open file and
                fstream binary_file("../stg_2/test.dat",ios::out|ios::binary|ios::trunc);
//                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                binary_file.write(reinterpret_cast<char *>(starts), i_fn_length_0);
                if (verbose) cout << "written startstring = "<< starts << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                if (verbose) cout << "written i_fn_length_1 = "<< i_fn_length_1 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_out), i_fn_length_1);
                if (verbose) cout << "written cfin_out = "<<  cfin_out << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
                if (verbose) cout << "written i_fn_length_2 = "<< i_fn_length_2 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_p), i_fn_length_2);
                if (verbose) cout << "written cfin_p = "<< cfin_p << endl;
                binary_file.write(reinterpret_cast<char *>(&Nchan), sizeof(short int));
                if (verbose) cout << "written Nchan = "<< Nchan << endl;
                binary_file.write(reinterpret_cast<char *>(&Tburst), sizeof(float));
                if (verbose) cout << "written Tburst = "<< Tburst << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMin),sizeof(float));
               if(verbose) cout<<"written EnMin: "<< EnMin << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMax),sizeof(float));
               if(verbose) cout<<"written EnMax: "<< EnMax << endl;
                binary_file.write(reinterpret_cast<char *>(&N_regions),sizeof(short int));
               if(verbose) cout<<"written N_regions: "<< N_regions << endl;
                binary_file.write(reinterpret_cast<char *>(&max_angle),sizeof(float));
                if(verbose) cout<<"written max_angle: "<< max_angle << endl;
                binary_file.write(reinterpret_cast<char *>(&f_length),sizeof(float));
               if(verbose) cout<<"written f_length: "<< f_length << endl;
                binary_file.write(reinterpret_cast<char *>(&s_width),sizeof(float));
                if(verbose)   cout<<"write s_width: "<<  s_width << endl;
                binary_file.write(reinterpret_cast<char *>(&delta_norm),sizeof(float));
                if(verbose) cout<<"written delta_norm: "<< delta_norm << endl;

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Angles[w]),sizeof(float));
                  if(verbose) cout<<"written C_Angles, element  "<< w << " value "<< C_Angles[w] << endl;
              }

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Coeffs[w]),sizeof(float));
                  if(verbose) cout<<"written C_Coeffs, element  "<< w << " value "<< C_Coeffs[w] << endl;
              }


              binary_file.write(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));
              if(verbose) cout<<"written Hist_Size  "<< w << " value "<< Hist_Size << endl;


              for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_x[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;
             }

            for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_z[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_z, element  "<< w << " value " << Point_Hist_z[w] << endl;
            }

            for(w=0; w<4; w++){ // write detector index
              binary_file.write(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
             if (verbose) cout << "written D_Seq[w] = " << D_Seq[w] << endl;
            }

           if (verbose) cout << "SAL3Eventlist::saveIrosMap() going to write the MultiDetectorImage"<< endl;
            /// REMEMBER TO CHANGE !
            /// AND USE DEFAULT VALUES!


            if(verbose) cout << "For "<< N_regions << " regions " << endl;
            for (w=0; w<4; w++) cout << "For detector n. "<<  D_Seq[w] <<  " and then "<< endl;
            int count = 0;
            for(x=0; x<N_regions; x++){ // loop on the sky regions
            if(verbose) cout << "####  data for the sky region "<< C_Index[x]  << endl;

            binary_file.write(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int)); /// write the region index
            if(verbose) cout << " written  index region "<< C_Index[x]   << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[0]  << " det   = "<< 0  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code"<< D_Seq[0] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[0]][w]<< endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"    completed MDImage,  detector code"<< D_Seq[0]  << " det  "<< 0  <<  endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[1]  << " det   = "<< 1  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector "<< D_Seq[1] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[1]  << " det =  "<< 1  << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code"<< D_Seq[2]  << " det  "<< 2  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(int));
                    if(verbose)if (verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[2] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[2] << " det  = "<< 2 << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[3]  << " det  = "<< 3  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(int));
                    if (verbose) cout << "        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[3] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                 }

                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[3] << " det  = "<< 3 << endl;
                 cout << endl;

                if (verbose) cout << endl;
                if (verbose) cout << endl;
                if(verbose)cout << "#### completed data for the sky region index: "<<  x << endl;
                if (verbose) cout << endl;
                if (verbose) cout << endl;

//               if(verbose)cout << "written mdimage array region n. "<< count++<< endl;
            }// end of the loop on the sky regions

                if(verbose) cout << "written all data" << endl;
                binary_file.close();
       }
          catch (exception e){
          // will catch  exceptions
          // found by
            std::cerr << " SAL3Eventlist::saveIrosMap function \n" ;
//            e.handle();

          }

//
 if (verbose) cout << "SAL3Eventlist::saveIrosMap() ended!"<< endl;
    
 }


/** No descriptions */
void SAdata::SAL3Eventlist::createPointHistos(){
 if (verbose) cout << "SAL3Eventlist::createPointHistos() started"<< endl;
    verbose = false;
           
    float  Point_Hist_x[1024];
    float  Point_Hist_z[1024];

    float EnMin;    float EnMax;    short int N_regions;

    float maxangle;    float f_length;    float s_width;

    float delta_norm;    int dimss;    float  Tburst;
   /** */
//   float C_Angles[NREGVAL];
   /** */
//   float C_Coeffs[NREGVAL];
   /** */
   short int C_Shifts[NREGVAL]; for(int k=0; k< NREGVAL; k++)C_Shifts[k] = 0;
   /** */
   short int C_Coords[NREGVAL]; for(int k=0; k< NREGVAL; k++)C_Coords[k] = 0;  
 
     // verbose = false;
     /** */
    char *starts = new char[55];
   /** */
    char *cfin_out = new char[64];
   /** */
    char *cfin_p = new char[64];                                       

         /// ######## REMEMBER TO CHANGE
//          dimension = 10;
         /// ######## REMEMBER TO CHANGE

	N_regions = 10;
	Hist_Size = 1024;
 if (verbose) cout << "SAL3Eventlist::createPointHistos() executing !"<< endl;
  //      system("rm test.dat");
 if (verbose) cout << "SAL3Eventlist::createPointHistos() going to write following data" << endl;

          string ss("SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR");
          string fin_out("pippo1"); // name of the file
          string fin_p("plutone2");
          starts = (char *)ss.c_str();
           i_fn_length_0 = strlen(starts);
           if (verbose) cout << "startstring �lunga "<< i_fn_length_0 << endl;
           cfin_out = (char *)"pippo1";
           cfin_p = (char *)"plutone2";
           i_fn_length_1 = strlen(cfin_out);
           i_fn_length_2  = strlen(cfin_p);
           if (verbose) cout << "going to write the string "<< cfin_out << endl;
           if (verbose) cout << "that is  "<< i_fn_length_1 << " chars long" << endl;
           Tburst = (float)PI;

           D_Seq[0] = 2;       D_Seq[1] = 3;    D_Seq[2] = 0;       D_Seq[3] = 1;

            N_regions =  NREGVAL;   Hist_Size = HISTSIZVAL;    Nchan = NCHANVAL;

            float *C_Angles = new float[N_regions];     float *C_Coeffs = new float[N_regions];
    /*        
			float *Point_Hist_x = new float[Hist_Size];  
			float *Point_Hist_z = new float[Hist_Size];
*/
            for(w=0; w<N_regions; w++) C_Index[w] = (short int)w;
            for(int h=0; h<1024; h++){
                 Point_Hist_x[h] = 0.;
                 Point_Hist_z[h] = 0.;                 
            }

            /// Setting default values

    /** */
     max_angle = 60.;

     /** */
    f_length = 14.14;

     /** */
    s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;

     /** */
     EnMax = 100.;

     if (verbose) cout << "createPointHistos() writing pointing histogram " <<  endl;

     /** */
     for(w=0; w<N_regions; w++){
	   C_Angles[w] = max_angle/N_regions*(2.*w-1.)/2.;
	   C_Coeffs[w] = delta_norm*(tan(C_Angles[w]*PI/180.)-tan((C_Angles[w]-1.)*PI/180.));
	   C_Coeffs[w] = C_Coeffs[w]*1.00/0.93;
     }

///  pointing histogram creation
    float Psi_s_z;  float Psi_s_x;
    Psi_s_z = 0;  Psi_s_x = 0;


/// loop on all the events of the eventlist
    if (verbose) cout << "createPointHistos() loop on all the events of the eventlist" << endl;

unsigned long int c;  c = 0;

/// ###### REMEMBER TO CHANGE
// dimension = 10;
/// ###### REMEMBER TO CHANGE

SAexception se1; string ff;
while (c< dimension){

    ev = getEvent(c); /// get the temp event

 // verbose = true;
  verbose = false;
   if (verbose) {
     if (verbose) cout << "createPointHistos() events  n " << c << endl;
     if (c<100) ev.show();
   }

    iside 	= 0;
    
    if ((PI*180.*C_Coeffs[0]) == 0 ) {
	ff = "division by 0"; se1.setMsg(ff);throw se1;
    }

    if (ev.getPos() > 767) {
	     iside = 1;
          //	   ev.getPos() = ev.getPos() - 768;
          ev.setPos(ev.getPos() - 768);
	  }
	
        switch(ev.getDetector()){
          case 0:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		    C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
		  }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
          break;
          case 1:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]	= Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 2:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
          }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])] = Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 3:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = -1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		  Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])] = Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          default:    /// INSERT AN EXCEPTION
           if (verbose) cout << "wrong detector number !!!" << endl;
 	   SAexception se; string h("wrong detector number !!!"); se.setMsg(h);
	   throw(se); 
          break;
        }

        for(w=0; w<N_regions; w++){
            C_Coords[C_Index[i]] = C_Shifts[C_Index[i]] + ev.getPos();
        }

        for(w=0; w<N_regions; w++){ // loop on the sky region
        cond1 = (C_Coords[C_Index[i]] > 0);
        cond2 = (C_Coords[C_Index[i]] < 767);
//        cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
        if (cond1 && cond2) {
//	          if (cond3) {
		          MDImage[C_Index[i]] [ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768] =  MDImage[C_Index[i]][ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768]+1;
//	          }
	        }
         }
  c++;
}

        for(int i=0; i<1024; i++) {
          xx_xg[i] = (int)i;
          if (Point_Hist_x[i]>=0){          
            yy_xg[i] = (unsigned long int)Point_Hist_x[i];
          } else {
            yy_xg[i]=0;
          }
          if (verbose) cout << i << "createPointHistos() yy_xg = "<<  Point_Hist_x[i] << endl;
        }

        for(int i=0; i<1024; i++) {
          xx_zg[i] = (int)i;
          if (Point_Hist_z[i]>=0){
            yy_zg[i] = (unsigned long int)Point_Hist_z[i];
          } else {
            yy_zg[i] = 0;
          }
          if (verbose) cout << i << "createPointHistos() yy_zg = "<<  Point_Hist_z[i] << endl;
        }
        
  
/*  delete [] Point_Hist_x;
  delete [] Point_Hist_z;*/

  verbose = false;
  
 if (verbose) cout << "SAL3Eventlist::createPointHistos() ended"<< endl;
}
/** No descriptions */
void SAdata::SAL3Eventlist::readIrosMap(){
  verbose = false;
  tm.start();

//  for(int i=0; i<1024; i++) {
//          xx[i] = i;
//          yy[i] = gPoint_Hist_x[i];
//        }

  char *starts2 = new char[55]; // initial string  
  char *cfin_out2 = new char[64];  // contains fin_out variable
  char *cfin_p2 = new char[64];  // contains fin_p variable
  short int Nchan2;
  float Tburst2;
  float EnMin2;
  float EnMax2;
  short int N_regions2;
//  cout << "N_regions2 = " << N_regions2 << endl;
  float maxangle2;
  float f_length2;
  float s_width2;
  float delta_norm2;

  float *C_Angles2 = new float[N_regions2];
  float *C_Coeffs2 = new float[N_regions2];
  float *Point_Hist_x2 = new float[Hist_Size];  
  float *Point_Hist_z2 = new float[Hist_Size];
//  cout << "Hist_Size = " << Hist_Size << endl;
            string s;            stringstream ss;   
try
{
    //ifstream binary_file ("/home/lazza/flist_test_ST_Check_f19_agile.map", ios::in|ios::binary|ios::in);
    //fstream binary_file("test.dat",ios::binary|ios::in);
   if (verbose) cout << "going to open " << infile << endl;
    ifstream binary_file(infile.c_str(), ios::in | ios::binary);
   if (verbose) cout << "####################" << endl;
   if (verbose) cout << "       READ DATA    " << endl;
   if (verbose) cout << "####################" << endl;

  if (binary_file.is_open())
  {
            //binary_file.read(reinterpret_cast<char *>(starts2),55);
            binary_file.read(starts2,55);
            if (!binary_file) {
              /// if error occurred
              cerr << "error in reding the file :" << endl;
              cerr << "read " << binary_file.gcount()  << "bytes "<< endl;
              binary_file.clear();
            }
 
            if(verbose) cout<<"read startstring: "<< starts2 << endl;
           binary_file.read(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
            if(verbose) cout<<"read i_fn_length_1: "<< i_fn_length_1 << endl;            
            binary_file.read(reinterpret_cast<char *>(cfin_out2),i_fn_length_1);
            if(verbose) cout<<"read fin_out: "<< cfin_out2 << endl;
            binary_file.read(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
            if(verbose) cout<<"read i_fn_length_2: "<< i_fn_length_2 << endl;
            binary_file.read(reinterpret_cast<char *>(cfin_p2),i_fn_length_2);
            if(verbose) cout<<"read fin_p: "<< cfin_p2 << endl;  
           binary_file.read(reinterpret_cast<char *>(&Nchan2),sizeof(short int));
            if (verbose) cout<<"read Nchan: "<< Nchan2 << endl;
            binary_file.read(reinterpret_cast<char *>(&Tburst2),sizeof(float));
            if(verbose) cout<<"read Tburst: "<< Tburst2 << endl;
            binary_file.read(reinterpret_cast<char *>(&EnMin2),sizeof(float));
            if(verbose) cout<<"read EnMin: "<< EnMin2 << endl;
            binary_file.read(reinterpret_cast<char *>(&EnMax2),sizeof(float));
            if(verbose) cout<<"read EnMax: "<< EnMax2 << endl;
            binary_file.read(reinterpret_cast<char *>(&N_regions2),sizeof(short int));
           if (verbose) cout<<"read N_regions: "<< N_regions2 << endl;
            binary_file.read(reinterpret_cast<char *>(&maxangle2),sizeof(float));
            if(verbose) cout<<"read maxangle: "<< maxangle2 << endl;
            binary_file.read(reinterpret_cast<char *>(&f_length2),sizeof(float));
            if(verbose) cout<<"read f_length: "<< f_length2 << endl;
            binary_file.read(reinterpret_cast<char *>(&s_width2),sizeof(float));
//           if (verbose) cout<<"read s_width: "<<  << endl;
            binary_file.read(reinterpret_cast<char *>(&delta_norm2),sizeof(float));
            if(verbose) cout<<"read delta_norm: "<< delta_norm2 << endl;
            for(w=0; w<N_regions2; w++){
              binary_file.read(reinterpret_cast<char *>(&C_Angles2[w]),sizeof(float));
              if(verbose) cout<<"read C_Angles, element  "<< w << " value = " << C_Angles2[w] << endl;
            }
            for(w=0; w<N_regions2; w++){
             binary_file.read(reinterpret_cast<char *>(&C_Coeffs2[w]),sizeof(float));
              if(verbose) cout<<"read C_Coeffs, element  "<< w << " value = "<< C_Coeffs2[w] << endl;
 }            
            binary_file.read(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));
            if(verbose) cout<<"read Hist_Size "<< w << " value = "<< Hist_Size << endl;
           
            for(w=0; w<Hist_Size; w++){
              binary_file.read(reinterpret_cast<char *>(&gPoint_Hist_x[w]),sizeof(float));
              if(verbose) cout<<"read Point_Hist_x, element  "<< w << " value = "<< gPoint_Hist_x[w] << endl;
            }

            for(w=0; w<Hist_Size; w++){
              binary_file.read(reinterpret_cast<char *>(&gPoint_Hist_z[w]),sizeof(float));
              if(verbose) cout<<"read Point_Hist_z, element  "<< w << " value = "<< gPoint_Hist_z[w] << endl;
            }

            for(w=0; w<4; w++){ // read detector index
              binary_file.read(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
              if (verbose) cout << "D_Seq[w] = "   << D_Seq[w] << endl;
            }

           if (verbose) cout << "going to read data for regions  # "   << N_regions2 << endl;
           if (verbose) cout << "going to read data and channels  # "   << Nchan2 << endl;

            
            for(x=0; x<N_regions2; x++){ // loop on the sky regions
                binary_file.read(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int));
               if (verbose) cout << "data for the sky region " << C_Index[x] << endl;

                 /// detector 0
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[0] << " value = " << MDImage[C_Index[x]][D_Seq[0]][w] << endl;
                }// end of the loop on the strips

                 /// detector 1
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[1] << " value = " << MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                }// end of the loop on the strips


                 /// detector 2
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << " D_Seq = "  << D_Seq[2] << " value = " << MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                }// end of the loop on the strips


                 /// detector 3
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[3] << " value = " << MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                }// end of the loop on the strips

             }// end of the loop on the sky regions          

            binary_file.close();
}
  else cerr << "Unable to open file" << endl;;

  }        catch (exception e){
    cerr << "exception during binary file reading"<< endl;
}
   if (verbose) cout << "####################" << endl;
   if (verbose) cout << "       END   DATA    " << endl;
   if (verbose) cout << "####################" << endl;

   if (verbose) cout  << endl;

  tm.stop();
  tm.report();
  verbose = false;
}
/** No descriptions */
void SAdata::SAL3Eventlist::createVariables(){
}
/** No descriptions */
void SAdata::SAL3Eventlist::destroyVariables(){
}
/** No descriptions */
void SAdata::SAL3Eventlist::setInputFilename(string fn){
  infile = fn;
  //  SAFitsHandler::infilename = fn;
  //definfile = infile;
}

/** No descriptions */
void SAdata::SAL3Eventlist::getInputDimension(string fn){
}
/** No descriptions */
unsigned long SAdata::SAL3Eventlist::getInputDimension(){
       setVerbose(true);
       if (verbose) cout << "executing SAL3Eventlist::getInputDimension() " << endl;
       const string EVENTS("EVENTS");
       stringstream f;       f << infile.c_str();
       const string t = f.str();
        //const char * p;        p  = infile.c_str();
        //"/home/agile/SASOA/SA/data/L3/prova_l3_05_L3.evt"
        if (verbose) cout << "1) SAL3Eventlist::getInputDimension() going to open file " << t << endl;
        //std::auto_ptr<FITS> pInfile(new FITS("/home/agile/SASOA/SA/data/L3/prova_l3_05_L3.evt"
//,Read,EVENTS));
        
        std::auto_ptr<FITS> pInfile(new FITS(t.c_str(),Read,EVENTS));

        //FITS *  pInfile = (FITS *) new  FITS(infile.c_str(),Read,EVENTS);
        if (verbose) cout << "2) SAL3Eventlist::getInputDimension() opened file" <<  endl;
        
 try{

         // read a particular HDU within the file. This call reads just the header
         // information from EVENTS


         // define a reference for clarity. (std::auto_ptr<T>::get returns a pointer

        ExtHDU& table = pInfile->extension(EVENTS);
        if (verbose) cout << "3) SAL3Eventlist::getInputDimension() # of events " << table.rows() << endl;
         // read all the keywords, excluding those associated with columns.

         //table.readAllKeys();

         dim =  table.rows(); // set dimension for the l3eventlist object

          dimension = dim; // set dimension for the l3 structure

        if (verbose) cout << "4) SAL3Eventlist::getInputDimension() number of rows in the table  = " << table.rows() << endl;

         // print the result.
         //std::cout << table << std::endl;

	}
     catch (FitsException&)
     // will catch all exceptions thrown by CCfits, including errors
     // found by cfitsio (status != 0)
     {
        std::cerr << " Fits Exception Thrown by SAL3Eventlist::getInputDimension() \n";
        std::cerr << " perhaps input filename is not set: \n";
        //exit(0);
      }
     setVerbose(false);
     return dim;
}
/** No descriptions */
SAL3Event  SAdata::SAL3Eventlist::getEvent(unsigned long int evnum){
   ev2.setAmplitude( AMPLITUDE[evnum]);
   ev2.setCount( COUNT[evnum]);
   ev2.setTime( TIME[evnum]);   
   ev2.setDetector( DETECTOR[evnum]);
   ev2.setPhotonId( PHOTON_ID[evnum]);
   ev2.setPos( POS[evnum]);
   ev2.setPosShift( POS_SHIFT[evnum]);
   ev2.setSsid( SSID[evnum]);
   return ev2;
}


/** No descriptions */
void SAdata::SAL3Eventlist::save(const string &outfilename){
  
    std::auto_ptr<FITS> pFits(0);

    try
    {

        //const std::string fileName("atestfil.fit");
        pFits.reset( new FITS(outfilename,Write) );
    }
    catch (CCfits::FITS::CantOpen)
    {
          cerr << "SAL3Eventlist::save() exception in opening the outfile" << endl;
    }
//
//
    unsigned long rows = dimension;

   if (verbose) cout << "SAL3Eventlist::save() Number of rows of the output file = "<< rows << endl;    
    string hduName("EVENTS");
    std::vector<string> colName(8,"");
    std::vector<string> colForm(8,"");
    std::vector<string> colUnit(8,"");
    
    colName[0] = "COUNT";            colForm[0] = "J";     colUnit[0] = "n";
    colName[1] = "PHOTON_ID";    colForm[1] = "J";     colUnit[1] = "n";
    colName[2] = "TIME";               colForm[2] = "D";     colUnit[2] = "s";
    colName[3] = "AMPLITUDE";     colForm[3] = "E";     colUnit[3] = "pha";
    colName[4] = "POS";                 colForm[4] = "I";     colUnit[4] = "..";
    colName[5] = "DETECTOR";      colForm[5] = "B";     colUnit[5] = "n";
    colName[6] = "POS_SHIFT";      colForm[6] = "E";     colUnit[6] = "..";
    colName[7] = "SSID";                colForm[7] = "B";     colUnit[7] = "n";


  int val = 0;
  
 std::vector<long> count; // 
 std::vector<long> photon_id; // 
 std::vector<double> time;  // 
 std::vector<float> amplitude; // 
 std::vector<int> pos; // 
 std::vector<unsigned char> detector;
 std::vector<float> pos_shift;
 std::vector<unsigned char> ssid;

 unsigned long int rc;

/*  
  for(rc=0; rc<dimension; rc++){
        if (rc<10)getEvent(rc).show();    
        count[rc] = getEvent(rc).getCount();
        photon_id[rc] = getEvent(rc).getPhotonId();
        time[rc] = (double)getEvent(rc).getTime();
        amplitude[rc] = getEvent(rc).getAmplitude();
        if(getEvent(rc).getPos()>0){
          pos[rc] = (int)getEvent(rc).getPos();
        } else pos[rc]=(int)1540;        
        detector[rc] = (unsigned char)getEvent(rc).getDetector();
        pos_shift[rc] = getEvent(rc).getPosShift();
        ssid[rc] = (unsigned char)getEvent(rc).getSsid();
  }
	COUNT.clear();	PHOTON_ID.clear(); TIME.clear();
	AMPLITUDE.clear();	POS.clear();	DETECTOR.clear();
	POS_SHIFT.clear();	SSID.clear();

*/
	//dimension = COUNT.size();
	cout << "SAL3Eventlist::save() dimension = " << dimension << endl;
  for(rc=0; rc<dimension; rc++){
        //if (rc<10)getEvent(rc).show();    
        count.push_back(COUNT[rc]);
        photon_id.push_back(PHOTON_ID[rc]);
        time.push_back((double)TIME[rc]);
        amplitude.push_back(AMPLITUDE[rc]);
        if(POS[rc]>0){
          pos.push_back(POS[rc]);
        } else pos.push_back((int)1540);        
        detector.push_back((unsigned char)DETECTOR[rc]);
        pos_shift.push_back(POS_SHIFT[rc]);
        ssid.push_back((unsigned char)SSID[rc]);
  }

 Table* newTable;
 
try{
    newTable = pFits->addTable(hduName,dimension,colName,colForm,colUnit);
} catch (FitsException& f){
  cerr << "FITS exception : error in adding the eventlist table"<< endl;
} catch(const exception &e){
  cerr << "standard exception : error in adding the eventlist table"<< e.what() << endl;  
} catch (...){
  cerr << "exception : error in adding the eventlist table" << endl;  
}

      try{
        newTable->column(colName[0]).write(count,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing count"<< endl;
        for(int k=0; k<count.size(); k++)cerr << "count = "<< count[k] << endl;
      }
      try{
        newTable->column(colName[1]).write(photon_id,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing photon_id"<< endl;
        for(int k=0; k<photon_id.size(); k++) cerr << "photon_id = "<< photon_id[k] << endl;
      }
      try{
        newTable->column(colName[2]).write(time,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing time"<< endl;
        for(int k=0; k<time.size(); k++) cerr << " time = "<< time[k] << endl;
      }
      try{
        newTable->column(colName[3]).write(amplitude,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing amplitude"<< endl;
        for(int k=0; k<amplitude.size(); k++) cerr << " amplitude = "<< amplitude[k] << endl;
      }
      try{
        newTable->column(colName[4]).write(pos,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing pos"<< endl;
        for(int k=0; k<pos.size(); k++) cerr << " pos = "<< pos[k] << endl;
      }
      try{
      newTable->column(colName[5]).write(detector,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing detector"<< endl;
        for(int k=0; k<detector.size(); k++) cerr << " detector = "<< detector[k] << endl;
      }
      try{
        newTable->column(colName[6]).write(pos_shift,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing pos_shift"<< endl;
        for(int k=0; k<pos_shift.size(); k++) cerr << " pos_shift = "<< pos_shift[k] << endl;
      }
      try{
        newTable->column(colName[7]).write(ssid,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing ssid"<< endl;
        for(int k=0; k<ssid.size(); k++) cerr << " ssid = "<< ssid[k] << endl;
      }
      

//
//    //add a history string. This function call is in HDU:: so is identical
//    //for all HDUs
//
    string hist("This file was created for testing CCfits write functionality");
    hist += " it serves no other useful purpose. This particular part of the file was ";
    hist += " constructed to test the writeHistory() and writeComment() functionality" ;
//
//
    newTable->writeHistory(hist);
//
//    // add a comment string. Use std::string method to change the text in the message
//    // and write the previous junk as a comment.
//
    hist.insert(0, " COMMENT TEST ");
//
    newTable->writeComment(hist);
//
//    // ... print the result.
//
    //std::cout << *newTable << std::endl;
//
//    return 0;
}


/** No descriptions */
SAHistogram* SAdata::SAL3Eventlist::getImage(int detid){
verbose = true;
 if (verbose) cout << "SAL3Eventlist::getImage() started" << endl;
  SampleHistogram sh(0, 1537, 1);
  //sh = new SampleHistogram(0, 1535, 1);

 k = 0;
if (verbose) cout << "SAL3Eventlist::getImage() original eventlist dim = "<< dim << endl;
if (verbose) cout << "SAL3Eventlist::getImage() filtered eventlist dimension = "<<  dimension << endl;
 
 while(k< dimension ){
   if ( DETECTOR[k] == detid) sh +=  POS[k];
   //cout << "k = "<< k << "  POS[k] = " <<  POS[k] << endl;
   k++;
 }
 
 string s;stringstream ss;ss.str("");
 
 switch(sp.getImageType()){
   case 0:
   s = "detimg";
   break;
   case 1:
   s = "MDimg";
   break;
   default:
    cerr << "image type not defined !"<< endl;
    string a("image type not defined !");
    se.setMsg(a);
    throw se;
   break;
 }

 
 int *xx = new int[1536];
 unsigned long int *yy = new unsigned long int[1536];

  k=1;
  while(k< 1537){
      xx[k-1] = k-1;    yy[k-1] = sh.inBucket(k);
      k++;
  }

  SAPlot splot;
  splot.setDimension(1536);
  tempstring = "ASCII"; sp.setPlotType(tempstring);
  s = sp.getPlotSubsetDir(); s+="/";
  s+="detimage_";
  ss<<fcntr;
  s+= ss.str();  s+=".dat";
  for(int k=0; k<1536; k++) splot.setPoint(xx[k], yy[k]);
  // save the data passing the filename
  splot.saveGnuPlot(s);
  tempstring = "DetImg"; sp.setPlotType(tempstring); 	sp.setTerm(getPlotTerm());
  if (debug) sp.setInteractive(true);
  sp.setData(xx, yy, 1536);
  sp.setXRange(0, 1536);
 if (verbose) cout << "il massimo e' " << sh.max() << endl;
  sp.setYRange(0, (long int)sh.max());
  sp.start();
  ss.str("");
  ss << "Detector Image detector " << detid;
  tempstring = ss.str();
  sp.setPlotTitle(tempstring);
  sp.setInteractive(false);
  ss.str("");  ss << "detimg_";
  sp.setFilenameBase(ss.str());
  sp.plot();    sp.print(sp.getPlotSubsetDir()); sp.stop();
 if (verbose) cout << "SAL3Eventlist::getImage() ended" << endl;
  delete [] xx;   delete [] yy;
  fcntr++;
verbose = false;
  return (SAHistogram *)&sh;
}
/** No descriptions */
void SAdata::SAL3Eventlist::getAllDetImages(){
  if (verbose) cout << "SAL3Eventlist::getAllDetImages() started" << endl;
  sh0 = getImage(0);
  if (verbose) cout << "SAL3Eventlist::getAllDetImages() detimage for det 0 created" << endl;
  sh1 = getImage(1);
  if (verbose) cout << "SAL3Eventlist::getAllDetImages() detimage for det 1 created" << endl;
  sh2 = getImage(2);
  if (verbose) cout << "SAL3Eventlist::getAllDetImages() detimage for det 2 created" << endl;
  sh3 = getImage(3);
  if (verbose) cout << "SAL3Eventlist::getAllDetImages() detimage for det 3 created" << endl;
  if (verbose) cout << "SAL3Eventlist::getAllDetImages() ended " << endl;
}

void SAdata::SAL3Eventlist::getAllLightCurves(){
  if (verbose) cout << "SAL3Eventlist::AllLightCurves() started" << endl;
  sh0 = getLightCurve(0);
  if (verbose) cout << "SAL3Eventlist::AllLightCurves() lightcurve for det 0 created" << endl;
  sh1 = getLightCurve(1);
  if (verbose) cout << "SAL3Eventlist::AllLightCurves() lightcurve for det 1 created" << endl;
  sh2 = getLightCurve(2);
  if (verbose) cout << "SAL3Eventlist::AllLightCurves() lightcurve for det 2 created" << endl;
  sh3 = getLightCurve(3);
  if (verbose) cout << "SAL3Eventlist::AllLightCurves() lightcurve for det 3 created" << endl;
  if (verbose) cout << "SAL3Eventlist::AllLightCurves() ended " << endl;
}
void SAdata::SAL3Eventlist::getAllSpectra(){
  if (verbose) cout << "SAL3Eventlist::getAllSpectra() started" << endl;
  sh0 = getSpectrum(0);
  if (verbose) cout << "SAL3Eventlist::getAllSpectra() spectrum for det 0 created" << endl;
  sh1 = getSpectrum(1);
  if (verbose) cout << "SAL3Eventlist::getAllSpectra() spectrum for det 1 created" << endl;
  sh2 = getSpectrum(2);
  if (verbose) cout << "SAL3Eventlist::getAllSpectra() spectrum for det 2 created" << endl;
  sh3 = getSpectrum(3);
  if (verbose) cout << "SAL3Eventlist::getAllSpectra() spectrum for det 3 created" << endl;
  if (verbose) cout << "SAL3Eventlist::getAllSpectra() ended " << endl;
}
/** fill the MDImage object */
void SAdata::SAL3Eventlist::fillMDImage(){
   /** */
//   float C_Angles[NREGVAL];
   /** */
//   float C_Coeffs[NREGVAL];
   /** */
   short int C_Shifts[NREGVAL];
   /** */
   short int C_Coords[NREGVAL];   
    float EnMin;

    float EnMax;

    short int N_regions;

    float maxangle;

    float f_length;

    float s_width;

    float delta_norm;

    int dimss;

    float  Tburst;

//    verbose = true;
      verbose = false;
     /** */
    char *starts = new char[55];
   /** */
    char *cfin_out = new char[64];
   /** */
    char *cfin_p = new char[64];

 if (verbose) cout << "executing SAL3Eventlist::saveIrosMap()"<< endl;
        system("rm test.dat");
 if (verbose) cout << "going to write following data" << endl;

          string ss("SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR");
          string fin_out("pippo1"); // name of the file
          string fin_p("plutone2");
//          startstring = (char *)"SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR";
           starts = (char *)ss.c_str();
           i_fn_length_0 = strlen(starts);
           if (verbose) cout << "startstring e' lunga "<< i_fn_length_0 << endl;
           //cfin_out =  fin_out.c_str();
           //cfin_p =  fin_p.c_str();
           cfin_out = "pippo1";
           cfin_p = "plutone2";
           i_fn_length_1 = strlen(cfin_out);
           i_fn_length_2  = strlen(cfin_p);
           if (verbose) cout << "going to write the string "<< cfin_out << endl;
           if (verbose) cout << "that is  "<< i_fn_length_1 << " chars long" << endl;
           Tburst = (float)PI;

           D_Seq[0] = 2;
           D_Seq[1] = 3;
           D_Seq[2] = 0;
           D_Seq[3] = 1;

            N_regions =  NREGVAL;
            Hist_Size = HISTSIZVAL;
            Nchan = NCHANVAL;

            float *C_Angles = new float[N_regions];
            float *C_Coeffs = new float[N_regions];
            float *Point_Hist_x = new float[Hist_Size];
            float *Point_Hist_z = new float[Hist_Size];

            for(w=0; w<N_regions; w++) C_Index[w] = (short int)w;


            /// Setting default values

    /** */
     max_angle = 60.;

     /** */
    f_length = 14.14;

     /** */
    s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;

     /** */
     EnMax = 100.;

     if (verbose) cout << "writing pointing histogram " <<  endl;

     /** */
     for(w=0; w<N_regions; w++){
	   C_Angles[w] = max_angle/N_regions*(2.*w-1.)/2.;
	   C_Coeffs[w] = delta_norm*(tan(C_Angles[w]*PI/180.)-tan((C_Angles[w]-1.)*PI/180.));
	   C_Coeffs[w] = C_Coeffs[w]*1.00/0.93;
     }

///  pointing histogram creation
float Psi_s_z;
float Psi_s_x;


/// loop on all the events of the eventlist
    if (verbose) cout << "loop on all the events of the eventlist" << endl;

unsigned long int c;

c = 0;

/// ###### REMEMBER TO CHANGE
// dimension = 10;
/// ###### REMEMBER TO CHANGE

while (c< dimension){

    ev = getEvent(c); /// get the temp event

 // verbose = true;

   if (verbose) {
     if (verbose) cout << "events  n " << c << endl;
     ev.show();
   }
    iside 	= 0;

    if (ev.getPos() > 767) {
	     iside = 1;
          //	   ev.getPos() = ev.getPos() - 768;
          ev.setPos(ev.getPos() - 768);
	  }

        switch(ev.getDetector()){
          case 0:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		    C_Shifts[i] = -1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
		  }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
          break;
          case 1:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]	= Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 2:
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])] = Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 3:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = -1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		  Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])] = Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          default:    /// INSERT AN EXCEPTION
           if (verbose) cout << "wrong detector number !!!" << endl;
          break;
        }

        for(w=0; w<N_regions; w++){
            C_Coords[C_Index[i]] = C_Shifts[C_Index[i]] + ev.getPos();
        }

        for(w=0; w<N_regions; w++){ // loop on the sky region
        cond1 = (C_Coords[C_Index[i]] > 0);
        cond2 = (C_Coords[C_Index[i]] < 767);
//        cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
        if (cond1 && cond2) {
//	          if (cond3) {
		          MDImage[C_Index[i]] [ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768] =  MDImage[C_Index[i]][ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768]+1;
//	          }
	        }
         }
  c++;
}


// coordinates calculation !

///  Multi Detector Image structure creation !!

         if (verbose) cout << "N_regions = "<< N_regions << endl;
         if (verbose) cout << "N of det = "<< 4 << endl;
         if (verbose) cout << "Nchan = "<< Nchan << endl;


         if (verbose) cout << "size of  Nchan "<< sizeof(short int) << endl;
         if (verbose) cout << "size of  Hist_Size "<< sizeof(short int) << endl;

          try {
                // open file and
//                fstream binary_file("test.dat",ios::out|ios::binary|ios::trunc);
//                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
//                binary_file.write(reinterpret_cast<char *>(starts), i_fn_length_0);
                if (verbose) cout << "written startstring = "<< starts << endl;
//                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                if (verbose) cout << "written i_fn_length_1 = "<< i_fn_length_1 << endl;
//                binary_file.write(reinterpret_cast<char *>(cfin_out), i_fn_length_1);
                if (verbose) cout << "written cfin_out = "<<  cfin_out << endl;
//                binary_file.write(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
                if (verbose) cout << "written i_fn_length_2 = "<< i_fn_length_2 << endl;
//                binary_file.write(reinterpret_cast<char *>(cfin_p), i_fn_length_2);
                if (verbose) cout << "written cfin_p = "<< cfin_p << endl;
//                binary_file.write(reinterpret_cast<char *>(&Nchan), sizeof(short int));
                if (verbose) cout << "written Nchan = "<< Nchan << endl;
//                binary_file.write(reinterpret_cast<char *>(&Tburst), sizeof(float));
                if (verbose) cout << "written Tburst = "<< Tburst << endl;
//                binary_file.write(reinterpret_cast<char *>(&EnMin),sizeof(float));
               if(verbose) cout<<"written EnMin: "<< EnMin << endl;
//                binary_file.write(reinterpret_cast<char *>(&EnMax),sizeof(float));
               if(verbose) cout<<"written EnMax: "<< EnMax << endl;
//                binary_file.write(reinterpret_cast<char *>(&N_regions),sizeof(short int));
               if(verbose) cout<<"written N_regions: "<< N_regions << endl;
//                binary_file.write(reinterpret_cast<char *>(&maxangle),sizeof(float));
                if(verbose) cout<<"written maxangle: "<< maxangle << endl;
//                binary_file.write(reinterpret_cast<char *>(&f_length),sizeof(float));
               if(verbose) cout<<"written f_length: "<< f_length << endl;
//                binary_file.write(reinterpret_cast<char *>(&s_width),sizeof(float));
                //            cout<<"write s_width: "<<  << endl;
//                binary_file.write(reinterpret_cast<char *>(&delta_norm),sizeof(float));
                if(verbose) cout<<"written delta_norm: "<< delta_norm << endl;

              for(w=0; w<N_regions; w++){
//                  binary_file.write(reinterpret_cast<char *>(&C_Angles[w]),sizeof(float));
                  if(verbose) cout<<"written C_Angles, element  "<< w << " value "<< C_Angles[w] << endl;
              }

              for(w=0; w<N_regions; w++){
//                  binary_file.write(reinterpret_cast<char *>(&C_Coeffs[w]),sizeof(float));
                  if(verbose) cout<<"written C_Coeffs, element  "<< w << " value "<< C_Coeffs[w] << endl;
              }

//              binary_file.write(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));

            for(w=0; w<Hist_Size; w++){
//                binary_file.write(reinterpret_cast<char *>(&Point_Hist_x[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;
             }

            for(w=0; w<Hist_Size; w++){
//                binary_file.write(reinterpret_cast<char *>(&Point_Hist_z[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_z, element  "<< w << " value " << Point_Hist_z[w] << endl;
            }

            for(w=0; w<4; w++){ // write detector index
//              binary_file.write(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
             if (verbose) cout << "written D_Seq[w] = " << D_Seq[w] << endl;
            }

           if (verbose) cout << "SAL3Eventlist::saveIrosMap() going to write the MultiDetectorImage"<< endl;
            /// REMEMBER TO CHANGE !
            /// AND USE DEFAULT VALUES!


            //verbose = true;
            if(verbose) cout << "For "<< N_regions << " regions " << endl;
            for (w=0; w<4; w++) cout << "For detector n. "<<  D_Seq[w] <<  " and then "<< endl;
            int count = 0;
            for(x=0; x<N_regions; x++){ // loop on the sky regions
            if(verbose) cout << "####  data for the sky region "<< C_Index[x]  << endl;

//            binary_file.write(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int)); /// write the region index
            if(verbose) cout << " written  index region "<< C_Index[x]   << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[0]  << " det   = "<< 0  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
//                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(long int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code"<< D_Seq[0] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[0]][w]<< endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"    completed MDImage,  detector code"<< D_Seq[0]  << " det  "<< 0  <<  endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[1]  << " det   = "<< 1  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
//                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(long int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector "<< D_Seq[1] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[1]  << " det =  "<< 1  << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code"<< D_Seq[2]  << " det  "<< 2  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
//                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(long int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[2] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[2] << " det  = "<< 2 << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[3]  << " det  = "<< 3  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
//                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(long int));
                    if(verbose) cout << "        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[3] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                 }

                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[3] << " det  = "<< 3 << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if (verbose) cout << endl;
                if(verbose)cout << "#### completed data for the sky region index: "<<  x << endl;
                if (verbose) cout << endl;
                if (verbose) cout << endl;

//               if(verbose)cout << "written mdimage array region n. "<< count++<< endl;
            }// end of the loop on the sky regions

                if(verbose) cout << "written all data" << endl;
 //               binary_file.close();
       }
          catch (exception e){
          // will catch  exceptions
          // found by
            std::cerr << " SAL3Eventlist::saveIrosMap function \n" ;
//            e.handle();

          }

//
 if (verbose) cout << "SAL3Eventlist::saveIrosMap() ended!"<< endl;

}
/** prints out the IrosMap data content to an output stream (video, disk file or socket) */
void SAdata::SAL3Eventlist::printIrosMap(ostream &os){
  tm.start();
  char *starts2 = new char[55]; // initial string
  char *cfin_out2 = new char[64];  // contains fin_out variable
  char *cfin_p2 = new char[64];  // contains fin_p variable
  short int Nchan2;
  float Tburst2;
  float EnMin2;
  float EnMax2;
  short int N_regions2;
//  os << "N_regions2 = " << N_regions2 << endl;
  float maxangle2;
  float f_length2;
  float s_width2;
  float delta_norm2;

  float *C_Angles2 = new float[N_regions2];
  float *C_Coeffs2 = new float[N_regions2];
  float *Point_Hist_x2 = new float[Hist_Size];
  float *Point_Hist_z2 = new float[Hist_Size];
//  os << "Hist_Size = " << Hist_Size << endl;
            string s;
            stringstream ss;
try
{
    //ifstream binary_file ("/home/lazza/flist_test_ST_Check_f19_agile.map", ios::in|ios::binary|ios::in);
    //fstream binary_file("test.dat",ios::binary|ios::in);
    os << "going to open " << infile << endl;
    ifstream binary_file(infile.c_str(), ios::in | ios::binary);
    os << "####################" << endl;
    os << "       READ DATA    " << endl;
    os << "####################" << endl;

  if (binary_file.is_open())
  {
            //binary_file.read(reinterpret_cast<char *>(starts2),55);
            binary_file.read(starts2,55);
            if (!binary_file) {
              /// if error occurred
              cerr << "error in reding the file :" << endl;
              cerr << "read " << binary_file.gcount()  << "bytes "<< endl;
              binary_file.clear();
            }
            verbose = true;
            if(verbose) os<<"read startstring: "<< starts2 << endl;
           binary_file.read(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
            if(verbose) os<<"read i_fn_length_1: "<< i_fn_length_1 << endl;
            binary_file.read(reinterpret_cast<char *>(cfin_out2),i_fn_length_1);
            if(verbose) os<<"read fin_out: "<< cfin_out2 << endl;
            binary_file.read(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
            if(verbose) os<<"read i_fn_length_2: "<< i_fn_length_2 << endl;
            binary_file.read(reinterpret_cast<char *>(cfin_p2),i_fn_length_2);
            if(verbose) os<<"read fin_p: "<< cfin_p2 << endl;
           binary_file.read(reinterpret_cast<char *>(&Nchan2),sizeof(short int));
            os<<"read Nchan: "<< Nchan2 << endl;
            binary_file.read(reinterpret_cast<char *>(&Tburst2),sizeof(float));
            if(verbose) os<<"read Tburst: "<< Tburst2 << endl;
            binary_file.read(reinterpret_cast<char *>(&EnMin2),sizeof(float));
            if(verbose) os<<"read EnMin: "<< EnMin2 << endl;
            binary_file.read(reinterpret_cast<char *>(&EnMax2),sizeof(float));
            if(verbose) os<<"read EnMax: "<< EnMax2 << endl;
            binary_file.read(reinterpret_cast<char *>(&N_regions2),sizeof(short int));
            os<<"read N_regions: "<< N_regions2 << endl;
            binary_file.read(reinterpret_cast<char *>(&maxangle2),sizeof(float));
            if(verbose) os<<"read maxangle: "<< maxangle2 << endl;
            binary_file.read(reinterpret_cast<char *>(&f_length2),sizeof(float));
            if(verbose) os<<"read f_length: "<< f_length2 << endl;
            binary_file.read(reinterpret_cast<char *>(&s_width2),sizeof(float));
//            os<<"read s_width: "<<  << endl;
            binary_file.read(reinterpret_cast<char *>(&delta_norm2),sizeof(float));
            if(verbose) os<<"read delta_norm: "<< delta_norm2 << endl;
            for(w=0; w<N_regions2; w++){
              binary_file.read(reinterpret_cast<char *>(&C_Angles2[w]),sizeof(float));
              if(verbose) os<<"read C_Angles, element  "<< w << " value = " << C_Angles2[w] << endl;
            }
            for(w=0; w<N_regions2; w++){
             binary_file.read(reinterpret_cast<char *>(&C_Coeffs2[w]),sizeof(float));
              if(verbose) os<<"read C_Coeffs, element  "<< w << " value = "<< C_Coeffs2[w] << endl;
 }
            binary_file.read(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));

            for(w=0; w<Hist_Size; w++){
              binary_file.read(reinterpret_cast<char *>(&gPoint_Hist_x[w]),sizeof(float));
              if(verbose) os<<"read C_Angles, element  "<< w << " value = "<< gPoint_Hist_x[w] << endl;
            }

            for(w=0; w<Hist_Size; w++){
              binary_file.read(reinterpret_cast<char *>(&gPoint_Hist_z[w]),sizeof(float));
              if(verbose) os<<"read C_Coeffs, element  "<< w << " value = "<< gPoint_Hist_z[w] << endl;
            }

            verbose = true;
            for(w=0; w<4; w++){ // read detector index
              binary_file.read(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
               os << "D_Seq[w] = "   << D_Seq[w] << endl;
            }

            os << "going to read data for regions  # "   << N_regions2 << endl;
            os << "going to read data and channels  # "   << Nchan2 << endl;
            verbose = true;

            for(x=0; x<N_regions2; x++){ // loop on the sky regions
                binary_file.read(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int));
                os << "data for the sky region " << C_Index[x] << endl;

                 /// detector 0
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(long int ));
                    if(verbose) os<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[0] << " value = " << MDImage[C_Index[x]][D_Seq[0]][w] << endl;
                }// end of the loop on the strips

                 /// detector 1
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(long int ));
                    if(verbose) os<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[1] << " value = " << MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                }// end of the loop on the strips


                 /// detector 2
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(long int ));
                    if(verbose) os<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << " D_Seq = "  << D_Seq[2] << " value = " << MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                }// end of the loop on the strips


                 /// detector 3
                for(w=0; w<Nchan2; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(long int ));
                    if(verbose) os<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[3] << " value = " << MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                }// end of the loop on the strips

             }// end of the loop on the sky regions

            binary_file.close();
}
  else os << "Unable to open file" << endl;;

  }        catch (exception e){
    cerr << "exception during binary file reading"<< endl;
}
    os << "####################" << endl;
    os << "       END   DATA    " << endl;
    os << "####################" << endl;

    os  << endl;

  tm.stop();
  tm.report();
}
/** No descriptions */
void SAdata::SAL3Eventlist::setIrosMapData(){

   /** */
//   float C_Angles[NREGVAL];
   /** */
//   float C_Coeffs[NREGVAL];
   /** */
  short int C_Shifts[NREGVAL];
   /** */
   short int C_Coords[NREGVAL];   
 
   float EnMin;

    float EnMax;

    short int N_regions;

    float maxangle;

    float f_length;

    float s_width;

    float delta_norm;

    int dimss;

    float  Tburst;

//    verbose = true;
      verbose = false;
     /** */
    char *starts = new char[55];
   /** */
    char *cfin_out = new char[64];
   /** */
    char *cfin_p = new char[64];

 if (verbose) cout << "executing SAL3Eventlist::saveIrosMap()"<< endl;
        system("rm ../stg_2/test.dat");
 if (verbose) cout << "going to write following data" << endl;

          string ss("SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR");
          string fin_out("pippo1"); // name of the file
          string fin_p("plutone2");

//          startstring = (char *)"SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR";
           starts = (char *)ss.c_str();           _starts = (char *)ss.c_str();

           i_fn_length_0 = strlen(starts);
           _i_fn_length_0 = i_fn_length_0;

           if (verbose) cout << "startstring �lunga "<< i_fn_length_0 << endl;
           //cfin_out =  fin_out.c_str();
           //cfin_p =  fin_p.c_str();
           cfin_out = "pippo1";           _cfin_out = cfin_out;
           cfin_p = "plutone2";                     _cfin_p = cfin_p;

           i_fn_length_1 = strlen(cfin_out);  _i_fn_length_1 = strlen(cfin_out);

           i_fn_length_2  = strlen(cfin_p);    _i_fn_length_2  = strlen(cfin_p);

           if (verbose) cout << "going to write the string "<< cfin_out << endl;
           if (verbose) cout << "that is  "<< i_fn_length_1 << " chars long" << endl;


           D_Seq[0] = 2;           D_Seq[1] = 3;           D_Seq[2] = 0;           D_Seq[3] = 1;

           N_regions =  NREGVAL;            Hist_Size = HISTSIZVAL;            Nchan = NCHANVAL;

           _N_regions =  NREGVAL;         _Hist_Size = HISTSIZVAL;           _Nchan = NCHANVAL;

           _D_Seq[0] = 2;           _D_Seq[1] = 3;           _D_Seq[2] = 0;           _D_Seq[3] = 1;

            float *C_Angles = new float[N_regions];
            float *C_Coeffs = new float[N_regions];
            float *Point_Hist_x = new float[Hist_Size];
            float *Point_Hist_z = new float[Hist_Size];

            for(w=0; w<N_regions; w++) C_Index[w] = (short int)w;
                /** IrosMap object */
            for(w=0; w<N_regions; w++) _C_Index[w] = (short int)w;

            /// Setting default values
            for(w=0; w<Hist_Size; w++) {
                 Point_Hist_x[w] = 0.;
                 Point_Hist_z[w] = 0.;
            }


    /** */
     max_angle = 60.; _max_angle = 60.;

     /** */
    f_length = 14.14;    _f_length = 14.14;

     /** */
    s_width = 0.0121;    _s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;     _delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;     _EnMin = 15.;

     /** */
     EnMax = 100.;   _EnMax = 100.;

     /** */
     Tburst = 598.975; _Tburst = 598.975;

     if (verbose) cout << "setIrosMapData() writing pointing histogram " <<  endl;

     PI = M_PI;    if (verbose) cout << "PI = "<< PI << endl;

     /** */
     for(w=1; w<N_regions+1; w++){
	   C_Angles[w-1] = max_angle/N_regions*(2.*w-1.0)/2.;
	   C_Coeffs[w-1] = delta_norm*(tan(C_Angles[w-1]*PI/180.)-tan((C_Angles[w-1]-1.)*PI/180.));
	   C_Coeffs[w-1] = C_Coeffs[w-1]*1.00/0.93;
     }

     /** _C_Angles and _C_Coeffs for IrosMapObject */
    for(w=1; w<N_regions+1; w++){
	   _C_Angles[w-1] = _max_angle/_N_regions*(2.*w-1.0)/2.;
	   _C_Coeffs[w-1] = _delta_norm*(tan(_C_Angles[w-1]*PI/180.)-tan((_C_Angles[w-1]-1.)*PI/180.));
	   _C_Coeffs[w-1] = _C_Coeffs[w-1]*1.00/0.93;
     }

///  pointing histogram creation
float Psi_s_z;      float Psi_s_x;


/// loop on all the events of the eventlist
    if (verbose) cout << "setIrosMapData() loop on all the events of the eventlist" << endl;

unsigned long int c = 0;
int a=0;
/// ###### REMEMBER TO CHANGE
// dimension = 10;
/// ###### REMEMBER TO CHANGE
   if (verbose) cout << "setIrosMapData() number of events to fill in the histogram = "<<  dimension << endl;

while (c< dimension){
    ev = getEvent(c); /// get the temp event
   // verbose = true;

   if (verbose) {
     if (verbose) cout << "events  n " << c << endl;
     ev.show();
   }
    iside 	= 0;

    if (ev.getPos() > 767) {
	     iside = 1;
          //	   ev.getPos() = ev.getPos() - 768;
          ev.setPos(ev.getPos() - 768);
	  }

        switch(ev.getDetector()){
          case 0:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<_N_regions){
		    C_Shifts[i] = -1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
		    _C_Shifts[i] = -1.*(Psi_s_z)/ PI*180.*_C_Coeffs[i];

            i++;
		  }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
		  _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])]	= _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          case 1:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<_N_regions){
		   C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
		   _C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*_C_Coeffs[i];
            i++;
          }
		Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]	= Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]+1.;
		_Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])]	= _Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          case 2:
          i=0;
		  while(i<_N_regions){
		   C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
		   _C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*_C_Coeffs[i];
            i++;
          }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])] = Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
		  _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])] = _Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          case 3:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<_N_regions){
		   _C_Shifts[i] = -1.*(Psi_s_x)/ PI*180.*_C_Coeffs[i];
            i++;
          }
		  Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])] = Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]+1.;
		  _Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])] = _Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*_C_Coeffs[0])]+1.;
          break;
          default:    /// INSERT AN EXCEPTION
           if (verbose) cout << "wrong detector number !!!" << endl;
          break;
        }

        for(w=0; w<N_regions; w++){
            C_Coords[C_Index[w]] = C_Shifts[C_Index[w]] + ev.getPos();
        }

        for(w=0; w<_N_regions; w++){
            _C_Coords[_C_Index[w]] = _C_Shifts[_C_Index[w]] + ev.getPos();
        }

        for(w=0; w<N_regions; w++){ // loop on the sky region
            cond1 = (C_Coords[C_Index[w]] >= 0);
            cond2 = (C_Coords[C_Index[w]] <= 767);
            // cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
           if (cond1 && cond2) {
            //	          if (cond3) {
  		          MDImage[C_Index[w]] [ev.getDetector()][1+C_Coords[C_Index[w]]+iside*768] += 1;
            //	          }
	        }
         }

        for(w=0; w<_N_regions; w++){ // loop on the sky region
            cond1 = (_C_Coords[_C_Index[w]] >= 0);
            cond2 = (_C_Coords[_C_Index[w]] <= 767);
            // cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
           if (cond1 && cond2) {
            //	          if (cond3) {
  		          _MDImage[_C_Index[w]] [ev.getDetector()][1+_C_Coords[_C_Index[w]]+iside*768] += 1;
            //	          }
	        }
         }

  c++;
}

          try {
                // open file and
                fstream binary_file("../stg_2/test.dat",ios::out|ios::binary|ios::trunc);
//                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                binary_file.write(reinterpret_cast<char *>(starts), i_fn_length_0);
                if (verbose) cout << "written startstring = "<< starts << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                if (verbose) cout << "written i_fn_length_1 = "<< i_fn_length_1 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_out), i_fn_length_1);
                if (verbose) cout << "written cfin_out = "<<  cfin_out << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
                if (verbose) cout << "written i_fn_length_2 = "<< i_fn_length_2 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_p), i_fn_length_2);
                if (verbose) cout << "written cfin_p = "<< cfin_p << endl;
                binary_file.write(reinterpret_cast<char *>(&Nchan), sizeof(short int));
                if (verbose) cout << "written Nchan = "<< Nchan << endl;
                binary_file.write(reinterpret_cast<char *>(&Tburst), sizeof(float));
                if (verbose) cout << "written Tburst = "<< Tburst << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMin),sizeof(float));
               if(verbose) cout<<"written EnMin: "<< EnMin << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMax),sizeof(float));
               if(verbose) cout<<"written EnMax: "<< EnMax << endl;
                binary_file.write(reinterpret_cast<char *>(&N_regions),sizeof(short int));
               if(verbose) cout<<"written N_regions: "<< N_regions << endl;
                binary_file.write(reinterpret_cast<char *>(&max_angle),sizeof(float));
                if(verbose) cout<<"written max_angle: "<< max_angle << endl;
                binary_file.write(reinterpret_cast<char *>(&f_length),sizeof(float));
               if(verbose) cout<<"written f_length: "<< f_length << endl;
                binary_file.write(reinterpret_cast<char *>(&s_width),sizeof(float));
                if(verbose)   cout<<"write s_width: "<<  s_width << endl;
                binary_file.write(reinterpret_cast<char *>(&delta_norm),sizeof(float));
                if(verbose) cout<<"written delta_norm: "<< delta_norm << endl;

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Angles[w]),sizeof(float));
                  if(verbose) cout<<"written C_Angles, element  "<< w << " value "<< C_Angles[w] << endl;
              }

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Coeffs[w]),sizeof(float));
                  if(verbose) cout<<"written C_Coeffs, element  "<< w << " value "<< C_Coeffs[w] << endl;
              }


              binary_file.write(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));
              if(verbose) cout<<"written Hist_Size  "<< w << " value "<< Hist_Size << endl;


              for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_x[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;
             }

            for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_z[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_z, element  "<< w << " value " << Point_Hist_z[w] << endl;
            }

            for(w=0; w<4; w++){ // write detector index
              binary_file.write(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
              cout << "written D_Seq[w] = " << D_Seq[w] << endl;
            }

            cout << "SAL3Eventlist::saveIrosMap() going to write the MultiDetectorImage"<< endl;
            /// REMEMBER TO CHANGE !
            /// AND USE DEFAULT VALUES!


            if(verbose) cout << "For "<< N_regions << " regions " << endl;
            for (w=0; w<4; w++) cout << "For detector n. "<<  D_Seq[w] <<  " and then "<< endl;
            int count = 0;
            for(x=0; x<N_regions; x++){ // loop on the sky regions
            if(verbose) cout << "####  data for the sky region "<< C_Index[x]  << endl;

            binary_file.write(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int)); /// write the region index
            if(verbose) cout << " written  index region "<< C_Index[x]   << endl;

                 cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[0]  << " det   = "<< 0  <<  endl;
                 cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(long int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code"<< D_Seq[0] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[0]][w]<< endl;
                 }
                 cout << endl;
                if(verbose)cout<<"    completed MDImage,  detector code"<< D_Seq[0]  << " det  "<< 0  <<  endl;
                 cout << endl;

                 cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[1]  << " det   = "<< 1  <<  endl;
                 cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(long int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector "<< D_Seq[1] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                 }
                 cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[1]  << " det =  "<< 1  << endl;
                 cout << endl;

                 cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code"<< D_Seq[2]  << " det  "<< 2  <<  endl;
                 cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(long int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[2] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                 }
                 cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[2] << " det  = "<< 2 << endl;
                 cout << endl;

                 cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[3]  << " det  = "<< 3  <<  endl;
                 cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(long int));
                    if(verbose) cout << "        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[3] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                 }

                 cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[3] << " det  = "<< 3 << endl;
                 cout << endl;

                 cout << endl;
                 cout << endl;
                if(verbose)cout << "#### completed data for the sky region index: "<<  x << endl;
                 cout << endl;
                 cout << endl;

//               if(verbose)cout << "written mdimage array region n. "<< count++<< endl;
            }// end of the loop on the sky regions

                if(verbose) cout << "written all data" << endl;
                binary_file.close();
       }
          catch (exception e){
          // will catch  exceptions
          // found by
            std::cerr << " SAL3Eventlist::saveIrosMap function \n" ;
//            e.handle();

          }

//
  cout << "SAL3Eventlist::saveIrosMap() ended!"<< endl;

}
/** saves pointing histograms */
void SAdata::SAL3Eventlist::savePointHistos(){
  
}
/** No descriptions */

/** No descriptions */
SAHistogram* SAdata::SAL3Eventlist::getPointingHistogram(char axes){
  cout << "SAL3Eventlist::getImage() started" << endl;
  SampleHistogram sh(0, 1024, 1);
  return (SAHistogram *)&sh;
}
/** No descriptions */
void SAdata::SAL3Eventlist::plotPointingHistogram(char axes){
  SAPlot *splot = new SAPlot();
  splot->setDimension(1024);tempstring = "ASCII";phplot.setPlotType(tempstring);
  string s = phplot.getPlotSubsetDir(); s+="/";
  stringstream ss;
  s+="phist_";
  try{
  ss<<fcntr;
  } catch(...){
    cerr << "SAL3Eventlist::plotPointingHistogram() exception in creating filename"<< endl;
  }
  s+= ss.str();  s+=".dat";

    // prepare point.hist. plotter
  phplot.setXSize(1024);  phplot.setYSize(1024);
  phplot.setAxes(axes);
  if (debug) phplot.setInteractive(true);

  switch (axes) {
    case 'x':
    for(int k=0; k<1024; k++) {
      splot->setPoint(xx_xg[k], yy_xg[k]);      
    }
    phplot.setData(xx_xg, yy_xg, 1024);
      
    break;
    case 'z':
    for(int k=0; k<1024; k++) {
      splot->setPoint(xx_zg[k], yy_zg[k]);
    }
    phplot.setData(xx_zg, yy_zg, 1024);

    break;
    default:
    cerr << "illegal axes"<< endl;
    throw e;
  }
  // save the data passing the filename
  splot->saveGnuPlot(s);

  // pass point.hist data to the plotter
//  phplot.SAPlotter::setXRange(0, 1024);
  tempstring = "Pointing"; phplot.setPlotType(tempstring); 	phplot.setTerm(getPlotTerm());
  phplot.SAPlotter::setYRange(0, (long int)1024);
  // pass name to give to the plot
  ss.str("");  ss << "phist_";
  phplot.setFilenameBase(ss.str());
  // print on ps file and plot on the screen
  phplot.start();
  phplot.plot();  phplot.print(phplot.getPlotSubsetDir());
  phplot.stop();
  fcntr++;
  delete splot;
  cout << "SAL3Eventlist::getImage() ended" << endl;
 }
/** No descriptions */
void SAdata::SAL3Eventlist::plotMDImage(){
    verbose = false;
    sp.setXSize(1536);      sp.setYSize(1536);
    setImageType(1);
    if (debug) sp.setInteractive(true);
    else  sp.setInteractive(false);
    stringstream ss; ss.str("");  ss << "MDimg_";
    sp.setFilenameBase(ss.str());   
     int *xxi = new int[1536];
     unsigned long int *yyi = new unsigned long int[1536];
  for (int k=0; k<NREGVAL; k++){ // cicle on sky regions
    //        splot.setDimension(NREGVAL);
    for (int i=0; i<NDET; i++){ // cicle on detectors
//      splot = new SAPlot();
      SAPlot splot;
      splot.setDimension(1536);      
	  tempstring = "ASCII";sp.setPlotType(tempstring);
      string st = sp.getPlotSubsetDir(); st+="/";
      st+="MDimg_";      ss.str("");      ss<<fcntr;                               
      st+= ss.str();  st+=".dat";
      for (int j=0; j<NCHANVAL; j++){ // cicle on detectors
      // fill the X display plot & ASCII
        if (verbose)  printMDImageMessage(k, i, j);
                xxi[j] = j; yyi[j] = MDImage[k][i][j];
                splot.setPoint((float)xxi[j], (long)yyi[j] );
      } // end cicle on strips      
      // save the data passing the filename
      splot.saveGnuPlot(st);
//      delete splot;
      // pass data & plot
//      xp = (int *) &xxi; yp = (unsigned long int *) &yyi;
      string temps = "MDImg";sp.setPlotType(temps);
	  sp.setTerm(getPlotTerm());
      sp.setData(xxi, yyi, NCHANVAL);
      sp.start();
      ss.str("");      ss << "MDImage region " << k << " detector " << i ;    string  temps2 = ss.str();
      sp.setPlotTitle(temps2);
      sp.plot();      sp.print(sp.getPlotSubsetDir());    
      sp.stop();
      // load the plot
      fcntr++;      
    } // end cicle on detectors
  }  // end cicle on sky regions
  delete [] xxi;  delete [] yyi;    
  verbose = false;
}
/** No descriptions */
void SAdata::SAL3Eventlist::setDebug(bool bval){
   debug = bval;
}
/** No descriptions */
void SAdata::SAL3Eventlist::fixProdSetDir(){
/*  stringstream  ss;
  ss.str("");
  ss << "saprodset_" << sp.getPlotSetCtr() << "_"<< tm.getDateString();
  sp.setPlotSetDir(ss.str());
  phplot.setPlotSetDir(ss.str());
  isfixpsd = true;
*/
stringstream ss; ss.str("");ss<<sp.getPlotSetCtr();tempstring = ss.str();
setProdSetDir(tempstring);
}
void SAdata::SAL3Eventlist::setProdSetDir(const string &run_n){
  stringstream  ss;
  ss.str("");
  ss << "saprodset_" << run_n << "_"<< tm.getDateString();
  sp.setPlotSetDir(ss.str());
  phplot.setPlotSetDir(ss.str());
  isfixpsd = true;
}
/** No descriptions */
void SAdata::SAL3Eventlist::createProdSetDir(){
  if (isfixpsd) sp.createPlotSetDir();
  else {
      tempstring = "error : Products Set Directory name was not set !";
      se.setMsg(tempstring);
      throw se;
  }
}
/** No descriptions */
void SAdata::SAL3Eventlist::setInteractive(bool bval){
  sp.setInteractive(bval);
}
/** No descriptions */
void SAdata::SAL3Eventlist::printPointingHistogram(char axes){
  plotPointingHistogram(axes);
}
/** No descriptions */
void SAdata::SAL3Eventlist::createDefaults(){
}
/** No descriptions */
void SAdata::SAL3Eventlist::setImageType(int imt){
  sp.setImageType(imt);
}
/** No descriptions */
void SAdata::SAL3Eventlist::printMDImageMessage(int a, int b, int c){
    cout << "loading in SAPlot Multi Detector Image element"
    <<  "sky region" << a
    << "detector " << b
    << "strip  " << c
    << endl;
    cout << "Plotting Multi Detector Image" << endl;
}
/** No descriptions */
void SAdata::SAL3Eventlist::setFCounter(int fc){
  fcntr = fc;
  sp.setPlotCounter(fc);
  phplot.setPlotCounter(fc);
}
/** No descriptions */
void SAdata::SAL3Eventlist::plotTotMDImage(){
    verbose = false;
    SAPlot *splot;
    mdp.setXSize(NCHANVAL);      mdp.setYSize(NCHANVAL);
    mdp.setZSize(NCHANVAL);
    mdp.setXRange(0, 1536);
    mdp.setZRange(0, 10);
    //setImageType(1);
    if (debug) mdp.setInteractive(true);
    else  mdp.setInteractive(false);
    stringstream ss; ss.str("");  ss << "MDimg_";
    mdp.setFilenameBase(ss.str());
     int *xxi = new int[NCHANVAL];
     unsigned long int *yyi = new unsigned long int[NCHANVAL];
     unsigned long int *zzi = new unsigned long int[NCHANVAL];

  for (int k=0; k<NREGVAL; k++){ // cicle on sky regions
    //        splot.setDimension(NREGVAL);
    zzi[k] = k;
    for (int i=0; i<NDET; i++){ // cicle on detectors

    //      splot = new SAPlot();      splot->setDimension(1536);
    //      string st = mdp.getPlotSetDir(); st+="/";
    //      st+="TotMDimg_";      ss.str("");      ss<<fcntr;
    //      st+= ss.str();  st+=".dat";

      for (int j=0; j<NCHANVAL; j++){ // cicle on detectors
      // fill the X display plot & ASCII
        if (verbose)  printMDImageMessage(k, i, j);
                //xxi[j] = j; yyi[j] = MDImage[k][i][j];
                xxi[j] = j; yyi[j] = j*(j+k);
                //splot->setPoint((float)xxi[j], (long)yyi[j] );
      } // end cicle on strips
      // save the data passing the filename
      //splot->saveGnuPlot(st);
      //delete splot;
      ss.str("");
      ss << "MDImage region " << k << " detector " << i ;
      tempstring = ss.str();
      // pass data & plot
      // xp = (int *) &xxi; yp = (unsigned long int *) &yyi;
      mdp.setData(xxi, yyi, zzi, NCHANVAL);
      mdp.start();
      mdp.setPlotTitle(tempstring);
      mdp.plotAll();      mdp.print();
      mdp.stop();
      // load the plot
//      fcntr++;
    } // end cicle on detectors
    
  }  // end cicle on sky regions
        ss.str("");    ss << "TotMDImage" << i ;      tempstring = ss.str();
      // pass data & plot
      mdp.setData(xxi, yyi, zzi, NCHANVAL);
      mdp.start();
      mdp.setPlotTitle(tempstring);
      mdp.plotAll();      mdp.print();
      mdp.stop();
  delete [] xxi;  delete [] yyi;  delete [] zzi;
  verbose = false;
}
/** No descriptions */
void SAdata::SAL3Eventlist::saveIrosMap3(const string &fn){

	verbose = false;

    cout << "SAL3Eventlist::saveIrosMap3() start saving irosmap on file "<< fn << endl;

    cout << "SAL3Eventlist::saveIrosMap3() dimension =  "<< dimension << endl;

    float EnMin;    float EnMax;

    short int N_regions;

	N_regions = 10;
	Hist_Size = 1024;
    
	float maxangle;    float f_length;   float s_width;    float delta_norm;       float  Tburst;

    int dimss;

	float C_Angles[10];
    float C_Coeffs[1024];
            
    float  Point_Hist_x[1024];
    float  Point_Hist_z[1024];

    short int C_Shifts[10];
   /** */
    short int C_Coords[10];   


    for(int ff=0; ff<10; ff++){

     C_Angles[ff] = 0.;  /** float */

     C_Coeffs[ff]= 0.;  /** float */

     C_Shifts[ff]= 0;    /**  short int*/

     C_Coords[ff]= 0;  /**  short int*/

     C_Index[ff]= 0;  /** short int*/

    }


      for(int i=0; i<1024; i++) {
          xx_xg[i] = (int)i;
          yy_xg[i]=0;
        }

        for(int i=0; i<1024; i++) {
          xx_zg[i] = (int)i;
          yy_zg[i] = 0;
        }

    
//    verbose = true;
     /** */
    char *starts = new char[55];
   /** */
    char *cfin_out = new char[64];
   /** */
    char *cfin_p = new char[64];

 if (verbose) cout << "executing SAL3Eventlist::saveIrosMap3()"<< endl;
  //system("rm ../stg_2/test*.dat");
 if (verbose) cout << "SAL3Eventlist::saveIrosMap3() going to write following data" << endl;

          string ss("SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR");

          string fin_out("pippo1"); // name of the file          string fin_p("plutone2");

           starts = (char *)ss.c_str();

           i_fn_length_0 = strlen(starts);

           if (verbose) cout << "startstring has length "<< i_fn_length_0 << endl;

           cfin_out = (char *)"pippo1";
           cfin_p = (char *)"plutone2";

           i_fn_length_1 = strlen(cfin_out);

           i_fn_length_2  = strlen(cfin_p);

           if (verbose) cout << "going to write the string "<< cfin_out << endl;
           if (verbose) cout << "that is  "<< i_fn_length_1 << " chars long" << endl;


           D_Seq[0] = 2;
           D_Seq[1] = 3;
           D_Seq[2] = 0;
           D_Seq[3] = 1;

           

           N_regions =  NREGVAL;            Hist_Size = HISTSIZVAL;            Nchan = NCHANVAL;
           if (verbose)  cout << "SAL3Eventlist::saveIrosMap3() N_regions = "<< N_regions << endl;
           if (verbose)  cout << "SAL3Eventlist::saveIrosMap3() Hist_Size = "  <<  Hist_Size << endl;
           if (verbose)  cout << "SAL3Eventlist::saveIrosMap3() Nchan = "<< Nchan << endl;



           for(w=0; w<N_regions; w++) {
             C_Index[w] = (short int)w;
             if (verbose) cout << "SAL3Eventlist::saveIrosMap3() C_Index[" << w << "] = "<< C_Index[w] << endl;
           }
                /** IrosMap object */
           if (verbose) cout << "SAL3Eventlist::saveIrosMap3() C_Index[w] set : OK" << endl;

           if (verbose)  cout << "SAL3Eventlist::saveIrosMap3() resetted Point_Hist_x and Point_Hist_z[w]  variables "<< endl;
            /// Setting default values
            for(w=0; w<Hist_Size; w++) {
                 Point_Hist_x[w] = 0.;
                 Point_Hist_z[w] = 0.;                
            }

           

            for(int w=0; w<Nchan; w++){ // loop on the strips
              for(int k=0; k<4; k++){          // loop on the detectors
                 for(int x=0; x<N_regions; x++){        // loop on the regions
                    MDImage[C_Index[x]][k][w] = 0;
                    //if(verbose) cout<<" initializing MDImage, region "<< C_Index[x] << " detector code"<< k << " element " << w << " value "<< MDImage[C_Index[x]][k][w]<< endl;
                 }
              }
            }
           if (verbose)  cout << "SAL3Eventlist::saveIrosMap3()  MDImage initialized : OK"<< endl;

    /** */
     max_angle = 60.;

     /** */
    f_length = 14.14;

     /** */
    s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;

     /** */
     EnMax = 100.;

     /** */
    retrieveExposure();

     Tburst = float(getExposure());

     PI = M_PI;     cout << "PI = "<< PI << endl;

     if (verbose) cout << "SAL3Eventlist::saveIrosMap3() filled parameters  " <<  endl;

     /** */

     /** C_Angles and C_Coeffs*/

     for(w=1; w<N_regions+1; w++){
	   C_Angles[w-1] = max_angle/N_regions*(2.*w-1.0)/2.;
     if (verbose) cout << "C_Angles ["<< w-1 << "] = " << C_Angles[w-1] << endl;
	   C_Coeffs[w-1] = delta_norm*(tan(C_Angles[w-1]*PI/180.)-tan((C_Angles[w-1]-1.)*PI/180.));
	   C_Coeffs[w-1] = C_Coeffs[w-1]*1.00/0.93;
     if (verbose) cout << "C_Coeffs  ["<< w-1 << "] = "<< C_Coeffs[w-1] << endl;
     }

     if (verbose) cout << "SAL3Eventlist::saveIrosMap3()  C_Angles and C_Coeffs set: OK " <<  endl;

///  pointing histogram creation
float Psi_s_z;      float Psi_s_x;

/// loop on all the events of the eventlist
    if (verbose) cout << "loop on all the events of the eventlist" << endl;

unsigned long int c = 0;int a=0;
/// ###### REMEMBER TO CHANGE
// dimension = 10;
/// ###### REMEMBER TO CHANGE
   if (verbose) cout << "saveIrosMap() number of events to fill in the histogram = "<<  dimension << endl;

while (c< dimension){ // loop on all the events

   Psi_s_z = 0.; Psi_s_x = 0.;

    ev = getEvent(c); /// get the current event

   if ((verbose)&&(c<50)) {
     if (verbose) cout << "events  n " << c << endl;
     ev.show();
   }
    iside = 0;

    if (ev.getPos() > 767) {
	     iside = 1;
          ev.setPos(ev.getPos() - 768);
	  }

        switch(ev.getDetector()){
          case 0:
            Psi_s_z = ev.getPosShift();
            i=0;
              while(i<N_regions){
		      C_Shifts[i] = (short int)+1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
              i++;
		    }
           if (verbose) cout << "det 0: incrementing Point_Hist_z["<< (unsigned short int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])<< "]"<< endl;
		    Point_Hist_z[(unsigned short int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(unsigned short int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
          break;
          case 1:
            Psi_s_x = ev.getPosShift();
            i=0;
		    while(i<N_regions){
		    C_Shifts[i] = (short int)+1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
              i++;
            }
		    Point_Hist_x[(unsigned short int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]	= Point_Hist_x[(unsigned short int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]+1.;
           if (verbose)  cout << "det 1: incrementing Point_Hist_x["<< (unsigned short int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])<< "]"<< endl;
          break;
          case 2:
            Psi_s_z = ev.getPosShift();
            i=0;
		    while(i<N_regions){
		    C_Shifts[i] =(short int) -1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
              i++;
            }
		    Point_Hist_z[(unsigned short int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])] = Point_Hist_z[(unsigned short int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
           if (verbose)  cout << "det 2: incrementing Point_Hist_z["<< (unsigned short int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])<< "]"<< endl;
          break;
          case 3:
            Psi_s_x = ev.getPosShift();
            i=0;
		    while(i<N_regions){
		      C_Shifts[i] = (short int)-1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
              i++;
            }
		    Point_Hist_x[(unsigned short int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])] = Point_Hist_x[(unsigned short int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])]+1.;
           if (verbose)  cout << "det 3:  incrementing Point_Hist_x["<<(unsigned short int)(511+(Psi_s_x)/PI*180.*C_Coeffs[0])<< "]"<< endl;
          break;
          default:    /// INSERT AN EXCEPTION
           if (verbose) cout << "wrong detector number !!!" << endl;
          break;
        }

        for(w=0; w<N_regions; w++){
            C_Coords[C_Index[w]] = C_Shifts[C_Index[w]] + ev.getPos();
//            if((c<50)||((c>36000)&&(c<38000))){
//              cout << "C_Shifts[C_Index[w]] = " << C_Shifts[C_Index[w]]   << endl;
//              cout << "C_Index[w] = " << C_Index[w] << " ; C_Coords[C_Index[w]] = "<< C_Coords[C_Index[w]] << endl;
//              cout << "evnt_num = "<< c << "ev.getPos() "<< ev.getPos() << endl;              cout << "ev.getPosShift() "<< ev.getPosShift() << endl;
//            }
        }

        
        for(w=0; w<N_regions; w++){ // loop on the sky region
            cond1 = (C_Coords[C_Index[w]] >= 0);
            cond2 = (C_Coords[C_Index[w]] <= 767);
            // cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
           if (cond1 && cond2) {
            //	          if (cond3) {
  		          MDImage[C_Index[w]] [ev.getDetector()][1+C_Coords[C_Index[w]]+iside*768] += 1;
            //	          }
	        }
         }
  c++;
}

//*** fill pointing histograms to be printed/plotted

       if (verbose) cout << endl;
        
        for(int i=0; i<1024; i++) {
          if (Point_Hist_x[i]>=0){
            yy_xg[i] = (unsigned long int)Point_Hist_x[i];
          } else {
            yy_xg[i] = 0;
          }
          if (verbose) cout << i << " saveirosmap3 debug --> yy_xg = "<<  Point_Hist_x[i] << endl;
        }

        cout << endl;

        for(int i=0; i<1024; i++) {
          if (Point_Hist_z[i]>=0){
            yy_zg[i] = (unsigned long int)Point_Hist_z[i];
          } else {
            yy_zg[i] = 0;
          }
          if (verbose) cout << i << " saveirosmap3 debug --> yy_zg = "<<  Point_Hist_z[i] << endl;
        }

        

 if (verbose) cout << "out of the loop on events: counter  = " << c << endl;
// coordinates calculation !
///  Multi Detector Image structure filled !!

 
         if (verbose) cout << "N_regions = "<< N_regions << endl;
         if (verbose) cout << "N of det = "<< 4 << endl;
         if (verbose) cout << "Nchan = "<< Nchan << endl;


         if (verbose) cout << "size of  Nchan "<< sizeof(short int) << endl;
         if (verbose) cout << "size of  Hist_Size "<< sizeof(short int) << endl;

          try {
                // open file and
                fstream binary_file(fn.c_str(),ios::out|ios::binary|ios::trunc);
//                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                binary_file.write(reinterpret_cast<char *>(starts), i_fn_length_0);
                if (verbose) cout << "written startstring = "<< starts << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                if (verbose) cout << "written i_fn_length_1 = "<< i_fn_length_1 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_out), i_fn_length_1);
                if (verbose) cout << "written cfin_out = "<<  cfin_out << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
                if (verbose) cout << "written i_fn_length_2 = "<< i_fn_length_2 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_p), i_fn_length_2);
                if (verbose) cout << "written cfin_p = "<< cfin_p << endl;
                binary_file.write(reinterpret_cast<char *>(&Nchan), sizeof(short int));
                if (verbose) cout << "written Nchan = "<< Nchan << endl;
                binary_file.write(reinterpret_cast<char *>(&Tburst), sizeof(float));
                if (verbose) cout << "written Tburst = "<< Tburst << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMin),sizeof(float));
               if(verbose) cout<<"written EnMin: "<< EnMin << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMax),sizeof(float));
               if(verbose) cout<<"written EnMax: "<< EnMax << endl;
                binary_file.write(reinterpret_cast<char *>(&N_regions),sizeof(short int));
 
               if(verbose) cout<<"written N_regions: "<< N_regions << endl;
                binary_file.write(reinterpret_cast<char *>(&max_angle),sizeof(float));

                if(verbose) cout<<"written max_angle: "<< max_angle << endl;
                binary_file.write(reinterpret_cast<char *>(&f_length),sizeof(float));
               if(verbose) cout<<"written f_length: "<< f_length << endl;
                binary_file.write(reinterpret_cast<char *>(&s_width),sizeof(float));
                if(verbose)   cout<<"write s_width: "<<  s_width << endl;
                binary_file.write(reinterpret_cast<char *>(&delta_norm),sizeof(float));
                if(verbose) cout<<"written delta_norm: "<< delta_norm << endl;

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Angles[w]),sizeof(float));
                  if(verbose) cout<<"written C_Angles, element  "<< w << " value "<< C_Angles[w] << endl;
              }

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Coeffs[w]),sizeof(float));
                  if(verbose) cout<<"written C_Coeffs, element  "<< w << " value "<< C_Coeffs[w] << endl;
              }


              binary_file.write(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));
              if(verbose) cout<<"written Hist_Size  "<< w << " value "<< Hist_Size << endl;


              for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_x[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;
             }

            for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_z[w]),sizeof(float));
                if(verbose) cout<<"written Point_Hist_z, element  "<< w << " value " << Point_Hist_z[w] << endl;
            }

            for(w=0; w<4; w++){ // write detector index
              binary_file.write(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
             if (verbose) cout << "written D_Seq[w] = " << D_Seq[w] << endl;
            }

           if (verbose) cout << "SAL3Eventlist::saveIrosMap() going to write the MultiDetectorImage"<< endl;
            /// REMEMBER TO CHANGE !
            /// AND USE DEFAULT VALUES!

       
 
            if(verbose) cout << "For "<< N_regions << " regions " << endl;
            for (w=0; w<4; w++) cout << "For detector n. "<<  D_Seq[w] <<  " and then "<< endl;
            int count = 0;
            for(x=0; x<N_regions; x++){ // loop on the sky regions
    

            if(verbose) cout << "####  data for the sky region "<< C_Index[x]  << endl;

            binary_file.write(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int)); /// write the region index
            if(verbose) cout << " written  index region "<< C_Index[x]   << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[0]  << " det   = "<< 0  <<  endl;
                if (verbose) cout << endl;
                 
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code"<< D_Seq[0] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[0]][w]<< endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"    completed MDImage,  detector code"<< D_Seq[0]  << " det  "<< 0  <<  endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[1]  << " det   = "<< 1  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector "<< D_Seq[1] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                 }                                                                          
                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[1]  << " det =  "<< 1  << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code"<< D_Seq[2]  << " det  "<< 2  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(int));
                    if(verbose) cout<<"        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[2] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                 }
                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[2] << " det  = "<< 2 << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if(verbose)cout<<"    writing MDImage,  detector code = "<< D_Seq[3]  << " det  = "<< 3  <<  endl;
                if (verbose) cout << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof( int));
                    if(verbose) cout << "        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[3] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                 }

                if (verbose) cout << endl;
                if(verbose)cout<<"completed MDImage,  detector code = "<< D_Seq[3] << " det  = "<< 3 << endl;
                if (verbose) cout << endl;

                if (verbose) cout << endl;
                if (verbose) cout << endl;
                if(verbose)cout << "#### completed data for the sky region index: "<<  x << endl;
                if (verbose) cout << endl;
                if (verbose) cout << endl;

//               if(verbose)cout << "written mdimage array region n. "<< count++<< endl;
            }// end of the loop on the sky regions

                if(verbose) cout << "written all data" << endl;
                verbose = false;
                binary_file.close();
       }
          catch (exception e){
          // will catch  exceptions
          // found by
            std::cerr << " SAL3Eventlist::saveIrosMap3 function " << e.what() << endl;
//            e.handle();
			
          }

    cout << "SAL3Eventlist::saveIrosMap3() dimension =  "<< dimension << endl;
//
	cout << "SAL3Eventlist::saveIrosMap()3 ended!"<< endl;
/*
            delete C_Angles ;
            delete C_Coeffs ; 
            delete Point_Hist_x ;
            delete Point_Hist_z ;
    delete starts;
    delete cfin_out;
    delete cfin_p;*/

	verbose = false;

//#####################

}



/** No descriptions */
void SAdata::SAL3Eventlist::savePart(const string &ofnam, long int dime){
     dim = (unsigned long int)dime;
     save(ofnam);
}

/* */

void SAdata::SAL3Eventlist::readPart(const string &infilename, unsigned long startindex, unsigned long new_nrows){ 

        tm.start();
        
        cout << "executing AL3Eventlist::readPart()" << endl;
        fitsfile * in = (fitsfile*) new fitsfile[1];
        cout << "SAL3Eventlist::readPart() created  fitsfile (cfitsio)" << endl;
         //verbose = false;
try
{
     // read a table and explicitly read selected columns. To read instead all the
     // data on construction, set the last argument of the FITS constructor
     // call to 'true'. This functionality was tested in the last release

     std::vector<string> hdus(2) ;

     std::vector<long int> pp;

     std::vector<short int> ss;

     std::vector<long long int> ll;

     std::vector<unsigned char> bb;

     std::vector<float> ff;

     std::vector<double> d;

     int k;
     int ncols;
  	 long nrows = 0;
   	 int colnum = 0;
	 unsigned long long int * cftime;
     int status = 0;

     hdus[1] = "EVENTS" ;

     std::auto_ptr<FITS> pInfile(new FITS(infile,Read,hdus,false));


     ExtHDU& table = pInfile->extension(hdus[1]) ;

    // fitsfile * input = (fitsfile*)&pInfile;

    fits_open_file(&in, infile.c_str(), READONLY, &status);
    cout << "SAL3Eventlist::readPart() fitsfile is open (cfitsio)" << endl;

    fits_movabs_hdu(in, 2, NULL, &status);
    cout << "SAL3Eventlist::readPart() reached extension 2 (cfitsio)" << endl;

   	fits_get_num_rows(in, &nrows, &status);
    cout << "SAL3Eventlist::readPart() original  number of rows " << nrows << endl;
	fits_get_num_cols(in, &ncols, &status);
    cout << "SAL3Eventlist::readPart() original  number of cols = " << ncols << endl;
     dimension = nrows; // dimension of the external eventlist structure
    dim = nrows;  // dimension of the dim field of the eventlist



    
       dimension = startindex+new_nrows;
      dim =  dimension;
    cout << "SAL3Eventlist::readPart()  number of rows to be read = " <<  dimension << endl;

   try {

     table.column("COUNT").read(pp, startindex+1, dimension ) ;
     int  i=0;
     while(i< dimension){
     if (verbose)      cout <<  "COUNT = " << pp[i] << endl;
       COUNT[i] = pp[i];
      i++ ;
     }
        cout << "read COUNT column " << endl;

     pp.resize(0);

     table.column("PHOTON_ID").read(pp, startindex+1, dimension) ;
      i=0;
     while(i< dimension){
      if (verbose) cout <<  "PHOTON_ID = " << pp[i] << endl;
       PHOTON_ID[i] = pp[i];
      i++ ;
     }
        cout << "read PHOTON_ID column " << endl;

     pp.resize(0);
}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading photon_id) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in photon_id reading \n" ;

}
try
{

///// REMEMBER TO CORRECT !!!

   cftime = new unsigned long long[ dimension];

	fits_get_colnum(in, 1, "TIME", &colnum, &status);

     table.column("TIME").read(d, startindex+1, dimension ) ;
     unsigned long i=0;
//    fits_read_col(in, TDOUBLE, colnum, startindex+1, 1,  dimension, NULL, cftime, NULL, &status);
     while(i< dimension){
         //TIME[i] = cftime[i];
         TIME[i] = d[i];
//      if (verbose) cout <<  "TIME = " << cftime[i] << endl;
        //if((i<10)||(i>614195))cout <<  "TIME = " << cftime[i] << endl;
      if (verbose) cout <<  "TIME = " << d[i] << endl;
      i++ ;
     }
     cout << "read TIME column " << endl;
    d.resize(0);
    //delete []cftime;

}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading time) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in time reading \n" ;

}
catch (CCfits::Column::InvalidDataType) {
  cout << "exception thrown by CCfits \n"<< endl;
}


try
{
      table.column("AMPLITUDE").read(ff, 1, dimension ) ;
     i=0;
     while(i< dimension){
        AMPLITUDE[i] = ff[i];
      if (verbose) cout <<  "AMPLITUDE = " << ff[i] << endl;
      i++ ;
     }
     cout << "read AMPLITUDE column " << endl;
    ff.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading amplitude) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in amplitude reading \n" ;

}
    try{

     table.column("POS").read(ss, 1, dimension ) ;
     i=0;
     while(i< dimension){
        POS[i] = ss[i];
      if (verbose) cout <<  "POS = " << ss[i] << endl;
      i++ ;
     }
     cout << "read POS column " << endl;
    ss.resize(0);
}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading position) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in position reading \n" ;

}

try{
     table.column("DETECTOR").read(bb, 1,  dimension );
     i=0;
     while(i< dimension){
       DETECTOR[i] = bb[i];
      k = (int)bb[i];
      if (verbose) cout <<  "DETECTOR = " << k << endl;
      i++ ;
     }
    cout << "read DETECTOR column " << endl;
     bb.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading detector) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in detector reading \n" ;

}

try{
     table.column("POS_SHIFT").read(ff, 1, dimension );
     i=0;
     while(i< dimension){
      if (verbose) cout <<  "POS_SHIFT = " << ff[i] << endl;
       POS_SHIFT[i] = ff[i];
      i++ ;
     }
      cout << "read POS_SHIFT column " << endl;
     ff.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading POS_SHIFT) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in POS_SHIFT reading \n" ;

}

try{
     table.column("SSID").read(bb, 1,  dimension) ;
     i=0;
     while(i< dimension){
      k = (int)bb[i];
      if (verbose) cout <<  " = " << (int)bb[i] << endl;
       SSID[i] = bb[i];
      i++ ;
     }
      cout << "read SSID column " << endl;
      bb.resize(0);
  delete in;
}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << "Fits Exception Thrown by SAL3Eventlist::read() function (reading SSID) \n" ;
}
} catch (const exception &e){
       std::cerr << " error in SSID reading \n" ;

}

  tm.stop();
  tm.report();
  //
  
}

/**
       COUNT[i] = pp[i];
       PHOTON_ID[i] = pp[i];
       TIME[i] = ll[i];
       AMPLITUDE[i] = ff[i];
       POS[i] = ss[i];
       DETECTOR[i] = bb[i];
       POS_SHIFT[i] = ff[i];
       SSID[i] = ;

 
/
*//** No descriptions */
/** No descriptions */
void SAdata::SAL3Eventlist::readDebug(string &fn){
        tm.start();
        if (verbose) cout << "SAL3Eventlist::readDebug() executing " << endl;
        //fitsfile * in = (fitsfile*) new fitsfile[1];
        if (verbose) cout << "SAL3Eventlist::readDebug() created input fitsfile object (cfitsio)" << endl;
         //verbose = false;
try
{
     // read a table and explicitly read selected columns. To read instead all the
     // data on construction, set the last argument of the FITS constructor
     // call to 'true'. This functionality was tested in the last release

     std::vector<string> hdus(1) ;

    
     unsigned long long int * cftime;

     int k; int ncols;
     long nrows = 0;   	 int colnum = 0;

     int status = 0;
     tempstring = (string)"EVENTS" ;
     hdus[0] = tempstring;

     //std::auto_ptr<FITS> pInfile(new FITS(fn,Read,hdus,false));
    if (verbose) cout << "SAL3Eventlist::read() going to read fitsfile " << fn << endl;
    if (verbose) cout << "SAL3Eventlist::read() going to read extension " << hdus[0] << endl;


    /*if (fits_open_file(&in, fn.c_str(), READONLY, &status)) printerror(status);

    if (verbose) cout << "SAL3Eventlist::read() fitsfile is open (cfitsio)" << endl;

    if (fits_movabs_hdu(in, 2, NULL, &status)) printerror(status);
    if (verbose) cout << "SAL3Eventlist::read() reached extension 2 (cfitsio)" << endl;

   	if (fits_get_num_rows(in, &nrows, &status)) printerror(status);
    if (verbose) cout << "SAL3Eventlist::read() number of rows " << nrows << endl;
	if (fits_get_num_cols(in, &ncols, &status))printerror(status);
    if (verbose) cout << "SAL3Eventlist::read() number of cols " << ncols << endl;
*/
//
	//if(fits_close_file(in, &status)) printerror(status);


    pInfile = (FITS *)new FITS(fn,Read,hdus,false);

    ExtHDU& table = pInfile->extension(hdus[0]) ;

	long int neval; neval = table.rows();
	cout << "SAL3Eventlist::read() reading # of rows  "<< neval << endl;
    dimension = (unsigned long int)neval; // dimension of the external eventlist structure
    dim = (unsigned long int)neval;  // dimension of the dim field of the eventlist

   try {

     table.column("COUNT").read( COUNT, 1, dimension ) ;

         cout << "read COUNT column " << endl;
}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << "Fits Exception Thrown by SAL3Eventlist::read() function (reading COUNT) \n" ;
}

   try {

     table.column("PHOTON_ID").read( PHOTON_ID, 1, dimension ) ;

         cout << "read PHOTON_ID column " << endl;
}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << "Fits Exception Thrown by SAL3Eventlist::read() function (reading SSID) \n" ;
}


try
{
   table.column("TIME").read(TIME, 1, dimension);

    cout << "read TIME column " << endl;


}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading time) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in time reading \n" ;

}
catch (CCfits::Column::InvalidDataType) {
  cout << "exception thrown by CCfits \n"<< endl;
}

catch (...) {
  cout << "exception thrown reading time column \n"<< endl;
}


try
{
      table.column("AMPLITUDE").read( AMPLITUDE, 1, dimension ) ;
     cout << "read AMPLITUDE column " << endl;
//    ff.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading amplitude) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in amplitude reading \n" ;

}
    try{

     table.column("POS").read( POS, 1, dimension ) ;
     cout << "read POS column " << endl;
  //  ss.resize(0);
}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading position) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in position reading \n" ;

}

try{
     table.column("DETECTOR").read( DETECTOR, 1,  dimension );
    cout << "read DETECTOR column " << endl;
//     bb.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading detector) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in detector reading \n" ;

}

try{
     table.column("POS_SHIFT").read( POS_SHIFT, 1, dimension );
     cout << "read POS_SHIFT column " << endl;
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading POS_SHIFT) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in POS_SHIFT reading \n" ;

}

try{
     table.column("SSID").read( SSID, 1,  dimension) ;
     cout << "read SSID column " << endl;
}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << "Fits Exception Thrown by SAL3Eventlist::read() function (reading SSID) \n" ;
}


} catch (const exception &e){
       std::cerr << " error in FITS reading \n" ;

}

  tm.stop();
  tm.report();

  //delete in;
  delete pInfile;

}

/*!
    \fn SAdata::SAL3Eventlist::readDebug2(string &fn)
 */
void SAdata::SAL3Eventlist::readDebug2(string &fn)
{
	verbose = true;
        tm.start();
        if (verbose) cout << "SAL3Eventlist::readDebug() executing " << endl;
        fitsfile * in = (fitsfile*) new fitsfile[1];
        if (verbose) cout << "SAL3Eventlist::readDebug() created input fitsfile object (cfitsio)" << endl;
         //verbose = false;
try
{
     // read a table and explicitly read selected columns. To read instead all the
     // data on construction, set the last argument of the FITS constructor
     // call to 'true'. This functionality was tested in the last release

     std::vector<string> hdus(2) ;

     std::vector<long int> pp;

     std::vector<short int> ss;

     std::vector<long long int> ll;

     std::vector<unsigned char> bb;

     std::vector<float> ff;
    
     unsigned long long int * cftime;

     int k; int ncols;
     long nrows = 0;   	 int colnum = 0;

     int status = 0;
     tempstring = (string)"EVENTS" ;
     hdus[1] = tempstring;

     //std::auto_ptr<FITS> pInfile(new FITS(fn,Read,hdus,false));
    if (verbose) cout << "SAL3Eventlist::read() going to read fitsfile " << fn << endl;
    if (verbose) cout << "SAL3Eventlist::read() going to read extension " << hdus[1] << endl;

    pInfile = (FITS *)new FITS(fn,Read,hdus,false);

    ExtHDU& table = pInfile->extension(hdus[1]) ;

    fits_open_file(&in, fn.c_str(), READONLY, &status);
    if (verbose) cout << "SAL3Eventlist::read() fitsfile is open (cfitsio)" << endl;

    fits_movabs_hdu(in, 2, NULL, &status);
    if (verbose) cout << "SAL3Eventlist::read() reached extension 2 (cfitsio)" << endl;

   	fits_get_num_rows(in, &nrows, &status);
    if (verbose) cout << "SAL3Eventlist::read() number of rows " << nrows << endl;
	fits_get_num_cols(in, &ncols, &status);
    if (verbose) cout << "SAL3Eventlist::read() number of cols " << ncols << endl;
     dimension = nrows; // dimension of the external eventlist structure
    dim = nrows;  // dimension of the dim field of the eventlist
//

   try {

     table.column("COUNT").read(pp, 1, dimension ) ;
     unsigned int  i=0;
     while(i< dimension){
     if (verbose)      cout <<  "COUNT = " << pp[i] << endl;
       COUNT[i] = pp[i];
      i++ ;
     }
        if (verbose) cout << "read COUNT column " << endl;

     pp.resize(0);

     table.column("PHOTON_ID").read(pp, 1, dimension) ;
      i=0;
     while(i< dimension){
      if (verbose) if (verbose) cout <<  "PHOTON_ID = " << pp[i] << endl;
       PHOTON_ID[i] = pp[i];
      i++ ;
     }
        if (verbose) cout << "read PHOTON_ID column " << endl;

     pp.resize(0);
}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading photon_id) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in photon_id reading \n" ;

}

try
{
      table.column("AMPLITUDE").read(ff, 1, dimension ) ;
     i=0;
     while(i< dimension){
        AMPLITUDE[i] = ff[i];
      if (verbose) cout <<  "AMPLITUDE = " << ff[i] << endl;
      i++ ;
     }
     if (verbose) cout << "read AMPLITUDE column " << endl;
    ff.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading amplitude) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in amplitude reading \n" ;

}
    try{

     table.column("POS").read(ss, 1, dimension ) ;
     i=0;
     while(i< dimension){
       if (ss[i]==1540) ss[i]=0;
        POS[i] = ss[i];
      if (verbose) cout <<  "POS = " << ss[i] << endl;
      i++ ;
     }
     if (verbose) cout << "read POS column " << endl;
    ss.resize(0);
}
catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading position) \n" ;

//       std::cerr << " exception number " << e << endl;

} catch (const exception &e){
       std::cerr << " error in position reading \n" ;

}
try{
     table.column("DETECTOR").read(bb, 1,  dimension );
     i=0;
     while(i< dimension){
       DETECTOR[i] = bb[i];
      k = (int)bb[i];
      if (verbose) cout <<  "DETECTOR = " << k << endl;
      i++ ;
     }
    if (verbose) cout << "read DETECTOR column " << endl;
     bb.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading detector) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in detector reading \n" ;

}

try{
     table.column("POS_SHIFT").read(ff, 1, dimension );
     i=0;
     while(i< dimension){
      if (verbose) cout <<  "POS_SHIFT = " << ff[i] << endl;
       POS_SHIFT[i] =ff[i];
      i++ ;
     }
      if (verbose) cout << "read POS_SHIFT column " << endl;
     ff.resize(0);
} catch (FitsException& e)
//catch (CCfits::Column::InvalidDataType)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << " Fits Exception Thrown by SAL3Eventlist::read() function (reading POS_SHIFT) \n" ;

//       std::cerr << " exception number " << e << endl;;

} catch (const exception &e){
       std::cerr << " error in POS_SHIFT reading \n" ;

}

try{
     table.column("SSID").read(bb, 1,  dimension) ;
     i=0;
     while(i< dimension){
      k = (int)bb[i];
      if (verbose) cout <<  " = " << (int)bb[i] << endl;
       SSID[i] = bb[i];
      i++ ;
     }
      if (verbose) cout << "read SSID column " << endl;
      bb.resize(0);


}
catch (FitsException&)
// will catch all exceptions thrown by CCfits, including errors
// found by cfitsio (status != 0)
{
       std::cerr << "Fits Exception Thrown by SAL3Eventlist::read() function (reading SSID) \n" ;
}
} catch (const exception &e){
       std::cerr << " error in SSID reading \n" ;

}

  
  tm.stop();
  tm.report();

  delete in;

  delete pInfile;

verbose = false;


}


/*!
    \fn SAdata::SAL3Eventlist::readGTI(const string &gtifn)
 */
void SAdata::SAL3Eventlist::readGTI(const string &gtifn)
{
    /// @todo implement me
}
void SAdata::SAL3Eventlist::readSagaGTI(const string &gtifn)
{
    /// @todo implement me
}
void SAdata::SAL3Eventlist::readExposureGTI(const string &gtifn)
{
    /// @todo implement me
}

  /** */
  void SAdata::SAL3Eventlist::printerror( int status){
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

/*     std::vector<long int> pp( dimension);
     std::vector<long int>::iterator ipp;

     std::vector<short int> ss( dimension);
     std::vector<short int>::iterator iss;
     std::vector<long long int> ll( dimension);
     std::vector<long long int>::iterator ill;

     std::vector<unsigned char> bb( dimension);
     std::vector<unsigned char>::iterator ibb;

     std::vector<float> ff( dimension);
     std::vector<float>::iterator iff;
*/
/*
        vector<long int> COUNT;
        vector<long int> PHOTON_ID;
        vector<long long int> TIME;
        vector<float> AMPLITUDE;
        vector<short int> POS;
        vector<unsigned char> DETECTOR;
        vector<float> POS_SHIFT;
        vector<unsigned char> SSID; //Number: 8   unit:format: B comment:
*/


/*!
    \fn SAdata::SAL3Eventlist::createPointHistos2()
 */
void SAdata::SAL3Eventlist::createPointHistos2()
{
 if (verbose) cout << "SAL3Eventlist::createPointHistos2() started"<< endl;
    verbose = true;

    float EnMin;    float EnMax;    short int N_regions;

    float maxangle;    float f_length;    float s_width;

    float delta_norm;    int dimss;    float  Tburst;
   /** */
//   float C_Angles[NREGVAL];
   /** */
//   float C_Coeffs[NREGVAL];
   /** */
   short int C_Shifts[NREGVAL];
   /** */
   short int C_Coords[NREGVAL];   
//    verbose = true;
    verbose = false;
     /** */
    char *starts = new char[55];
   /** */
    char *cfin_out = new char[64];
   /** */
    char *cfin_p = new char[64];                                       

         /// ######## REMEMBER TO CHANGE
//          dimension = 10;
         /// ######## REMEMBER TO CHANGE

	N_regions = 10;	Hist_Size = 1024;
 if (verbose) cout << "createPointHistos() executing SAL3Eventlist::saveIrosMap()"<< endl;
  //      system("rm test.dat");
 if (verbose) cout << "createPointHistos() going to write following data" << endl;

          string ss("SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR");
          string fin_out("pippo1"); // name of the file
          string fin_p("plutone2");
          starts = (char *)ss.c_str();
           i_fn_length_0 = strlen(starts);
           if (verbose) cout << "startstring �lunga "<< i_fn_length_0 << endl;
           cfin_out = (char *)"pippo1";
           cfin_p = (char *)"plutone2";
           i_fn_length_1 = strlen(cfin_out);
           i_fn_length_2  = strlen(cfin_p);
           if (verbose) cout << "going to write the string "<< cfin_out << endl;
           if (verbose) cout << "that is  "<< i_fn_length_1 << " chars long" << endl;
           Tburst = (float)PI;

           D_Seq[0] = 2;       D_Seq[1] = 3;    D_Seq[2] = 0;       D_Seq[3] = 1;

            N_regions =  NREGVAL;   Hist_Size = HISTSIZVAL;    Nchan = NCHANVAL;

            float *C_Angles = new float[N_regions];     float *C_Coeffs = new float[N_regions];
            float *Point_Hist_x = new float[Hist_Size];  
			float *Point_Hist_z = new float[Hist_Size];

            for(w=0; w<N_regions; w++) C_Index[w] = (short int)w;
            for(int h=0; h<1024; h++){
                 Point_Hist_x[h] = 0.;
                 Point_Hist_z[h] = 0.;                 
            }

            /// Setting default values

    /** */
     max_angle = 60.;

     /** */
    f_length = 14.14;

     /** */
    s_width = 0.0121;

     /** */
     delta_norm = f_length/s_width;

     /** */
     EnMin = 15.;

     /** */
     EnMax = 100.;

     if (verbose) cout << "createPointHistos() writing pointing histogram " <<  endl;

     /** */
     for(w=0; w<N_regions; w++){
	   C_Angles[w] = max_angle/N_regions*(2.*w-1.)/2.;
	   C_Coeffs[w] = delta_norm*(tan(C_Angles[w]*PI/180.)-tan((C_Angles[w]-1.)*PI/180.));
	   C_Coeffs[w] = C_Coeffs[w]*1.00/0.93;
     }

///  pointing histogram creation
    float Psi_s_z;  float Psi_s_x;
    Psi_s_z = 0;  Psi_s_x = 0;


/// loop on all the events of the eventlist
    if (verbose) cout << "createPointHistos() loop on all the events of the eventlist" << endl;

unsigned long int c;  c = 0;

/// ###### REMEMBER TO CHANGE
// dimension = 10;
/// ###### REMEMBER TO CHANGE


while (c< dimension){

    ev = getEvent(c); /// get the temp event

 // verbose = true;

   if (verbose) {
     if (verbose) cout << "createPointHistos() events  n " << c << endl;
     ev.show();
   }
    iside 	= 0;

    if (ev.getPos() > 767) {
	     iside = 1;
          //	   ev.getPos() = ev.getPos() - 768;
          ev.setPos(ev.getPos() - 768);
	  }

        switch(ev.getDetector()){
          case 0:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		    C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
		  }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
          break;
          case 1:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]	= Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 2:
          Psi_s_z = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = +1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
          }
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])] = Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 3:
          Psi_s_x = ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = -1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		  Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])] = Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          default:    /// INSERT AN EXCEPTION
           if (verbose) cout << "wrong detector number !!!" << endl;
          break;
        }

        for(w=0; w<N_regions; w++){
            C_Coords[C_Index[i]] = C_Shifts[C_Index[i]] + ev.getPos();
        }

        for(w=0; w<N_regions; w++){ // loop on the sky region
        cond1 = (C_Coords[C_Index[i]] > 0);
        cond2 = (C_Coords[C_Index[i]] < 767);
//        cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
        if (cond1 && cond2) {
//	          if (cond3) {
		          MDImage[C_Index[i]] [ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768] =  MDImage[C_Index[i]][ev.getDetector()][1+C_Coords[C_Index[i]]+iside*768]+1;
//	          }
	        }
         }
  c++;
}

        for(int i=0; i<1024; i++) {
          xx_xg[i] = (int)i;
          if (Point_Hist_x[i]>=0){          
            yy_xg[i] = (unsigned long int)Point_Hist_x[i];
          } else {
            yy_xg[i]=0;
          }
          if (verbose) cout << i << "createPointHistos() yy_xg = "<<  Point_Hist_x[i] << endl;
        }

        for(int i=0; i<1024; i++) {
          xx_zg[i] = (int)i;
          if (Point_Hist_z[i]>=0){
            yy_zg[i] = (unsigned long int)Point_Hist_z[i];
          } else {
            yy_zg[i] = 0;
          }
          if (verbose) cout << i << "createPointHistos() yy_zg = "<<  Point_Hist_z[i] << endl;
        }
        
  
  delete [] Point_Hist_x;
  delete [] Point_Hist_z;

  verbose = false;
  
 if (verbose) cout << "SAL3Eventlist::createPointHistos()2 ended"<< endl;
}


/*!
    \fn SAdata::SAL3Eventlist::filterTime(double timemin, double timemax)
 */
void SAdata::SAL3Eventlist::filterTime(double timemin, double timemax)
{
	verbose = true;
	success = false;
	try{
	//vector<long int>::iterator lit;

	count_lit = COUNT.begin();	pid_lit = PHOTON_ID.begin();	time_dit = TIME.begin();
	ampli_fit = AMPLITUDE.begin();	pos_sit = POS.begin();	det_ucit = DETECTOR.begin();
	posh_fit = POS_SHIFT.begin();	ss_ucit = SSID.begin();
	unsigned long int cu, newcu; cu = 0;	newcu = 0;
		while( count_lit != COUNT.end()){

	if	((*time_dit>timemin)&&(*time_dit<timemax)){

	//cout << "Accepted n. " << (count_lit - COUNT.begin()) << "time = " <<*time_dit 
	//	<< " tmin = " << timemin << " tmax = "<< timemax << endl;
		success = true;
		myCOUNT.push_back(*count_lit); myPHOTON_ID.push_back(*pid_lit); myTIME.push_back(*time_dit);
		myAMPLITUDE.push_back(*ampli_fit);	myPOS.push_back(*pos_sit);	myDETECTOR.push_back(*det_ucit);
	    myPOS_SHIFT.push_back(*posh_fit);	mySSID.push_back(*ss_ucit);	
		newcu++;
	}
	count_lit++;	pid_lit++;	time_dit++;
	ampli_fit++;	pos_sit++;	det_ucit++;
	posh_fit++;	ss_ucit++;
	} 		

	if (success) {
	if (verbose){
		cout << "SAL3Eventlist::filterTime() executing, eventlist dimension =  "<< dimension << endl;
		cout << "SAL3Eventlist::filterTime() executing, tmin = " << timemin << " tmax = "<< timemax << endl;
	}
	if (verbose)	cout << "SAL3Eventlist::filterTime() accepted event n. "<<  newcu << endl; 
	if ((myCOUNT.size()>0)&&(verbose)){
	cout << "SAL3Eventlist::filterTime() eventlist dimension =  "<< COUNT.size() << endl;
/*		
		cout << "COUNT.size() = " << myCOUNT.size() << endl;
		cout << "PHOTON_ID.size() = " <<myPHOTON_ID.size() << endl;
		cout << "TIME.size() = " << myTIME.size() << endl;
		cout << "AMPLITUDE.size() = " << myAMPLITUDE.size() << endl;
		cout << "POS.size() = " << myPOS.size() << endl;
		cout << "DETECTOR.size() = " << myDETECTOR.size() << endl;
		cout << "POS_SHIFT.size() = " << myPOS_SHIFT.size() << endl;
		cout << "SSID.size() = " << mySSID.size() << endl;
*/
	}
	cout << "SAL3Eventlist::filterTime() total number of accepted events n. "<< newcu << " (to be saved ...)" << endl; 
	}
	verbose = false;
} catch(...){
	cerr << "error in time filtering the eventlist " << endl;
}

/*	COUNT = myCOUNT;	PHOTON_ID = myPHOTON_ID;	TIME = myTIME;
	AMPLITUDE = myAMPLITUDE;	POS =  myPOS;DETECTOR = myDETECTOR;
	POS_SHIFT = myPOS_SHIFT;	SSID =  mySSID; 
*/
}


/*!
    \fn SAdata::SAL3Eventlist::filterAllGTI(const string &gtifname)
 */
void SAdata::SAL3Eventlist::filterAllGTI(const string &gtifname)
{
    // read GTI 
	string newstring = "_";
	newstring += gtifname.substr(gtifname.find_last_of("/")+1, (gtifname.size() - gtifname.find_last_of(".")));
	setFilterTarget(newstring);
	myCOUNT.clear();	myPHOTON_ID.clear();	myTIME.clear();
	myAMPLITUDE.clear();	myPOS.clear();	myDETECTOR.clear();
	myPOS_SHIFT.clear();	mySSID.clear();

	  SAGTI mygti;
  	  mygti.read(gtifname);
      double mytmin, mytmax;
	  vector<GTI>::iterator it;
	  it = mygti.begin();
	  while (it!=mygti.end()){
		mytmin = it->first; mytmax = it->second;
		if (verbose) cout << "SAL3Eventlist::filterAllGTI() tmin =  " << mytmin << " tmax = "<< mytmax << endl;
		filterTime(mytmin, mytmax);
		//filterTime(1., 2.);
		if (verbose) cout << "SAL3Eventlist::filterAllGTI() filtered gti n. "<< (it-mygti.begin() + 1) << endl;
		it++;
	  } 

	cout << "filterAllGTI() COUNT.size() = " << myCOUNT.size() << endl;
	cout << "filterAllGTI() PHOTON_ID.size() = " <<myPHOTON_ID.size() << endl;
	cout << "filterAllGTI() TIME.size() = " << myTIME.size() << endl;
	cout << "filterAllGTI() AMPLITUDE.size() = " << myAMPLITUDE.size() << endl;
	cout << "filterAllGTI() POS.size() = " << myPOS.size() << endl;
	cout << "filterAllGTI() DETECTOR.size() = " << myDETECTOR.size() << endl;
	cout << "filterAllGTI() POS_SHIFT.size() = " << myPOS_SHIFT.size() << endl;
	cout << "filterAllGTI() SSID.size() = " << mySSID.size() << endl;

	COUNT.clear();	PHOTON_ID.clear(); TIME.clear();
	AMPLITUDE.clear();	POS.clear();	DETECTOR.clear();
	POS_SHIFT.clear();	SSID.clear();

	copy(myCOUNT.begin(), myCOUNT.end(), COUNT.begin());
	copy(myPHOTON_ID.begin(), myPHOTON_ID.end(), PHOTON_ID.begin());
	copy(myTIME.begin(), myTIME.end(), TIME.begin());
	copy(myAMPLITUDE.begin(), myAMPLITUDE.end(), AMPLITUDE.begin() );
	copy(myPOS.begin(), myPOS.end(), POS.begin());
	copy(myDETECTOR.begin(), myDETECTOR.end(), DETECTOR.begin());
	copy(myPOS_SHIFT.begin(), myPOS_SHIFT.end(), POS_SHIFT.begin());
	copy(mySSID.begin(), mySSID.end(), 	SSID.begin());

/*
	COUNT = myCOUNT;	PHOTON_ID = myPHOTON_ID;	TIME = myTIME;
	AMPLITUDE = myAMPLITUDE;	POS = myPOS;	DETECTOR = myDETECTOR;
	POS_SHIFT = myPOS_SHIFT;	SSID = mySSID;
*/
	count_lit = COUNT.begin();
	bool fatto = false;
	while( count_lit != COUNT.end()){
		cout << "count = " << *count_lit++<< endl;
		fatto = true;
	}
	if (fatto) {
	cout << "SAL3Eventlist::filterAllGTI() vectors are full " << endl;
	} else cout << "SAL3Eventlist::filterAllGTI() vectors are empty " << endl;


	if (SAEventlist::isSaveFiltered()){
		//string newfn("time_filtered_list_L3.evt");
		string newfn = arc->filenamer.getOutputFileName(SourcesExtraction);
		string ots = newfn.insert(newfn.find_last_of("."), getFilterTarget());
	cout << "SAL3Eventlist::filterAllGTI() filtered list name =  " << ots << endl;
		//newfn.insert(newfn.find_last_of("."), getFilterTarget());
		saveFiltered(ots);
	} else {
		cout << "SAL3Eventlist::filterAllGTI() filtered list is NOT saved" << endl;
	}

	double c = getExposure();
	// extract vector of pair<double, double>
 	// filter l3list for all the pairs
}


/*!
    \fn SAdata::SAL3Eventlist::saveFiltered(const string &outfilename)
 */
void SAdata::SAL3Eventlist::saveFiltered(const string &outfilename)
{
  
    std::auto_ptr<FITS> pFits(0);

    try
    {
        //const std::string fileName("atestfil.fit");
        pFits.reset( new FITS(outfilename,Write) );
    }
    catch (CCfits::FITS::CantOpen)
    {
          cerr << "SAL3Eventlist::save() exception in opening the outfile" << endl;
    }
//
//
    unsigned long rows = myCOUNT.size();

   if (verbose) cout << "SAL3Eventlist::save() Number of rows of the output file = "<< rows << endl;    
    string hduName("EVENTS");
    std::vector<string> colName(8,"");
    std::vector<string> colForm(8,"");
    std::vector<string> colUnit(8,"");
    
    colName[0] = "COUNT";            colForm[0] = "J";     colUnit[0] = "n";
    colName[1] = "PHOTON_ID";    colForm[1] = "J";     colUnit[1] = "n";
    colName[2] = "TIME";               colForm[2] = "D";     colUnit[2] = "s";
    colName[3] = "AMPLITUDE";     colForm[3] = "E";     colUnit[3] = "pha";
    colName[4] = "POS";                 colForm[4] = "I";     colUnit[4] = "..";
    colName[5] = "DETECTOR";      colForm[5] = "B";     colUnit[5] = "n";
    colName[6] = "POS_SHIFT";      colForm[6] = "E";     colUnit[6] = "..";
    colName[7] = "SSID";                colForm[7] = "B";     colUnit[7] = "n";


  int val = 0;
  
 std::vector<long> count; // 
 std::vector<long> photon_id; // 
 std::vector<double> time;  // 
 std::vector<float> amplitude; // 
 std::vector<int> pos; // 
 std::vector<unsigned char> detector;
 std::vector<float> pos_shift;
 std::vector<unsigned char> ssid;

 unsigned long int rc;

	cout << "saveFiltered() new dimension = " << rows << endl;
	cout << "saveFiltered() saving on filename = " <<  outfilename << endl;

  for(rc=0; rc<rows; rc++){
        //if (rc<10)getEvent(rc).show();    
        count.push_back(myCOUNT[rc]);
        photon_id.push_back(myPHOTON_ID[rc]);
        time.push_back((double)myTIME[rc]);
        amplitude.push_back(myAMPLITUDE[rc]);
        if(myPOS[rc]>0){
          pos.push_back(myPOS[rc]);
        } else pos.push_back((int)1540);        
        detector.push_back((unsigned char)myDETECTOR[rc]);
        pos_shift.push_back(myPOS_SHIFT[rc]);
        ssid.push_back((unsigned char)mySSID[rc]);
  }

 Table* newTable;
 
try{
    newTable = pFits->addTable(hduName,rows,colName,colForm,colUnit);
} catch (FitsException& f){
  cerr << "FITS exception : error in adding the eventlist table"<< endl;
} catch(const exception &e){
  cerr << "standard exception : error in adding the eventlist table"<< e.what() << endl;  
} catch (...){
  cerr << "exception : error in adding the eventlist table" << endl;  
}

      try{
        newTable->column(colName[0]).write(count,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing count"<< endl;
        for(int k=0; k<count.size(); k++)cerr << "count = "<< count[k] << endl;
      }
      try{
        newTable->column(colName[1]).write(photon_id,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing photon_id"<< endl;
        for(int k=0; k<photon_id.size(); k++) cerr << "photon_id = "<< photon_id[k] << endl;
      }
      try{
        newTable->column(colName[2]).write(time,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing time"<< endl;
        for(int k=0; k<time.size(); k++) cerr << " time = "<< time[k] << endl;
      }
      try{
        newTable->column(colName[3]).write(amplitude,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing amplitude"<< endl;
        for(int k=0; k<amplitude.size(); k++) cerr << " amplitude = "<< amplitude[k] << endl;
      }
      try{
        newTable->column(colName[4]).write(pos,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing pos"<< endl;
        for(int k=0; k<pos.size(); k++) cerr << " pos = "<< pos[k] << endl;
      }
      try{
      newTable->column(colName[5]).write(detector,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing detector"<< endl;
        for(int k=0; k<detector.size(); k++) cerr << " detector = "<< detector[k] << endl;
      }
      try{
        newTable->column(colName[6]).write(pos_shift,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing pos_shift"<< endl;
        for(int k=0; k<pos_shift.size(); k++) cerr << " pos_shift = "<< pos_shift[k] << endl;
      }
      try{
        newTable->column(colName[7]).write(ssid,1);
      } catch (FitsException& f){
        cerr << "FITS exception : error in writing ssid"<< endl;
        for(int k=0; k<ssid.size(); k++) cerr << " ssid = "<< ssid[k] << endl;
      }
      

//
//    //add a history string. This function call is in HDU:: so is identical
//    //for all HDUs
//
    string hist("This file was created for testing CCfits write functionality");
    hist += " it serves no other useful purpose. This particular part of the file was ";
    hist += " constructed to test the writeHistory() and writeComment() functionality" ;
//
//
    newTable->writeHistory(hist);
//
//    // add a comment string. Use std::string method to change the text in the message
//    // and write the previous junk as a comment.
//
    hist.insert(0, " COMMENT TEST ");
//
    newTable->writeComment(hist);
//
//    // ... print the result.
//
    //std::cout << *newTable << std::endl;
//
//    return 0;
}
void SAdata::SAL3Eventlist::filterDetector(unsigned char detmin, unsigned char detmax)
{
	verbose = true;
	try{
	//vector<long int>::iterator lit;
	count_lit = COUNT.begin();	pid_lit = PHOTON_ID.begin();	time_dit = TIME.begin();
	ampli_fit = AMPLITUDE.begin();	pos_sit = POS.begin();	det_ucit = DETECTOR.begin();
	posh_fit = POS_SHIFT.begin();	ss_ucit = SSID.begin();
	unsigned long int cu, newcu; cu = 0;	newcu = 0;
	cout << "SAL3Eventlist::filterDetector() executing, evenlist dimension =  "<< dimension << endl;
	cout << "SAL3Eventlist::filterDetector() executing, detmin = " << detmin << " detmax = "<< detmax << endl;
	
	while( count_lit != COUNT.end()){

	if	((*det_ucit>=detmin)&&(*det_ucit<=detmax)){

	//cout << "Accepted n. " << (count_lit - COUNT.begin()) << "time = " <<*time_dit 
	//	<< " tmin = " << timemin << " tmax = "<< timemax << endl;
		myCOUNT.push_back(*count_lit); myPHOTON_ID.push_back(*pid_lit); myTIME.push_back(*time_dit);
		myAMPLITUDE.push_back(*ampli_fit);	myPOS.push_back(*pos_sit);	myDETECTOR.push_back(*det_ucit);
	    myPOS_SHIFT.push_back(*posh_fit);	mySSID.push_back(*ss_ucit);	
		newcu++;
	}
	count_lit++;	pid_lit++;	time_dit++;
	ampli_fit++;	pos_sit++;	det_ucit++;
	posh_fit++;	ss_ucit++;
	} 		
	if (verbose)	cout << "SAL3Eventlist::filterDetector() accepted event n. "<<  newcu << endl; ;
	cout << "COUNT.size() = " << myCOUNT.size() << endl;
	cout << "PHOTON_ID.size() = " <<myPHOTON_ID.size() << endl;
	cout << "TIME.size() = " << myTIME.size() << endl;
	cout << "AMPLITUDE.size() = " << myAMPLITUDE.size() << endl;
	cout << "POS.size() = " << myPOS.size() << endl;
	cout << "DETECTOR.size() = " << myDETECTOR.size() << endl;
	cout << "POS_SHIFT.size() = " << myPOS_SHIFT.size() << endl;
	cout << "SSID.size() = " << mySSID.size() << endl;
			verbose = false;
			cout << "SAL3Eventlist::filterDetector() total number of accepted events n. "<< newcu << endl; 
} catch(...){
	cerr << "error in filtering the eventlist for detectors" << endl;
}

}

/*!
    \fn SAdata::SAL3Eventlist::filterAllDetectors()
 */
void SAdata::SAL3Eventlist::filterAllDetectors()
{
	filt_list_name.resize(5);
	tempstring = "det_0.evt";	setFilteredListName(tempstring, 0);
	tempstring = "det_1.evt";	setFilteredListName(tempstring, 1);
	tempstring = "det_2.evt";	setFilteredListName(tempstring, 2);
	tempstring = "det_3.evt";	setFilteredListName(tempstring, 3);
	tempstring = "filtered_list.evt";	setFilteredListName(tempstring, 4);
	clearTempVectors();
	resetTime(0.);	
	saveFiltered(filt_list_name[4]);
	update();
	clearTempVectors();
    filterDetector(0, 0);
	saveFiltered(filt_list_name[0]);
	clearTempVectors();
    filterDetector(1, 1);
	saveFiltered(filt_list_name[1]);
	clearTempVectors();
    filterDetector(2, 2);
	saveFiltered(filt_list_name[2]);
	clearTempVectors();
    filterDetector(3, 3);
	saveFiltered(filt_list_name[3]);
	filt_list_name.clear();
}


/*!
    \fn SAdata::SAL3Eventlist::clearTempVectors()
 */
void SAdata::SAL3Eventlist::clearTempVectors()
{
  	myCOUNT.clear();	myPHOTON_ID.clear(); myTIME.clear();
	myAMPLITUDE.clear();	myPOS.clear();	myDETECTOR.clear();
	myPOS_SHIFT.clear();	mySSID.clear();
}


/*!
    \fn SAdata::SAL3Eventlist::clearDataVectors()
 */
void SAdata::SAL3Eventlist::clearDataVectors()
{
  	COUNT.clear();	PHOTON_ID.clear(); TIME.clear();
	AMPLITUDE.clear();	POS.clear();	DETECTOR.clear();
	POS_SHIFT.clear();	SSID.clear();
}

/*!
    \fn SAdata::SAL3Eventlist::setFilteredListName(const string &n, int num)
 */
void SAdata::SAL3Eventlist::setFilteredListName(const string &n, int num)
{
    filt_list_name[num] = n;
}

/*!
    \fn SAdata::SAL3Eventlist::resetTime(double tzero)
 */
void SAdata::SAL3Eventlist::resetTime(double tzero)
{
	verbose = true;
	try{
	count_lit = COUNT.begin();	pid_lit = PHOTON_ID.begin();	time_dit = TIME.begin();
	ampli_fit = AMPLITUDE.begin();	pos_sit = POS.begin();	det_ucit = DETECTOR.begin();
	posh_fit = POS_SHIFT.begin();	ss_ucit = SSID.begin();
	unsigned long int cu, newcu; cu = 0;	newcu = 0;
	cout << "SAL3Eventlist::resetTime() executing, eventlist dimension =  "<< dimension << endl;	
	double tstart; bool first = true; 
	while( count_lit != COUNT.end()){
		if (first) tstart = *time_dit;
		myCOUNT.push_back(*count_lit); myPHOTON_ID.push_back(*pid_lit); myTIME.push_back((*time_dit-tstart)+tzero);
		myAMPLITUDE.push_back(*ampli_fit);	myPOS.push_back(*pos_sit);	myDETECTOR.push_back(*det_ucit);
	    myPOS_SHIFT.push_back(*posh_fit);	mySSID.push_back(*ss_ucit);	
		newcu++;
	count_lit++;	pid_lit++;	time_dit++;
	ampli_fit++;	pos_sit++;	det_ucit++;
	posh_fit++;	ss_ucit++;
	first = false;
	} 		
	verbose = false;
			cout << "SAL3Eventlist::resetTime() total number of re-tagged events n. "<< newcu << endl; 
} catch(...){
	cerr << "error in time filtering the eventlist " << endl;
}
}

void  SAdata::SAL3Eventlist::update(){
	cout << "SAL3Eventlist::update() executing"<< endl; 

	copy(myCOUNT.begin(), myCOUNT.end(), COUNT.begin());
	copy(myPHOTON_ID.begin(), myPHOTON_ID.end(), PHOTON_ID.begin());
	copy(myTIME.begin(), myTIME.end(), TIME.begin());
	copy(myAMPLITUDE.begin(), myAMPLITUDE.end(), AMPLITUDE.begin() );
	copy(myPOS.begin(), myPOS.end(), POS.begin());
	copy(myDETECTOR.begin(), myDETECTOR.end(), DETECTOR.begin());
	copy(myPOS_SHIFT.begin(), myPOS_SHIFT.end(), POS_SHIFT.begin());
	copy(mySSID.begin(), mySSID.end(), 	SSID.begin());
	clearTempVectors();
}
void SAdata::SAL3Eventlist::filterEnergy(float emin, float emax){
	try{
	//vector<long int>::iterator lit;

	count_lit = COUNT.begin();	pid_lit = PHOTON_ID.begin();	time_dit = TIME.begin();
	ampli_fit = AMPLITUDE.begin();	pos_sit = POS.begin();	det_ucit = DETECTOR.begin();
	posh_fit = POS_SHIFT.begin();	ss_ucit = SSID.begin();
	unsigned long int cu, newcu; cu = 0;	newcu = 0;
	if (verbose){
		cout << "SAL3Eventlist::filterEnergy() executing, evenlist dimension =  "<< dimension << endl;
		cout << "SAL3Eventlist::filterEnergy() executing, energymin = " << emin << " energymax = "<< emax << endl;
	}
	while( count_lit != COUNT.end()){

	if	((*ampli_fit>emin)&&(*ampli_fit<emax)){

	//cout << "Accepted n. " << (count_lit - COUNT.begin()) << "time = " <<*time_dit 
	//	<< " tmin = " << timemin << " tmax = "<< timemax << endl;

		myCOUNT.push_back(*count_lit); myPHOTON_ID.push_back(*pid_lit); myTIME.push_back(*time_dit);
		myAMPLITUDE.push_back(*ampli_fit);	myPOS.push_back(*pos_sit);	myDETECTOR.push_back(*det_ucit);
	    myPOS_SHIFT.push_back(*posh_fit);	mySSID.push_back(*ss_ucit);	
		newcu++;
	}
	count_lit++;	pid_lit++;	time_dit++;
	ampli_fit++;	pos_sit++;	det_ucit++;
	posh_fit++;	ss_ucit++;
	} 		


	if (verbose)	{
	cout << "SAL3Eventlist::filterEnergy() accepted event n. "<<  newcu << endl; ;
	cout << "COUNT.size() = " << myCOUNT.size() << endl;
	cout << "PHOTON_ID.size() = " <<myPHOTON_ID.size() << endl;
	cout << "TIME.size() = " << myTIME.size() << endl;
	cout << "AMPLITUDE.size() = " << myAMPLITUDE.size() << endl;
	cout << "POS.size() = " << myPOS.size() << endl;
	cout << "DETECTOR.size() = " << myDETECTOR.size() << endl;
	cout << "POS_SHIFT.size() = " << myPOS_SHIFT.size() << endl;
	cout << "SSID.size() = " << mySSID.size() << endl;
	}

	cout << "SAL3Eventlist::filterEnergy() total number of accepted events n. "<< newcu << endl; 		newdimension = newcu;
} catch(...){
	cerr << "error in energy filtering the eventlist " << endl;
}

}

/*!
    \fn SAdata::SAL3Eventlist::effect()
 */
void SAdata::SAL3Eventlist::effect()
{
	verbose = true;
	try{
	cout << "SAL3Eventlist::effect() executing after filtering, now saving, new eventlist dimension =  "<< newdimension << endl;	

	dimension = newdimension;
        clearDataVectors();
	COUNT.assign(myCOUNT.begin(), myCOUNT.end()); 
	PHOTON_ID.assign(myPHOTON_ID.begin(), myPHOTON_ID.end());  
	TIME.assign(myTIME.begin(), myTIME.end());
	AMPLITUDE.assign(myAMPLITUDE.begin(), myAMPLITUDE.end());
	POS.assign(myPOS.begin(), myPOS.end());
	DETECTOR.assign(myDETECTOR.begin(), myDETECTOR.end());
	POS_SHIFT.assign(myPOS_SHIFT.begin(), myPOS_SHIFT.end());
	SSID.assign(mySSID.begin(), mySSID.end());
	clearTempVectors();
	verbose = false;
			cout << "SAL3Eventlist::effect() total number of re-tagged events n. "<< dimension << endl; 

} catch(...){
	cerr << "error in time filtering the eventlist " << endl;
}
}

/*	COUNT.clear(); 
	PHOTON_ID.clear();  
	TIME.clear();
	AMPLITUDE.clear();
	POS.clear();
	DETECTOR.clear();
	POS_SHIFT.clear();
	SSID.clear();

	COUNT.resize(newdimension); 
	PHOTON_ID.resize(newdimension);  
	TIME.resize(newdimension);
	AMPLITUDE.resize(newdimension);
	POS.resize(newdimension);
	DETECTOR.resize(newdimension);
	POS_SHIFT.resize(newdimension);
	SSID.resize(newdimension);
*/
/*  
  for(rc=0; rc<dimension; rc++){
        if (rc<10)getEvent(rc).show();    
        count[rc] = getEvent(rc).getCount();
        photon_id[rc] = getEvent(rc).getPhotonId();
        time[rc] = (double)getEvent(rc).getTime();
        amplitude[rc] = getEvent(rc).getAmplitude();
        if(getEvent(rc).getPos()>0){
          pos[rc] = (int)getEvent(rc).getPos();
} else pos[rc]=(int)1540;        
        detector[rc] = (unsigned char)getEvent(rc).getDetector();
        pos_shift[rc] = getEvent(rc).getPosShift();
        ssid[rc] = (unsigned char)getEvent(rc).getSsid();
}
	COUNT.clear();	PHOTON_ID.clear(); TIME.clear();
	AMPLITUDE.clear();	POS.clear();	DETECTOR.clear();
	POS_SHIFT.clear();	SSID.clear();

*/
/*	
        COUNT.clear(); 
	PHOTON_ID.clear();  
	TIME.clear();
	AMPLITUDE.clear();
	POS.clear();
	DETECTOR.clear();
	POS_SHIFT.clear();
	SSID.clear();
*/


/*!
    \fn SAdata::SAL3Eventlist::filterGTIFile(const string &gtifile)
 */
void SAdata::SAL3Eventlist::filterGTIFile(const string &gtifname)
{
    // read GTI 

	myCOUNT.clear();	myPHOTON_ID.clear();	myTIME.clear();
	myAMPLITUDE.clear();	myPOS.clear();	myDETECTOR.clear();
	myPOS_SHIFT.clear();	mySSID.clear();

	  SAGTI mygti;
  	  mygti.read(gtifname);
      double mytmin, mytmax;
	  vector<GTI>::iterator it;
	  it = mygti.begin();
	  while (it!=mygti.end()){
		mytmin = it->first; mytmax = it->second;
		cout << "SAL3Eventlist::filterGTIFile() tmin =  " << mytmin << " tmax = "<< mytmax << endl;
		filterTime(mytmin, mytmax);
		//filterTime(1., 2.);
		cout << "filtered gti n. "<< (it-mygti.begin() + 1) << endl;
		it++;
	  } 

	cout << "filterGTIFile() COUNT.size() = " << myCOUNT.size() << endl;
	cout << "filterGTIFile() PHOTON_ID.size() = " <<myPHOTON_ID.size() << endl;
	cout << "filterGTIFile() TIME.size() = " << myTIME.size() << endl;
	cout << "filterGTIFile() AMPLITUDE.size() = " << myAMPLITUDE.size() << endl;
	cout << "filterGTIFile() POS.size() = " << myPOS.size() << endl;
	cout << "filterGTIFile() DETECTOR.size() = " << myDETECTOR.size() << endl;
	cout << "filterGTIFile() POS_SHIFT.size() = " << myPOS_SHIFT.size() << endl;
	cout << "filterGTIFile() SSID.size() = " << mySSID.size() << endl;

	COUNT.clear();	PHOTON_ID.clear(); TIME.clear();
	AMPLITUDE.clear();	POS.clear();	DETECTOR.clear();
	POS_SHIFT.clear();	SSID.clear();

	copy(myCOUNT.begin(), myCOUNT.end(), COUNT.begin());
	copy(myPHOTON_ID.begin(), myPHOTON_ID.end(), PHOTON_ID.begin());
	copy(myTIME.begin(), myTIME.end(), TIME.begin());
	copy(myAMPLITUDE.begin(), myAMPLITUDE.end(), AMPLITUDE.begin() );
	copy(myPOS.begin(), myPOS.end(), POS.begin());
	copy(myDETECTOR.begin(), myDETECTOR.end(), DETECTOR.begin());
	copy(myPOS_SHIFT.begin(), myPOS_SHIFT.end(), POS_SHIFT.begin());
	copy(mySSID.begin(), mySSID.end(), 	SSID.begin());

	count_lit = COUNT.begin();
	bool fatto = false;
	while( count_lit != COUNT.end()){
		cout << "count = " << *count_lit++<< endl;
		fatto = true;
	}
	if (fatto) {
	cout << "SAL3Eventlist::filterGTIFile() i vettori sono pieni " << endl;
	} else cout << "SAL3Eventlist::filterGTIFile() i vettori sono vuoti " << endl;
}




/*!
    \fn SAdata::SAL3Eventlist::computeExposure()
 */
double SAdata::SAL3Eventlist::computeExposure()
{
   vector<double>::iterator it;it = TIME.begin();
	unsigned long count;	cout.setf(ios::fixed,ios::floatfield);
	double tstart = *it, tstop = *(TIME.end()-1);
	double totexp = (tstop - tstart);
   SAGTI gtis; double tempdistance;
	cout << "SAL3Eventlist::computeExposure()  Tstart = "  <<tstart << " Tstop = " << tstop << "Tot exposure "<< totexp << endl;
	if (TIME.size()>0){
try{

	GTI tempgti;
	 double temptstart = *it;
	while((it+1)<=TIME.end()){
		 tempdistance = *(it+1) - *it;
		if (tempdistance>1) {
		cout << "SAL3Eventlist::computeExposure() bti extracted tempdistance = " << tempdistance << endl;
			tempgti.first = temptstart;
			tempgti.second = *(it);
		cout << "SAL3Eventlist::computeExposure() saving gti, gti_tstart = " << tempgti.first << "gti_tstop = " << tempgti.second << endl;
			gtis.push_back(tempgti);
			temptstart = *(it+1);
		}
			it++;
	}
			tempgti.first = temptstart;
			tempgti.second = tstop;
			gtis.push_back(tempgti);

	count = 0;
	int cc = gtis.size();
	 cout << "SAL3Eventlist::computeExposure() n. of  found gtis "<< cc << endl;
	tempdistance = 0;
	vector<GTI>::iterator git; git = gtis.begin();
	if (cc > 0){
		while (git<gtis.end()){
			tempgti = *git;
			cout << "SAL3Eventlist::computeExposure() btin n "<< count++ << " gti_tstart = "<< tempgti.first << " gti_tstop "<< tempgti.second << endl;
			tempdistance += (tempgti.second - tempgti.first);
			git++;
		}
	} else {
		cerr << "SAL3Eventlist::computeExposure() no gtis found"<< endl;
	}
} catch(...){
	cerr << "SAL3Eventlist::getExposure() error in calculating the exposure " << endl;
}
	 cout << "SAL3Eventlist::getExposure() returning exposure time "<< tempdistance << " seconds "<< endl;

} else {
	tempstring = "TIME vector is empty";	se.setMsg(tempstring); throw(se);
}
	return tempdistance;
}


/*!
    \fn SAdata::SAL3Eventlist::setExposure(double ex)
 */
void SAdata::SAL3Eventlist::setExposure(double ex)
{
    exposure = ex;
}

/*!
    \fn SAdata::SAL3Eventlist::getExposure()
 */
double SAdata::SAL3Eventlist::getExposure()
{
    return exposure;
}


/*!
    \fn SAdata::SAL3Eventlist::retrieveExposure()
 */
void SAdata::SAL3Eventlist::retrieveExposure()
{
    setExposure(computeExposure());
}


/*!
    \fn SAdata::SAL3Eventlist::getLightCurve()
 */
SAHistogram* SAdata::SAL3Eventlist::getLightCurve(int detid)
{
//cout.setf(ios::fixed,ios::floatfield);
verbose = true;
 if (verbose) cout << "SAL3Eventlist::getLightCurve started" << endl;

 double tsr = TIME[0];
 double tsp = TIME[dim - 1];

	cout << "SAL3Eventlist::getLightCurve() tstart = " << tsr << endl;
	cout << "SAL3Eventlist::getLightCurve() tstop = " << tsp << endl;

  double w = 1.;
  SampleHistogram sh(tsr, tsp, w);
  //sh = new SampleHistogram(0, 1535, 1);

 k = 0;
if (verbose) cout << "SAL3Eventlist::getLightCurve original eventlist dim = "<< dim << endl;
if (verbose) cout << "SAL3Eventlist::getLightCurve filtered eventlist dimension = "<<  dimension << endl;
 
 while(k< dimension ){
	//cout << "entering "<< double(int(TIME[k])) << endl;
   if ( DETECTOR[k] == detid) sh +=  double(int(TIME[k]));
   //cout << "k = "<< k << "  POS[k] = " <<  POS[k] << endl;
   k++;
 }
 
 string s;stringstream ss;ss.str("");

 int a = sh.buckets();
 
 int *xx = new int[a];
 unsigned long int *yy = new unsigned long int[a];

  k=0;
  while(k< a){
      xx[k] = k;    yy[k] = sh.inBucket(k);
      k++;
  }

  SAPlot splot;
  splot.setDimension(a);
  tempstring = "ASCII"; sp.setPlotType(tempstring);
  tempstring = getProductsDir();  
  cout << "products dir = " << getProductsDir() << endl;
  sp.setPlotSetDir(tempstring);
  s = sp.getPlotSubsetDir(); s+="/";
  s+="lightcurve_";
  ss<<fcntr;
  s+= ss.str();  s+=".dat";

for(int k=0; k<a; k++) splot.setPoint(xx[k], yy[k]);
  // save the data passing the filename
  splot.saveGnuPlot(s);
  tempstring = "LightCurve"; sp.setPlotType(tempstring); 	sp.setTerm(getPlotTerm());
  if (debug) sp.setInteractive(true);
  sp.setData(xx, yy, a);
  sp.setXRange(0, a);
 if (verbose) cout << "il massimo e' " << sh.max() << endl;
  sp.setYRange(0, (long int)sh.max());
  sp.start();
  ss.str("");
  ss << "Light Curve detector " << detid;
  tempstring = ss.str();
  sp.setPlotTitle(tempstring);
  sp.setInteractive(false);
  ss.str("");  ss << "lightcurve_";
  sp.setFilenameBase(ss.str());
  sp.plot();    sp.print(sp.getPlotSubsetDir()); sp.stop();
 if (verbose) cout << "SAL3Eventlist::getLightCurve() ended" << endl;
  delete [] xx;   delete [] yy;
  fcntr++;

	verbose = false;
  return (SAHistogram *)&sh;
}
/*!
    \fn SAdata::SAL3Eventlist::getSpectrum()
 */
SAHistogram* SAdata::SAL3Eventlist::getSpectrum(int detid)
{
verbose = true;
 if (verbose) cout << "SAL3Eventlist::getSpectrum started" << endl;

 double tsr = TIME[0];
 double tsp = TIME[dim - 1];

	cout << "SAL3Eventlist::getSpectrum() tstart = " << tsr << endl;
	cout << "SAL3Eventlist::getSpectrum() tstop = " << tsp << endl;

  double w = 1.;
  SampleHistogram sh(0, 64, w);
  //sh = new SampleHistogram(0, 1535, 1);

 k = 0;
if (verbose) cout << "SAL3Eventlist::getSpectrum() original eventlist dim = "<< dim << endl;
if (verbose) cout << "SAL3Eventlist::getSpectrum() filtered eventlist dimension = "<<  dimension << endl;
 
 while(k< dimension ){
	//cout << "entering "<< double(int(TIME[k])) << endl;
   if ( DETECTOR[k] == detid) sh +=  double(AMPLITUDE[k]);
   //cout << "k = "<< k << "  POS[k] = " <<  POS[k] << endl;
   k++;
 }
 
 string s;stringstream ss;ss.str("");

 int a = sh.buckets();
 
 int *xx = new int[a];
 unsigned long int *yy = new unsigned long int[a];

  k=0;
  while(k< a){
      xx[k] = k;    yy[k] = sh.inBucket(k);
      k++;
  }

  SAPlot splot;
  splot.setDimension(a);
  tempstring = "ASCII"; sp.setPlotType(tempstring);
  tempstring ="."; sp.setPlotSetDir(tempstring);
  s = sp.getPlotSubsetDir(); s+="/";
  s+="spectrum_";
  ss<<fcntr;
  s+= ss.str();  s+=".dat";

for(int k=0; k<a; k++) splot.setPoint(xx[k], yy[k]);
  // save the data passing the filename
  splot.saveGnuPlot(s);
  tempstring = "Spectrum"; sp.setPlotType(tempstring); 	sp.setTerm(getPlotTerm());
  if (debug) sp.setInteractive(true);
  sp.setData(xx, yy, a);
  sp.setXRange(0, a);
 if (verbose) cout << "maximum is " << sh.max() << endl;
  sp.setYRange(0, (long int)sh.max());
  sp.start();
  ss.str("");
  ss << "Spectrum detector " << detid;
  tempstring = ss.str();
  sp.setPlotTitle(tempstring);
  sp.setInteractive(false);
  ss.str("");  ss << "spectrum_";
  sp.setFilenameBase(ss.str());
  sp.plot();    sp.print(sp.getPlotSubsetDir()); sp.stop();
 if (verbose) cout << "SAL3Eventlist::getSpectrum() ended" << endl;
  delete [] xx;   delete [] yy;
  fcntr++;

	verbose = false;
  return (SAHistogram *)&sh;

}

/*
D0 = +Z
D1 = -X
D2 = -Z
D3 = +X
*/
