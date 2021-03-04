/***************************************************************************
                          irosmap.cpp  -  description
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

#include "irosmap.h"

namespace SAdata{
IrosMap::IrosMap(){
    k=0;
    i_fn_length_0 = 55;
}
IrosMap::IrosMap(const SAL3Eventlist  &l3ref){
  l3 = l3ref;
}
IrosMap::~IrosMap(){
}
}/** No descriptions */
void SAdata::IrosMap::saveBinary(const string &fn){

  char *starts3;
  char *cfin_out3;
  char *cfin_p3;
    try{
      starts3 = new char[55]; // initial string
      cfin_out3 = new char[64];  // contains fin_out variable
      cfin_p3 = new char[64];  // contains fin_p variable
  } catch (const exception &e){
      cout <<"caught exception "<< e.what() << endl;
  }

  starts3 = (char *)starts.c_str();
  cfin_out3 = (char *)cfin_out.c_str();
  cfin_p3 = (char *)cfin_p.c_str();

  cout <<  "executing IrosMap::saveBinary()" << endl;
    //N_regions = 10;

      verbose = true;
      stringstream ss; string s("im_sb_log_");
      ss.str("");
      ss <<  s << k++ << ".txt";

      ofstream of;
      try{
        of.open(ss.str().c_str(), ofstream::out | ofstream::trunc);
    } catch (const exception &e){
       cerr << "caught exception " << e.what() << endl;
    }
 

          of << endl;
          of << "N_regions = "<< N_regions << endl;
          of << "N of det = "<< 4 << endl;
          of << "Nchan = "<< Nchan << endl;


          of << "size of  Nchan "<< sizeof(short int) << endl;
          of << "size of  Hist_Size "<< sizeof(short int) << endl;
          string f; f = "../stg_2/"+fn;
          try {
                // open file and
                fstream binary_file(f.c_str(),ios::out|ios::binary|ios::trunc);
//                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                binary_file.write(reinterpret_cast<char *>(starts3), i_fn_length_0);
                if (verbose) of << "written startstring = "<< starts3 << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
                if (verbose) of << "written i_fn_length_1 = "<< i_fn_length_1 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_out3), i_fn_length_1);
                if (verbose) of << "written cfin_out = "<<  cfin_out3 << endl;
                binary_file.write(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
                if (verbose) of << "written i_fn_length_2 = "<< i_fn_length_2 << endl;
                binary_file.write(reinterpret_cast<char *>(cfin_p3), i_fn_length_2);
                if (verbose) of << "written cfin_p = "<< cfin_p3 << endl;
                binary_file.write(reinterpret_cast<char *>(&Nchan), sizeof(short int));
                if (verbose) of << "written Nchan = "<< Nchan << endl;
                binary_file.write(reinterpret_cast<char *>(&Tburst), sizeof(float));
                if (verbose) of << "written Tburst = "<< Tburst << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMin),sizeof(float));
               if(verbose) of<<"written EnMin: "<< EnMin << endl;
                binary_file.write(reinterpret_cast<char *>(&EnMax),sizeof(float));
               if(verbose) of<<"written EnMax: "<< EnMax << endl;
                binary_file.write(reinterpret_cast<char *>(&N_regions),sizeof(short int));
               if(verbose) of<<"written N_regions: "<< N_regions << endl;
                binary_file.write(reinterpret_cast<char *>(&max_angle),sizeof(float));
                if(verbose) of<<"written max_angle: "<< max_angle << endl;
                binary_file.write(reinterpret_cast<char *>(&f_length),sizeof(float));
               if(verbose) of<<"written f_length: "<< f_length << endl;
                binary_file.write(reinterpret_cast<char *>(&s_width),sizeof(float));
                if(verbose)   of<<"write s_width: "<<  s_width << endl;
                binary_file.write(reinterpret_cast<char *>(&delta_norm),sizeof(float));
                if(verbose) of<<"written delta_norm: "<< delta_norm << endl;

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Angles[w]),sizeof(float));
                  if(verbose) of<<"written C_Angles, element  "<< w << " value "<< C_Angles[w] << endl;
              }

              for(w=0; w<N_regions; w++){
                  binary_file.write(reinterpret_cast<char *>(&C_Coeffs[w]),sizeof(float));
                  if(verbose) of<<"written C_Coeffs, element  "<< w << " value "<< C_Coeffs[w] << endl;
              }


              binary_file.write(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));
              if(verbose) of<<"written Hist_Size  "<< w << " value "<< Hist_Size << endl;


              for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_x[w]),sizeof(float));
                if(verbose) of<<"written Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;
             }

            for(w=0; w<Hist_Size; w++){
                binary_file.write(reinterpret_cast<char *>(&Point_Hist_z[w]),sizeof(float));
                if(verbose) of<<"written Point_Hist_z, element  "<< w << " value " << Point_Hist_z[w] << endl;
            }

            for(w=0; w<4; w++){ // write detector index
              binary_file.write(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
              of << "written D_Seq[w] = " << D_Seq[w] << endl;
            }

            of << "SAL3Eventlist::saveIrosMap() going to write the MultiDetectorImage"<< endl;
            /// REMEMBER TO CHANGE !
            /// AND USE DEFAULT VALUES!


            if(verbose) of << "For "<< N_regions << " regions " << endl;
            for (w=0; w<4; w++) of << "For detector n. "<<  D_Seq[w] <<  " and then "<< endl;
            int count = 0;
            for(x=0; x<N_regions; x++){ // loop on the sky regions
            if(verbose) of << "####  data for the sky region "<< C_Index[x]  << endl;

            binary_file.write(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int)); /// write the region index
            if(verbose) of << " written  index region "<< C_Index[x]   << endl;

                 of << endl;
                if(verbose)of<<"    writing MDImage,  detector code = "<< D_Seq[0]  << " det   = "<< 0  <<  endl;
                 of << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(long int));
                    if(verbose) of<<"        writing MDImage, region "<< C_Index[x] << " detector code"<< D_Seq[0] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[0]][w]<< endl;
                 }
                 of << endl;
                if(verbose)of<<"    completed MDImage,  detector code"<< D_Seq[0]  << " det  "<< 0  <<  endl;
                 of << endl;

                 of << endl;
                if(verbose)of<<"    writing MDImage,  detector code = "<< D_Seq[1]  << " det   = "<< 1  <<  endl;
                 of << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(long int));
                    if(verbose) of<<"        writing MDImage, region "<< C_Index[x] << " detector "<< D_Seq[1] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                 }
                 of << endl;
                if(verbose)of<<"completed MDImage,  detector code = "<< D_Seq[1]  << " det =  "<< 1  << endl;
                 of << endl;

                 of << endl;
                if(verbose)of<<"    writing MDImage,  detector code"<< D_Seq[2]  << " det  "<< 2  <<  endl;
                 of << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(long int));
                    if(verbose) of<<"        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[2] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                 }
                 of << endl;
                if(verbose)of<<"completed MDImage,  detector code = "<< D_Seq[2] << " det  = "<< 2 << endl;
                 of << endl;

                 of << endl;
                if(verbose)of<<"    writing MDImage,  detector code = "<< D_Seq[3]  << " det  = "<< 3  <<  endl;
                 of << endl;
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(long int));
                    if(verbose) of << "        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[3] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                 }

                 of << endl;
                if(verbose)of<<"completed MDImage,  detector code = "<< D_Seq[3] << " det  = "<< 3 << endl;
                 of << endl;

                 of << endl;
                 of << endl;
                if(verbose)of << "#### completed data for the sky region index: "<<  x << endl;
                 of << endl;
                 of << endl;

