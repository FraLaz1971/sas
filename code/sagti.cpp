/***************************************************************************
                          sagti  -  description
                             -------------------
    begin                : mer giu 13 2007
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
#include "sagti.h"

namespace SAdata {

SAGTI::SAGTI()
{
 verbose = true;
}


SAGTI::~SAGTI()
{
}


}


/*!
    \fn SAdata::SAGTI::read(const string &gtifile)
 */
void SAdata::SAGTI::read(const string &gtifile)
{
	nrows = 0;
	ij=0;

	char *infi  = (char *)gtifile.c_str();  /* name for existing FITS file   */
	cout << "SAGTI::read opening " << infi << endl;
	const string bim(infi);

	
              int status, morekeys, hdutype;

//         double mfi; mfi = 53005.;
//         double mff; mff = 0.00075444444444444;
//         double tz; tz = 0.;

    status = 0;
  //  remove(outf);            /* Delete old file if it already exists */

    if ( fits_open_file(&infptr, infi, READONLY, &status) )
         SAFitsHandler::printerror( status );

	// read events table dimension


	if ( fits_movabs_hdu(infptr, 2, &hdutype, &status) )
         printerror( status );


   	fits_get_num_rows(infptr, &nrows, &status);


    if (verbose) cout << "SAGTI::read number of rows " << nrows << endl;
	// correct time
      frow      = 1; felem     = 1;       nelem     = nrows;
      longnull  = 0;      floatnull = 0.;      Doublenull = 0.;

     double *loc_start = new double[nrows];
     memset((void *)loc_start , 0, nrows*sizeof(double));

     double *loc_stop = new double[nrows];
     memset((void *)loc_stop , 0, nrows*sizeof(double));

     if(fits_read_col(infptr, TDOUBLE, 1, frow, felem, nelem, &anynull,  loc_start,
                    &anynull, &status)) SAFitsHandler::printerror(status);

     if(fits_read_col(infptr, TDOUBLE, 2, frow, felem, nelem, &anynull,  loc_stop,
                    &anynull, &status)) SAFitsHandler::printerror(status);

     for (ij = 0; ij < nrows; ij++){

      if ((verbose)&&(ij<10)) cout << "SAGTI::read() good time start =  " << loc_start[ij] << endl;

      tempgti.first = loc_start[ij];tempgti.second = loc_stop[ij];
      push_back(tempgti);
      if ((verbose)&&(ij<10)) cout << "SAGTI::read() goot time stop =  " << loc_stop[ij] << endl;

     }

delete[] loc_start;
delete[] loc_stop;

    if (fits_close_file(infptr, &status)) SAFitsHandler::printerror(status);

}


/*!
    \fn SAdata::SAGTI::save(const string &gtifile)
 */
void SAdata::SAGTI::save(const string &gtifile)
{
	ij = 0; ii=0;

    char* ttype1[2];     char* tform1[2];     char* tunit1[2];

    char extname1[]  = "STDGTI";

  tform1[0] = (char *)"1D";   ttype1[0] = (char *)"START"; tunit1[0] = (char *)"s";
  tform1[1] = (char *)"1D";   ttype1[1] = (char *)"STOP"; tunit1[1] = (char *)"s";

        char *outf = (char *)gtifile.c_str();  /* name for new FITS file        */

    if (fits_create_file(&outfptr, outf, &status)) /*create FITS file*/
         SAFitsHandler::printerror( status );           /* call printerror if error occurs */

    if ( fits_create_tbl(outfptr, BINARY_TBL, nrows, 2, ttype1, tform1,
        tunit1, extname1, &status) )
        printerror( status );


     double *loc_start = new double[nrows];
     memset((void *)loc_start , 0, nrows*sizeof(double));

     double *loc_stop = new double[nrows];
     memset((void *)loc_stop , 0, nrows*sizeof(double));

	
	gticur = begin();
        for (ii = 0; ii < nrows; ii++){
	  tempgti = *gticur++;
          loc_start[ii] = tempgti.first;
          loc_stop[ii] = tempgti.second;
          if (verbose) cout << "saved TSTART n. " << ii << " value = " << loc_start[ii] << endl;
          if (verbose) cout << "saved TSTOP n. " << ii << " value = " << loc_stop[ii] << endl;
        }

        if(fits_write_col(outfptr, TDOUBLE, 1, 1, 1, (long)nrows, loc_start, &status))
            printerror(status);


        if(fits_write_col(outfptr, TDOUBLE, 2, 1, 1, (long)nrows, loc_stop, &status))
            printerror(status);


    if (fits_close_file(outfptr, &status)) SAFitsHandler::printerror(status);

	delete[] loc_start;
	delete[] loc_stop;

}


/*!
    \fn SAdata::SAGTI::getDistance(GTI g)
 */
double SAdata::SAGTI::getDistance(GTI g)
{
    return (g.second - g.first);
}
