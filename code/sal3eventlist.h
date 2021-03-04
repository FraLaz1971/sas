/***************************************************************************
                          sal3eventlist.h  -  description
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

#ifndef SAL3EVENTLIST_H
#define SAL3EVENTLIST_H

/// Multi Detector Image definitions

/*
#define NREGVAL     2
#define  NCHANVAL  2
#define  HISTSIZVAL  2
*/

#define NDET     4
#define NREGVAL     10
#define NCHANVAL  1536
#define HISTSIZVAL  1024

///
#include "sadefinitions.h"
#include <string>
#include <CCfits>
#include <Column.h>
#include <FitsError.h>  
#include "saeventlist.h"
#include <map>
#include <HDU.h>
#include <PHDU.h> 
#include <Keyword.h>
#include "sanominalpointing.h"
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "sal3event.h"
#include <fstream>
#include "outputfileexception.h"
#include "sahistogram.h"
#include "saimageplotter.h"
#include "sapointhistosplotter.h"
#include "samdimageplotter.h"
#include "saplot.h"
#include "saplotter.h"
#include "SmplHist.h"
#include "saexception.h"
#include "sagti.h"
#include "archivehandler.h"

/**
  *@author Francesco Lazzarotto
 */




namespace SAdata{

using namespace Graphics;
using namespace SAdata;
using namespace std;


using namespace CCfits;
using std::valarray;
using namespace SAExceptions;

class SAL3Eventlist  : public SAEventlist {
friend class IrosMap;
public: 
	SAL3Eventlist();
  
	SAL3Eventlist(const string &fn);
  
	~SAL3Eventlist();
  /** No descriptions */
  void read(const string &infilename);
  /** No descriptions */
  void readPart(const string &infilename, unsigned long startindex, unsigned long new_nrows);
  
  /** No descriptions */
  void readHeaders(const string &hduname);
  /** No descriptions */
 void passData();
  /** No descriptions */
  void readTableHeader();
  /** No descriptions */
  void readGlobalHeader();
  /** No descriptions */
  void saveMDImage();
  /** No descriptions */
  void setDefault();
  /** No descriptions */
  void plotDetImage(int n);
  /** No descriptions */
  void init();
  /** No descriptions */
  void saveIrosMap();
  /** No descriptions */
  void createMDImage();
  /** No descriptions */
  void createPointHistos();
  /** No descriptions */
  void readIrosMap();
  /** No descriptions */
  void destroyVariables();
  /** No descriptions */
  void createVariables();
  /** No descriptions */
  void setInputFilename(string fn);
  /** No descriptions */
  void getInputDimension(string fn);
  /** No descriptions */
  unsigned long getInputDimension();
  /** No descriptions */
  SAL3Event  getEvent(unsigned long int evnum);
  /** No descriptions */
  void save(const string &outfilename);
  /** No descriptions */
  SAHistogram* getImage(int detid);
  /** No descriptions */
  void getAllDetImages();
  /** No descriptions */
  void getAllLightCurves();
  /** No descriptions */
  void getAllSpectra();
  /** fill the MDImage object */
  void fillMDImage();
  /** prints out the IrosMap data content to an output stream (video, disk file or socket) */
  void printIrosMap(ostream &os);
  /** No descriptions */
  void setIrosMapData();
  /** No descriptions */
  void saveIrosMap(const string &fn);
  /** saves pointing histograms */
  void savePointHistos();
  /** No descriptions */
  void plotPointingHistogram(char axes);
  /** No descriptions */
  SAHistogram* getPointingHistogram(char axes);
  /** No descriptions */
  void plotMDImage();
  /** No descriptions */
  void setDebug(bool bval);
  /** No descriptions */
  void fixProdSetDir();
  /** No descriptions */
  void createProdSetDir();
  /** No descriptions */
  void setInteractive(bool bval);
  /** No descriptions */
  void printPointingHistogram(char axes);
  /** No descriptions */
  void createDefaults();
  /** No descriptions */
  void setImageType(int imt);
  /** No descriptions */
  void printMDImageMessage(int a, int b, int c);
  /** No descriptions */
  void setFCounter(int fc);
  /** No descriptions */
  void plotTotMDImage();
  /** No descriptions */
  /** Used to create Iros Map separately --- at 19/03/2007 implement the correct version*/
  void saveIrosMap3(const string &fn);
  /** No descriptions */
  void savePart(const string &ofnam, long int dime);
  /** No descriptions */
  void readDebug(string &fn);
  /** No descriptions */
    void readDebug2(string &fn);
  /** No descriptions */
  //SAL3Eventlist * filterEnergy(unsigned short en_min, unsigned short en_max);
  /** No descriptions */
  void setEvent(unsigned long int num, SAL3Event * event);

