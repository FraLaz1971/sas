/***************************************************************************
                          irosmap.h  -  description
                             -------------------
    begin                : Tue Aug 1 2006
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

#ifndef IROSMAP_H
#define IROSMAP_H

#define NREGVAL     10
#define  NCHANVAL  1536
#define  HISTSIZVAL  1024

#include "sadataset.h"
#include "sal3eventlist.h"
#include "saimageset.h"
#include <iostream>
#include <fstream>                                     
#include <math.h>
/**
  *@author Francesco Lazzarotto
  */

namespace SAdata{
  using namespace SAdata;
  using namespace std;
  using namespace CCfits;
  using std::valarray;
  using namespace SAExceptions;

class IrosMap : public SADataSet  {
friend class SAL3Eventlist;
public: 

  IrosMap();
  IrosMap(const SAL3Eventlist &l3ref);

  ~IrosMap();
  /** No descriptions */
  void setDetOrder();
  /** No descriptions */
  void init();
  /** No descriptions */
  void saveBinary(const string &fn);
  /** No descriptions */
  void initHistograms();
  /** No descriptions */
  void initStrings();
  /** No descriptions */
  void setHistogramsDefault();
  /** No descriptions */
  void setParameters();
  /** No descriptions */
  void setPointingHistograms();
  /** No descriptions */
  void setL3Eventlist(const SAL3Eventlist &l3ref);
  /** No descriptions */
  void unpack();
  /** No descriptions */
  void show(ostream &os);
  /** load IrosMap data reading a binary file named fn */
  void loadBinary(const string &infile);
  /** No descriptions */
  void getL3EvlistData();
  /** No descriptions */
  void saveL3IMBinary();
  /** get the image set for a selected sky image */
  SAdata::SAImageSet getImageSet(int regnum);

private:
  
/** data for the IrosMap object */

    string starts;   // field 1
    
    int  i_fn_length_1;  // field 2

    string      cfin_out; // field 3

    int  i_fn_length_2; // field 4

    string      cfin_p; // field 5

    short int Nchan; // field 6

    float  Tburst;  // field 7

    float EnMin; // field 8

    float EnMax;  // field 9

    short int N_regions;  // field 10

    float max_angle;  // field 11

    float f_length;   // field 12

    float delta_norm;  // field 13

    float s_width;  // field 14

    short int Hist_Size;

    short int  D_Seq[4]; // field 15

    float C_Angles[NREGVAL]; // field 16

    float C_Coeffs[NREGVAL];  // field 17

    short int C_Shifts[NREGVAL];  // field 18

    short int C_Coords[NREGVAL];  // field 19

    float Point_Hist_x[HISTSIZVAL];  // field 20

    float Point_Hist_z[HISTSIZVAL];  // field 21

    short int C_Index[NREGVAL]; // field 22

    long int MDImage[NREGVAL][4][NCHANVAL]; // field 23

    /** */
    int iside;

    /** */
    int dimss;

    /** */
    string ss;

protected:

   /** */
   float Hist_Theta;
   /** */
   int l;
   /** */
   int i_fn_length_0;
   /** */


   double PI ;

  SAL3Eventlist l3;   

  int k;

   SAImageSet is;
};
}
#endif
//
//          /** */
//    float max_angle;
//
//     /** */
//
//    float f_length;
//
//     /** */
//    float s_width ;
//
//     /** */
//     float delta_norm;
//
//     /** */
//    float EnMin;
//
//     /** */
//    float EnMax;
//
//
//     /** */
//
//     /** */
//    char *starts; //= new char[55];
//     /** */
//    char *cfin_out; //= new char[64];
//     /** */
//    char *cfin_p; //= new char[64];
//
//
//          string fin_out; // name of the file
//          string fin_p;
//
/////  pointing histogram creation
//float Psi_s_z;
//float Psi_s_x;
//   double time_s, time_step, Duration, Samp1, att_m_t[3][3];
////   string inputfilename;
//   char strbuff[12], strbuff2[512];
//
//   short int one;
//   /** n. of (angular) sky regions */
//   short int N_regions;
//   /** number of strip (detector sensitive units -- pixels--) */
//   short int Nchan;
//   /** size of the histogram */
//   short int Hist_Size;
//   /** mapping values for detector numbers*/
//   short int  D_Seq[4];
//   /** */
//   short int iside;
//   /** */
//   float *C_Angles;
//   /** */
//   float *C_Coeffs;
//   /** */
//   int C_Shifts[NREGVAL];
//   /** */
//   int C_Coords[NREGVAL];
//   /** pointing histograms in  z*/
//   float *Point_Hist_x;
//   /** pointing histograms in  z*/
//   float *Point_Hist_z;
//   /** index of the sky regions*/
//   short int C_Index[NREGVAL];
//   /**The Multi Detector image value  */
//   long int MDImage[NREGVAL][4][NCHANVAL];
//   /** pigreco constant */
//   /** */
//   float Tburst;