//               if(verbose)of << "written mdimage array region n. "<< count++<< endl;
            }// end of the loop on the sky regions

                if(verbose) of << "written all data" << endl;
                binary_file.close();
       }
          catch (exception e){
          // will catch  exceptions
          // found by
            std::cerr << "exception during IrosMap::saveBinary() function " << e.what() << endl;
//            e.handle();

          }

//
  of.close();
  cout << " IrosMap::saveBinary() ended!"<< endl;
  verbose = false;

}
/** No descriptions */
void SAdata::IrosMap::init(){
//    N_regions =  NREGVAL;
//    Hist_Size = HISTSIZVAL;
//    Nchan = NCHANVAL;
//    setDetOrder();
//    initHistograms();
//    initStrings();
//setParameters();
}
/** No descriptions */
void SAdata::IrosMap::setDetOrder(){
          D_Seq[0] = 2;
          D_Seq[1] = 3;
          D_Seq[2] = 0;
          D_Seq[3] = 1;
}
/** No descriptions */
void SAdata::IrosMap::initHistograms(){

}
/** No descriptions */
void SAdata::IrosMap::initStrings(){
          ss = "SA_MAP_V4.0_BIN_POINTING_FROM_FLIST_TO_MAP_POINTING.FOR";
          starts = ss.c_str();
          i_fn_length_0 = strlen(starts.c_str());
          cfin_out = "pippo1";
          cfin_p = "plutone2";
          i_fn_length_1 = strlen(cfin_out.c_str());
          i_fn_length_2  = strlen(cfin_p.c_str());
}
/** No descriptions */
void SAdata::IrosMap::setParameters(){
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

//     C_Shifts =  (short int *) new C_Shifts[NREGVAL];
//   /** */
//     C_Coords =  (short int *) new C_Coords[NREGVAL];

     for(w=0; w<N_regions; w++) C_Index[w] = (short int)w;

}
/** No descriptions */
void SAdata::IrosMap::setHistogramsDefault(){
     for(w=0; w<N_regions; w++){
	   C_Angles[w] = max_angle/N_regions*(2.*w-1.)/2.;
	   C_Coeffs[w] = delta_norm*(tan(C_Angles[w]*PI/180.)-tan((C_Angles[w]-1.)*PI/180.));
	   C_Coeffs[w] = C_Coeffs[w]*1.00/0.93;
     }
}
/** No descriptions */
void SAdata::IrosMap::setPointingHistograms(){
  float Psi_s_z;
  float Psi_s_x;

/// loop on all the events of the eventlist
    if (verbose) cout << "loop on all the events of the eventlist" << endl;

  unsigned long int c = 0;

/// ###### REMEMBER TO CHANGE
l3.setDim(10);
/// ###### REMEMBER TO CHANGE

while (c<l3.getDim()){

    l3.ev = l3.getEvent(c); /// get the temp event

 // verbose = true;

   if (verbose) {
     if (verbose) cout << "events  n " << c << endl;
     l3.ev.show();
   }
    iside 	= 0;

    if (l3.ev.getPos() > 767) {
	     iside = 1;
          //	   l3.ev.setPos() = l3.ev.getPos() - 768;
          l3.ev.setPos(l3.ev.getPos() - 768);
	  }

        switch(l3.ev.getDetector()){
          case 0:
          Psi_s_x = l3.ev.getPosShift();

          i=0;
		  while(i<N_regions){
		    C_Shifts[i] = (short int) -1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
		  }
      
		  Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]	= Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[0])]+1.;
          break;
          case 1:
          Psi_s_z = l3.ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = (short int)+1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]	= Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 2:
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] = (short int)+1.*(Psi_s_z)/ PI*180.*C_Coeffs[i];
            i++;
          }
		Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])] = Point_Hist_z[(int)(511+(Psi_s_z)/PI*180.*C_Coeffs[1])]+1.;
          break;
          case 3:
          Psi_s_x = l3.ev.getPosShift();
          i=0;
		  while(i<N_regions){
		   C_Shifts[i] =(short int) -1.*(Psi_s_x)/ PI*180.*C_Coeffs[i];
            i++;
          }
		  Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])] = Point_Hist_x[(int)(511+(Psi_s_x)/PI*180.*C_Coeffs[1])]+1.;
          break;
          default:    /// INSERT AN EXCEPTION
            cout << "wrong detector number !!!" << endl;
          break;
        }

        for(w=0; w<N_regions; w++){
              C_Coords[C_Index[i]] = C_Shifts[C_Index[i]] + l3.ev.getPos();
              C_Coords[w] = C_Shifts[w] + l3.ev.getPos();            
        }

        for(w=0; w<N_regions; w++){ // loop on the sky region
        cond1 = (C_Coords[C_Index[w]] > 0);
        cond2 = (C_Coords[C_Index[w]] < 767);
//        cond3 = (ev.getAmplitude()  >= EnMin) && (ev.getAmplitude()  <=  EnMax);
        if (cond1 && cond2) {
//	          if (cond3) {
		          MDImage[C_Index[w]] [l3.ev.getDetector()][1+C_Coords[C_Index[w]]+iside*768] =  MDImage[C_Index[w]][l3.ev.getDetector()][1+C_Coords[C_Index[w]]+iside*768]+1;
//	          }
	        }
         }
  c++;
}

}
/** No descriptions */
void SAdata::IrosMap::setL3Eventlist(const SAL3Eventlist &l3ref){
  l3 =l3ref;
}
/** No descriptions */
void SAdata::IrosMap::unpack(){
  show(cout);
}
/** No descriptions */
void SAdata::IrosMap::show(ostream &os){
  try{
        os << "starts " << starts << endl;
        
        os << " i_fn_length_1 = " << i_fn_length_1<< endl;
        
        os << " cfin_out  = " <<  cfin_out << endl;
        
        os << " i_fn_length_2 = " <<  i_fn_length_2 << endl;
        
        os << " cfin_p = " <<  cfin_p << endl;
        
        os << " Nchan = " <<  Nchan << endl;
        
        os << " Tburst = " <<  Tburst << endl;
        
        os << " EnMin  = " <<  EnMin  << endl;
        
        os << " EnMax = " <<  EnMax << endl;
        
        os << " N_regions = " <<  N_regions << endl;
        
        os << " max_angle = " <<  max_angle << endl;
        
        os << " f_length = " <<  f_length << endl;
        
        os << " delta_norm = " <<  delta_norm << endl;
        
  for(w=0; w<N_regions; w++){
        os<<"C_Angles, element  "<< w << " value "<<  C_Angles[w] << endl;
  }
  for(w=0; w< N_regions; w++){
        os<<"   C_Coeffs, element  "<< w << " value "<<  C_Coeffs[w] << endl;
  }
        os << " delta_norm = " <<  delta_norm << endl;

        os << " Hist_Size = " <<  Hist_Size << endl;
  for(w=0; w< Hist_Size; w++){
        os<<"   Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;
  }
  for(w=0; w< Hist_Size; w++){
        os<<"   Point_Hist_z, element  "<< w << " value "<<  Point_Hist_z[w] << endl;
  }
  for(w=0; w<4; w++){ // write detector index
              os << "written D_Seq[w] = " <<  D_Seq[w] << endl;
  }

   for(x=0; x< N_regions; x++){ // loop on the sky regions
        os << "####  data for the sky region "<<  C_Index[x]  << endl;
                        for(w=0; w< Nchan; w++){ // loop on the strips
                             os<<" writing MDImage, region "<<  C_Index[x] << " detector code "<< D_Seq[0] << " element " << w << " value "<< MDImage[ C_Index[x]][ D_Seq[0]][w]<< endl;
                        } // end of the loop on the strips
                        for(w=0; w< Nchan; w++){ // loop on the strips
                             os<<" writing MDImage, region "<<  C_Index[x] << " detector code "<< D_Seq[1] << " element " << w << " value "<< MDImage[ C_Index[x]][ D_Seq[1]][w]<< endl;
                        } // end of the loop on the strips
                        for(w=0; w< Nchan; w++){ // loop on the strips
                             os<<" writing MDImage, region "<<  C_Index[x] << " detector code "<< D_Seq[2] << " element " << w << " value "<< MDImage[ C_Index[x]][ D_Seq[2]][w]<< endl;
                        } // end of the loop on the strips
                        for(w=0; w< Nchan; w++){ // loop on the strips
                             os<<" writing MDImage, region "<<  C_Index[x] << " detector code "<< D_Seq[3] << " element " << w << " value "<< MDImage[ C_Index[x]][ D_Seq[3]][w]<< endl;
                        } // end of the loop on the strips
                        os << endl;
                        os << endl;
                        os << "#### completed data for the sky region index: "<<  x << endl;
                        os << endl;
                        os << endl;

   }// end of the loop on the sky regions

 //                if(verbose) cout<<"written Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;

 /*
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  os << "l3. " << l3. << endl;
  */

  } catch(const exception& e) {
     cerr << "thrown exceptions "<< e.what() << endl;
  }

}
/** load IrosMap data reading a binary file named fn */
void SAdata::IrosMap::loadBinary(const string &infile){
//#define NREGVAL     10
//#define  NCHANVAL  1536
//#define  HISTSIZVAL  1024

  char *starts2;
  char *cfin_out2;
  char *cfin_p2;
  tm.start();
  try{
      starts2 = new char[55]; // initial string
      cfin_out2 = new char[64];  // contains fin_out variable
      cfin_p2 = new char[64];  // contains fin_p variable
  } catch (const exception &e){
      cout <<"caught exception "<< e.what() << endl;
  }
/*  
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

  float *C_Angles2 = new float[NREGVAL];
  float *C_Coeffs2 = new float[NREGVAL];
  float *Point_Hist_x2 = new float[HISTSIZVAL];
  float *Point_Hist_z2 = new float[HISTSIZVAL];    */
//  cout << "Hist_Size = " << Hist_Size << endl;
            string s;
            stringstream ss;
try
{
     cout << "going to open " << infile << endl;
    ifstream binary_file(infile.c_str(), ios::in | ios::binary);
    cout << "####################################" << endl;
    cout << "#   IrosMap::loadBinary    READ DATA    " << endl;
    cout << "####################################" << endl;

  if (binary_file.is_open())
  {
            //binary_file.read(reinterpret_cast<char *>(starts ),55);
            binary_file.read(starts2 ,55);
            if (!binary_file) {
              /// if error occurred
              cerr << "error in reding the file :" << endl;
              cerr << "read " << binary_file.gcount()  << "bytes "<< endl;
              binary_file.clear();
            }
 verbose = true;
            if(verbose) cout<<"read startstring: "<< starts2  << endl;
           binary_file.read(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
            if(verbose) cout<<"read i_fn_length_1: "<< i_fn_length_1 << endl;
            binary_file.read(reinterpret_cast<char *>(cfin_out2),i_fn_length_1);
            if(verbose) cout<<"read fin_out: "<< cfin_out  << endl;
            binary_file.read(reinterpret_cast<char *>(&i_fn_length_2 ), sizeof(int));
            if(verbose) cout<<"read i_fn_length_ : "<< i_fn_length_2  << endl;
            binary_file.read(reinterpret_cast<char *>(cfin_p2 ),i_fn_length_2 );
            if(verbose) cout<<"read fin_p: "<< cfin_p  << endl;
           binary_file.read(reinterpret_cast<char *>(&Nchan ),sizeof(short int));
            cout<<"read Nchan: "<< Nchan  << endl;
            binary_file.read(reinterpret_cast<char *>(&Tburst ),sizeof(float));
            if(verbose) cout<<"read Tburst: "<< Tburst  << endl;
            binary_file.read(reinterpret_cast<char *>(&EnMin ),sizeof(float));
            if(verbose) cout<<"read EnMin: "<< EnMin  << endl;
            binary_file.read(reinterpret_cast<char *>(&EnMax ),sizeof(float));
            if(verbose) cout<<"read EnMax: "<< EnMax  << endl;
            binary_file.read(reinterpret_cast<char *>(&N_regions ),sizeof(short int));
            cout<<"read N_regions: "<< N_regions  << endl;
            binary_file.read(reinterpret_cast<char *>(&max_angle ),sizeof(float));
            if(verbose) cout<<"read maxangle: "<< max_angle  << endl;
            binary_file.read(reinterpret_cast<char *>(&f_length ),sizeof(float));
            if(verbose) cout<<"read f_length: "<< f_length  << endl;
            binary_file.read(reinterpret_cast<char *>(&s_width ),sizeof(float));
            if(verbose) cout<<"read s_width: "<<  s_width << endl;
           verbose = false;
            binary_file.read(reinterpret_cast<char *>(&delta_norm ),sizeof(float));
            if(verbose) cout<<"read delta_norm: "<< delta_norm  << endl;
            for(w=0; w<N_regions ; w++){
              binary_file.read(reinterpret_cast<char *>(&C_Angles [w]),sizeof(float));
              if(verbose) cout<<"read C_Angles, element  "<< w << " value = " << C_Angles [w] << endl;
            }
            for(w=0; w<N_regions ; w++){
             binary_file.read(reinterpret_cast<char *>(&C_Coeffs [w]),sizeof(float));
              if(verbose) cout<<"read C_Coeffs, element  "<< w << " value = "<< C_Coeffs [w] << endl;
 }
            binary_file.read(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));
            if(verbose) cout<<"read Hist_Size "<< w << " value = "<< Hist_Size << endl;

            for(w=0; w<Hist_Size; w++){
              binary_file.read(reinterpret_cast<char *>(&Point_Hist_x[w]),sizeof(float));
              if(verbose) cout<<"read Point_Hist_x, element  "<< w << " value = "<< Point_Hist_x[w] << endl;
            }

            for(w=0; w<Hist_Size; w++){
              binary_file.read(reinterpret_cast<char *>(&Point_Hist_z[w]),sizeof(float));
              if(verbose) cout<<"read Point_Hist_z, element  "<< w << " value = "<< Point_Hist_z[w] << endl;
            }

            for(w=0; w<4; w++){ // read detector index
              binary_file.read(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
               cout << "D_Seq[w] = "   << D_Seq[w] << endl;
            }
              verbose = false;

            cout << "going to read data for regions  # "   << N_regions  << endl;
            cout << "going to read data and channels  # "   << Nchan  << endl;


            for(x=0; x<N_regions ; x++){ // loop on the sky regions
                binary_file.read(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int));
                cout << "data for the sky region " << C_Index[x] << endl;

                 /// detector 0
                for(w=0; w<Nchan ; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[0] << " value = " << MDImage[C_Index[x]][D_Seq[0]][w] << endl;
                }// end of the loop on the strips

                 /// detector 1
                for(w=0; w<Nchan ; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[1] << " value = " << MDImage[C_Index[x]][D_Seq[1]][w] << endl;
                }// end of the loop on the strips


                 /// detector  
                for(w=0; w<Nchan; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << " D_Seq = "  << D_Seq[2] << " value = " << MDImage[C_Index[x]][D_Seq[2]][w] << endl;
                }// end of the loop on the strips


                 /// detector 3
                for(w=0; w<Nchan ; w++){ // loop on the strips
                    binary_file.read(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(long int ));
                    if(verbose) cout<<"read MDImage, element  "<< w << " sky region "<< C_Index[x] << "D_Seq = " << D_Seq[3] << " value = " << MDImage[C_Index[x]][D_Seq[3]][w] << endl;
                }// end of the loop on the strips

             }// end of the loop on the sky regions

            binary_file.close();
}
  else cout << "Unable to open file" << endl;;

  }        catch (exception e){
    cerr << "exception during binary file reading"<< endl;
}
    cout << "######################################" << endl;
    cout << "#   IrosMap::loadBinary       END   DATA    " << endl;
    cout << "######################################" << endl;

    cout  << endl;

  tm.stop();
  tm.report();

  starts = starts2;
  cfin_out = cfin_out2;
  cfin_p = cfin_p2;
  //  verbose = false;

}