  void update();

  void readGTI(const string &gtifn);

  void readSagaGTI(const string &gtifn);

  void readExposureGTI(const string &gtifn);

  /** */
  	void printerror( int status);
    void createPointHistos2();
    void filterTime(double timemin, double timemax);
    void filterEnergy(float emin, float emax);
    void filterAllGTI(const string &gtifname);
    void saveFiltered(const string &outfilename);
	void filterDetector(unsigned char detmin, unsigned char detmax);

    void filterAllDetectors();
    void clearTempVectors();
    void clearDataVectors();
    void setFilteredListName(const string &n, int num);
    void resetTime(double tzero);
    void effect();
    void filterGTIFile(const string &gtifname);
	void setArchiveHandler(ArchiveHandler *ah);
    bool isSaveFiltered();
    void setSaveFiltered(bool val);
    double computeExposure();
    void setExposure(double ex);
    double getExposure();
    void retrieveExposure();
	void setProdSetDir(const string &run_n);
    SAHistogram* getLightCurve(int detid);
    SAHistogram* getSpectrum(int detid);

public:

SAL3Event   ev, ev2;
SANominalPointing sapoint;
private:        
SAL3Eventlist * outlist;
vector<SAL3Event> list;
vector<long int> COUNT;
vector<long int> PHOTON_ID;
vector<double> TIME;
vector<float> AMPLITUDE;
vector<short int> POS;
vector<unsigned char> DETECTOR;
vector<float> POS_SHIFT;
vector<unsigned char> SSID; //Number: 8   unit:format: B comment:
unsigned long int  dimension;
unsigned long int  newdimension;

// temp vectors for filtering
	vector<long int> myCOUNT;	vector<long int> myPHOTON_ID;	vector<double> myTIME;
	vector<float> myAMPLITUDE;	vector<short int> myPOS;	vector<unsigned char> myDETECTOR;
	vector<float> myPOS_SHIFT;	vector<unsigned char> mySSID;


/** data for the IrosMap object */
    string _starts;   // field 1
     int  _i_fn_length_0;  // field 2
     int  _i_fn_length_1;  // field 2
    string      _cfin_out; // field 3
     int  _i_fn_length_2; // field 4
    string      _cfin_p; // field 5
    short int _Nchan; // field 6
    float  _Tburst;  // field 7
    float _EnMin; // field 8
    float _EnMax;  // field 9
    short int _N_regions;  // field 10
    float _max_angle;  // field 11
    float _f_length;   // field 12
    float _delta_norm;  // field 13
    float _s_width;  // field 14
    short int _Hist_Size;
    short int  _D_Seq[4]; // field 15
    float _C_Angles[NREGVAL]; // field 16
    float _C_Coeffs[NREGVAL];  // field 17
    short int _C_Shifts[NREGVAL];  // field 18
    short int _C_Coords[NREGVAL];  // field 19
    float _Point_Hist_x[HISTSIZVAL];  // field 20
    float _Point_Hist_z[HISTSIZVAL];  // field 21
    short int _C_Index[NREGVAL]; // field 22
    long int _MDImage[NREGVAL][4][NCHANVAL]; // field 23  

/**
  ####   GLOBAL DATA !  ####
 */
    float C_Angles[NREGVAL]; // field 16
    float C_Coeffs[NREGVAL];  // field 17
map<string, string> metainfo;
map<string, string>::iterator cur;
Keyword *key;
vector<string> keynames;
string mdimagenam;
vector<SAL3Event> l3v; /// REMEMBER TO TEST
/// variables used for irosmap data generation
   int unit, status;
   int eof, err, itime, iunitlog;
   
