/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Tue Mar 21 13:02:28 CET 2006
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef   IOSTREAM_H
#include <iostream>
#endif

#ifndef SASOAUSERINTERFACE_H
#include "sasoauserinterface.h"
#endif
#include "qsasoapilot.h"
#include <string>
#include <qapplication.h>
#include <qlabel.h>
#include <CCfits>
#include <FITS.h>
using namespace CCfits;
using namespace SApipeline;
using namespace std;



// ######## SASOA main() BEGIN
int main(int argc, char** argv)
{
  int status;
  string compare, batchline;
  cout << "SASOA (Super Agile Standard Orbital Analysis pipeline),  version " << SASOA_VERSION << endl;
  bool verboseapp = false;
  bool once = false;
  SasoaUserInterface *commandline = new SasoaUserInterface(verboseapp);
  commandline->initPipeline();
  //cout << "numero di argomenti = " << argc << endl;
  //int c = 0;
  const char ** start =  (const char **)argv;
  /*  while(c<argc) {
      cout << "argomento n." << c++ <<  " = " << *argv++ << endl;
    } */  if (argc > 1){
       compare = *(start+1) ;
      if(compare == "-b"){
        commandline->setBatch(true);
        cout << "selected batch execution" << endl;
        batchline = *(start+2);
        commandline->setBatchCommand(batchline);
        once = true;
        }
        else{
          cout << "selected interactive execution "<< endl;
          if (compare == "-g"){
            cout << "selected graphical user interface (GUI) " << endl;
            QApplication app(argc, argv);
            QSasoaPilot *pilot = new QSasoaPilot();
            app.setMainWidget(pilot);
            pilot->setSasoa(*commandline);
            pilot->show();
            app.exec();
            return status;
          }
        }
      }
      /* starts the commandline interactive loop */
      status = commandline->run();
      commandline->setBatch(false);
     if(once){
      delete commandline;
    }
  cout << "bye, bye."<< endl;
  system("date");
  return status;
}


// ######## SASOA main() END