/** get the image set for a selected sky image */
SAdata::SAImageSet SAdata::IrosMap::getImageSet(int regnum){
  return is;
}

/** No descriptions */
void SAdata::IrosMap::getL3EvlistData(){

      i_fn_length_0 = l3._i_fn_length_0;

      starts = l3._starts;   // field 1

      i_fn_length_1 = l3._i_fn_length_1;  // field 2

      cfin_out = l3._cfin_out; // field 3

      i_fn_length_2 = l3._i_fn_length_2; // field 4

      cfin_p = l3._cfin_p; // field 5

      Nchan = l3._Nchan; // field 6

      Tburst = l3._Tburst;  // field 7

      EnMin = l3._EnMin; // field 8

      EnMax = l3._EnMax;  // field 9

      N_regions = l3._N_regions;  // field 10

      cout << "getL3EvlistData() N_regions = " << N_regions << endl;
      
      max_angle = l3._max_angle;  // field 11

      f_length = l3._f_length;   // field 12

      delta_norm = l3._delta_norm;  // field 13

      s_width = l3._s_width;  // field 14

      Hist_Size = l3._Hist_Size;  // field 15

       for(w=0; w<N_regions; w++){       // array field 16
        C_Angles[w] = l3._C_Angles[w];
      }
      
      for(w=0; w<N_regions; w++){    // array field 17
       C_Coeffs[w] = l3._C_Coeffs[w];
      }

     for(w=0; w<Hist_Size; w++){                // array field 18
      Point_Hist_x[w] = l3._Point_Hist_x[w];
    }
    
      for(w=0; w<Hist_Size; w++){                  // array field 19
         Point_Hist_z[w] = l3._Point_Hist_z[w];
      }

      for(w=0; w<4; w++){ // write detector index
             D_Seq[w]  = l3._D_Seq[w];                     // array field 20
      }

   for(x=0; x<N_regions; x++){ // loop on the sky regions

                         for(w=0; w<Nchan; w++){ // loop on the strips
                            MDImage[C_Index[x]][D_Seq[0]][w] = MDImage[l3._C_Index[x]][l3._D_Seq[0]][w];
                        } // end of the loop on the strips
                        for(w=0; w<Nchan; w++){ // loop on the strips
                            MDImage[C_Index[x]][D_Seq[1]][w] = MDImage[l3._C_Index[x]][l3._D_Seq[1]][w];
                        } // end of the loop on the strips
                        for(w=0; w<Nchan; w++){ // loop on the strips
                            MDImage[C_Index[x]][D_Seq[2]][w] = MDImage[l3._C_Index[x]][l3._D_Seq[2]][w];
                        } // end of the loop on the strips
                        for(w=0; w<Nchan; w++){ // loop on the strips
                            MDImage[C_Index[x]][D_Seq[3]][w] = MDImage[l3._C_Index[x]][l3._D_Seq[3]][w];
                        } // end of the loop on the strips

  }// end of loop on the sky regions
  
}
/** No descriptions */
void SAdata::IrosMap::saveL3IMBinary(){
}


        //  //                fstream binary_file("test.dat",ios::out|ios::binary|ios::trunc);