   double time_s, time_step, Duration, Samp1, att_m_t[3][3];
//   string inputfilename;
   char strbuff[12], strbuff2[512];
   short int one;
   /** n. of (angular) sky regions */
   short int N_regions;
   /** number of strip (detector sensitive units -- pixels--) */ 
   short int Nchan;
   /** size of the histogram */
   short int Hist_Size;
   /** mapping values for detector numbers*/
   short int  D_Seq[4];
   /** */
   short int iside;
   /** */
//   float C_Angles[NREGVAL];
   /** */
//   float C_Coeffs[NREGVAL];
   /** */
//   short int C_Shifts[NREGVAL];
   /** */
//   short int C_Coords[NREGVAL];   
   /** pointing histograms in  x*/
//   float Point_Hist_x[HISTSIZVAL];
////   /** pointing histograms in  z*/
//   float Point_Hist_z[HISTSIZVAL];
   float gPoint_Hist_x[HISTSIZVAL];
//   /** pointing histograms in  z*/
   float gPoint_Hist_z[HISTSIZVAL];
   /** pointing histograms in  x*/
   float Point_HistBis_x[HISTSIZVAL];
   /** pointing histograms in  z*/
   float Point_HistBis_z[HISTSIZVAL];
   /** index of the sky regions*/
   short int C_Index[NREGVAL];
   /**The Multi Detector image value  */
   int MDImage[NREGVAL][NDET][NCHANVAL];   
   /** pigreco constant */
   double PI ;
   /** */
   float Tburst;
   /** */
   float Hist_Theta[HISTSIZVAL];
   /** */
   int l;
   /** */
   int i_fn_length_0;
   /** */
   int i_fn_length_1;
   /** */
   int i_fn_length_2;
   /** */
   OutputFileException e;
   /** */
    int w;
   /** */
    int x;
   /** */
    int y;
   /** */
    int z;
   /** */
    bool cond1;
   /** */
    bool cond2;
   /** */
    bool cond3;

     /** */
    float max_angle;

     /** */

    float f_length;

     /** */
    float s_width ;

     /** */
     float delta_norm;

     /** */
     float EnMin;

     /** */
     float EnMax;
     /** */
     string definfile;

     /** */
     /** */
     SampleHistogram *s;
     /** */
     SampleHistogram *shx;

     /** */
     SampleHistogram *shz;

     /** */
     SampleHistogram *sh0;
     
     /** */
     SampleHistogram *sh1;

     /** */
     SampleHistogram *sh2;

     /** */
     SampleHistogram *sh3;

     /**Plots detector Images  */
     SAImagePlotter sp;

     /** Plots the pointing histograms  */
     SAPointHistosPlotter phplot;

     SAMDImagePlotter mdp;                        
     /** */
     int fcntr;
     /** */
     fitsfile * in ;

      /** */
     FITS *pInfile;
     
      vector<int> xx_xg;
      /** */
      vector<unsigned long int> yy_xg;

      /** */
      vector<int> xx_zg;
      /** */
      vector<unsigned long int> yy_zg;
      
     /** */
     int *xp; unsigned long int *yp;
     /** */
     SAPlot *splot; 
     /** */
     SAPlot * images;
     /** */
    bool debug;
     /** */
    bool isfixpsd; 
     /** */
    SAexception se;

     /** */
	double exposure;

	vector<long int>::iterator count_lit;vector<long int>::iterator pid_lit;vector<double>::iterator time_dit; 
	vector<float>::iterator ampli_fit; vector<short int>::iterator pos_sit; vector<unsigned char>::iterator det_ucit;
 	vector<float>::iterator posh_fit; vector<unsigned char>::iterator ss_ucit;
	vector<string> filt_list_name;

	string filtertarget;

//     /** *///      int *xx; //      unsigned long int *yy;
//      //     IrosMap im;//    MDImage mdimage;
     public:

};

}
#endif



 /*
typedef struct {
        long int COUNT[MAXDIMENSION];
        long int PHOTON_ID[MAXDIMENSION];
        long long int TIME[MAXDIMENSION];
        float AMPLITUDE[MAXDIMENSION];
        short int POS[MAXDIMENSION];
        unsigned char DETECTOR[MAXDIMENSION];
        float POS_SHIFT[MAXDIMENSION];
        unsigned char SSID[MAXDIMENSION]; //Number: 8   unit:format: B comment:
        unsigned long int  dimension;
  }  l3eventlist_;

typedef struct {
        vector<long int> COUNT;
        vector<long int> PHOTON_ID;
        vector<long long int> TIME;
        vector<float> AMPLITUDE;
        vector<short int> POS;
        vector<unsigned char> DETECTOR;
        vector<float> POS_SHIFT;
        vector<unsigned char> SSID; //Number: 8   unit:format: B comment:
        unsigned long int  dimension;
  }  l3eventlist_;

*/