////                binary_file.write(reinterpret_cast<char *>(starts), i_fn_length_0);
//                if (verbose) os << "written startstring = "<< starts << endl;
////                binary_file.write(reinterpret_cast<char *>(&i_fn_length_1), sizeof(int));
//                if (verbose) os << "written i_fn_length_1 = "<< i_fn_length_1 << endl;
////                binary_file.write(reinterpret_cast<char *>(cfin_out), i_fn_length_1);
//                if (verbose) os << "written cfin_out = "<<  cfin_out << endl;
////                binary_file.write(reinterpret_cast<char *>(&i_fn_length_2), sizeof(int));
//                if (verbose) os << "written i_fn_length_2 = "<< i_fn_length_2 << endl;
////                binary_file.write(reinterpret_cast<char *>(cfin_p), i_fn_length_2);
//                if (verbose) os << "written cfin_p = "<< cfin_p << endl;
////                binary_file.write(reinterpret_cast<char *>(&Nchan), sizeof(short int));
//                if (verbose) os << "written Nchan = "<< Nchan << endl;
////                binary_file.write(reinterpret_cast<char *>(&Tburst), sizeof(float));
//                if (verbose) os << "written Tburst = "<< Tburst << endl;
////                binary_file.write(reinterpret_cast<char *>(&EnMin),sizeof(float));
//               if(verbose) os<<"written EnMin: "<< EnMin << endl;
////                binary_file.write(reinterpret_cast<char *>(&EnMax),sizeof(float));
//               if(verbose) os<<"written EnMax: "<< EnMax << endl;
////                binary_file.write(reinterpret_cast<char *>(&N_regions),sizeof(short int));
//               if(verbose) os<<"written N_regions: "<< N_regions << endl;
////                binary_file.write(reinterpret_cast<char *>(&max_angle),sizeof(float));
//                if(verbose) os<<"written maxangle: "<< max_angle << endl;
////                binary_file.write(reinterpret_cast<char *>(&f_length),sizeof(float));
//               if(verbose) os<<"written f_length: "<< f_length << endl;
////                binary_file.write(reinterpret_cast<char *>(&s_width),sizeof(float));
//                // if(verbose)  os<<"written s_width: "<<  endl;
////                binary_file.write(reinterpret_cast<char *>(&delta_norm),sizeof(float));
//                if(verbose) os<<"written delta_norm: "<< delta_norm << endl;
//
//              for(w=0; w<N_regions; w++){
////                  binary_file.write(reinterpret_cast<char *>(&C_Angles[w]),sizeof(float));
//                  if(verbose) os<<"written C_Angles, element  "<< w << " value "<< C_Angles[w] << endl;
//              }
//
//              for(w=0; w<N_regions; w++){
////                  binary_file.write(reinterpret_cast<char *>(&C_Coeffs[w]),sizeof(float));
//                  if(verbose) os<<"written C_Coeffs, element  "<< w << " value "<< C_Coeffs[w] << endl;
//              }
//
////              binary_file.write(reinterpret_cast<char *>(&Hist_Size),sizeof(short int));
//
//            for(w=0; w<Hist_Size; w++){
////                binary_file.write(reinterpret_cast<char *>(&Point_Hist_x[w]),sizeof(float));
//                if(verbose) os<<"written Point_Hist_x, element  "<< w << " value "<<  Point_Hist_x[w] << endl;
//             }
//
//            for(w=0; w<Hist_Size; w++){
////                binary_file.write(reinterpret_cast<char *>(&Point_Hist_z[w]),sizeof(float));
//                if(verbose) os<<"written Point_Hist_z, element  "<< w << " value " << Point_Hist_z[w] << endl;
//            }
//
//            for(w=0; w<4; w++){ // write detector index
////              binary_file.write(reinterpret_cast<char *>(&D_Seq[w]),sizeof(short int));
//              os << "written D_Seq[w] = " << D_Seq[w] << endl;
//            }
//
//            os << "SAL3Eventlist::saveIrosMap() going to write the MultiDetectorImage"<< endl;
//            /// REMEMBER TO CHANGE !
//            /// AND USE DEFAULT VALUES!
//
//
//            //verbose = true;
//            if(verbose) os << "For "<< N_regions << " regions " << endl;
//            for (w=0; w<4; w++) os << "For detector n. "<<  D_Seq[w] <<  " and then "<< endl;
//            int count = 0;
//            for(x=0; x<N_regions; x++){ // loop on the sky regions
//            if(verbose) os << "####  data for the sky region "<< C_Index[x]  << endl;
//
////            binary_file.write(reinterpret_cast<char *>(&C_Index[x]),sizeof(short int)); /// write the region index
//            if(verbose) os << " written  index region "<< C_Index[x]   << endl;
//
//                 os << endl;
//                if(verbose)os<<"    writing MDImage,  detector code = "<< D_Seq[0]  << " det   = "<< 0  <<  endl;
//                 os << endl;
//                for(w=0; w<Nchan; w++){ // loop on the strips
////                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[0]][w]),sizeof(long int));
//                    if(verbose) os<<"        writing MDImage, region "<< C_Index[x] << " detector code"<< D_Seq[0] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[0]][w]<< endl;
//                 }
//                 os << endl;
//                if(verbose)os<<"    completed MDImage,  detector code"<< D_Seq[0]  << " det  "<< 0  <<  endl;
//                 os << endl;
//
//                 os << endl;
//                if(verbose)os<<"    writing MDImage,  detector code = "<< D_Seq[1]  << " det   = "<< 1  <<  endl;
//                 os << endl;
//                for(w=0; w<Nchan; w++){ // loop on the strips
////                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[1]][w]),sizeof(long int));
//                    if(verbose) os<<"        writing MDImage, region "<< C_Index[x] << " detector "<< D_Seq[1] << " element " << w << " value "<< MDImage[C_Index[x]][D_Seq[1]][w] << endl;
//                 }
//                 os << endl;
//                if(verbose)os<<"completed MDImage,  detector code = "<< D_Seq[1]  << " det =  "<< 1  << endl;
//                 os << endl;
//
//                 os << endl;
//                if(verbose)os<<"    writing MDImage,  detector code"<< D_Seq[2]  << " det  "<< 2  <<  endl;
//                 os << endl;
//                for(w=0; w<Nchan; w++){ // loop on the strips
////                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[2]][w]),sizeof(long int));
//                    if(verbose) os<<"        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[2] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[2]][w] << endl;
//                 }
//                 os << endl;
//                if(verbose)os<<"completed MDImage,  detector code = "<< D_Seq[2] << " det  = "<< 2 << endl;
//                 os << endl;
//
//                 os << endl;
//                if(verbose)os<<"    writing MDImage,  detector code = "<< D_Seq[3]  << " det  = "<< 3  <<  endl;
//                 os << endl;
//                for(w=0; w<Nchan; w++){ // loop on the strips
////                    binary_file.write(reinterpret_cast<char *>(&MDImage[C_Index[x]][D_Seq[3]][w]),sizeof(long int));
//                    if(verbose) os << "        writing MDImage, region "<< C_Index[x] << " detector code "<< D_Seq[3] << " element " << w <<  " value "<< MDImage[C_Index[x]][D_Seq[3]][w] << endl;
//                 }
//
//                 os << endl;
//                if(verbose)os<<"completed MDImage,  detector code = "<< D_Seq[3] << " det  = "<< 3 << endl;
//                 os << endl;
//
//                 os << endl;
//                 os << endl;
//                if(verbose)os << "#### completed data for the sky region index: "<<  x << endl;
//                 os << endl;
//                 os << endl;
//
////               if(verbose)os << "written mdimage array region n. "<< count++<< endl;
//            }// end of the loop on the sky regions
//
//                if(verbose) os << "written all data" << endl;
// //               binary_file.close();