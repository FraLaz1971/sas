/***************************************************************************
                          sourcesextractor.cpp  -  description
                             -------------------
    begin                : Wed Feb 22 2006
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
/***************************************************************************
This software is part of the of the SuperAGILE instrument data 
analysis software library
 ***************************************************************************/

#include "sourcesextractor.h"
namespace SApipeline{

SourcesExtractor::SourcesExtractor(){
    setDefault();
    showDefault();
    derived = 1;    
    status = PipelineModule::init();
    setExtern(true);
    created_del_dir = false;
	attitude_base_dir.assign("/../stg_2/attitude/version_for_sasoa");
}
SourcesExtractor::~SourcesExtractor(){
}
}/** No descriptions */
int SApipeline::SourcesExtractor::init(){
  irosmapfilename = "default_im_fn.dat";
  iroslogfilename = "default_iroslog.txt";
  tempstring =  arc->getSasoaHome()+"/stg_2/IROS_Multi-D/launchIrosIDLBatch";
  iros_idl_batch_fn = tempstring;
  return 0;
}
void SApipeline::SourcesExtractor::setDescription(){
  //cout << "SApipeline::Ssrcxtractor.ourcesExtractor::setDescription()" << endl;
  description = "[multiple sources extraction (stage 2)] ";
}
  /** No descriptions */
void SApipeline::SourcesExtractor::start(){
}
void SApipeline::SourcesExtractor::launch(string & infile, string & outfile, vector<int> params){
  PipelineModule::launch(infile, outfile, params);
  if (verbose) cout << "SourcesExtractor::launch() the commandlist to be executed is the following: " << endl;
  commandlist.show();
  //if arc->clear_L3_Data();
  launchAttitudeCorrection();
}  
/** No descriptions */
void SApipeline::SourcesExtractor::launchIDL_Batch(){
  //system( "./launchSourcesExtraction.bash");
}
/** No descriptions */
void SApipeline::SourcesExtractor::deliverProducts(){
//  string sarg1("ls *");
//  FileList *outfilelist = new FileList(sarg1);
//  outfilelist->show();
  //delete outfilelist;
  SAFileNamer sfn; sfn.setFileName(arc->filenamer.getFileName(OrbitRebuilding));  
  string temps0 = sfn.getNameRoot();
  if (verbose) cout << "SourcesExtractor::deliverProducts() base name for delivered files : " << temps0 << endl;
  if (verbose) cout << "SourcesExtractor::deliverProducts() source file to copy" << endl;
  
//############################################################################
//######################### REMEMBER TO HANDLE !!
//############################################################################

	//string sarg("ls ../stg_2/*.dat *.log ../stg_2/IROS_Multi-D/iros_log_det*.txt  *.evt ../stg_2/ ../stg_2/*.csl ../stg_2/*.si ../stg_2/*.sfl ../stg_2/*.ps ../stg_2/*.ascii ../stg_2/*.txt ");
  
 //  used for Temporal Data Set Analysis

  string sarg("ls *_bti.fits ../stg_2/*.dat *.evt  ../stg_2/IROS_Multi-D/iros_log_det*.txt  ../stg_2/*.evt  ../stg_2/*.csl ../stg_2/*.si ../stg_2/*.sfl ../stg_2/*.ps ../stg_2/*.ascii ../stg_2/*.txt ");

  FileList *soutfilelist = new FileList(sarg);
  soutfilelist->show();

  // create the file list with the destination files
  if (verbose) cout << "SourcesExtractor::deliverProducts() destinations " << endl;
  
//############################################################################
//######################### REMEMBER TO HANDLE !!
//############################################################################
  //string sarg2 = "ls ../stg_2/*.dat *.log ../stg_2/IROS_Multi-D/iros_log_det*.txt *.evt ../stg_2/*.csl ../stg_2/*.si ../stg_2/*.sfl ../stg_2/*.ps ../stg_2/*.ascii ../stg_2/*.txt ";
  string sarg2("ls *_bti.fits ../stg_2/*.dat *.evt  ../stg_2/IROS_Multi-D/iros_log_det*.txt  ../stg_2/*.evt  ../stg_2/*.csl ../stg_2/*.si ../stg_2/*.sfl ../stg_2/*.ps ../stg_2/*.ascii ../stg_2/*.txt ");
  FileList *doutfilelist = new FileList(sarg2);
  doutfilelist->show();

  list<string>::iterator rit1 = soutfilelist->begin();

  while (rit1 != soutfilelist->end()) {
       tempstring = "cp -f "+(*rit1)+" "+getSasoaWorkDir()+"/delivery";
       cout << "SourcesExtractor::deliverProducts() copy command = " << tempstring << endl;
       syscon.execCommand(tempstring);
       rit1++;
  }


  ts = "cp -f "; string tt(arc->get_L3_Dir());
  ts.append(tt);ts.append("/*L3*.evt ");
  ts.append(getSasoaWorkDir());ts.append("/delivery");
  cout << "SourcesExtractor::deliverProducts() executing " << ts << endl;
  syscon.execCommand(ts);

  // deliver the SourcesExtractor products
  ts = "mv -f "; ts.append(" saprodset* ");
  ts.append(getSasoaWorkDir());ts.append("/delivery");
  syscon.execCommand(ts);

  delete soutfilelist;
  delete doutfilelist;


}

/** No descriptions */
void SApipeline::SourcesExtractor::announceDelivery(){
  cout << "SourcesExtractor (stage 2) "<< endl;
  PipelineModule::announceDelivery();
  tempstring = "ls "+getSasoaWorkDir()+"/delivery/*L3.evt";
  system(tempstring.c_str());
}

      /**
      creates a script to launch stage 2 [sources extractor]
      to launch the second step is mandatory to have a datacards.txt file 
      create the datacards.txt file and insert:
      1) 39.05 data filename
      2) 39.14 attitude data filename
      3) outputfilename
      */
      
void SApipeline::SourcesExtractor::createLaunchBatchScript(){
if (verbose) cout << "[stage 2] SourcesExtractor::createLaunchBatchScript()" << endl;
if (verbose) cout << "inputfilename to write in the datacard is "<< commandlist.getInputFilename()  << endl;;
ofstream outfile;
outfile.open ("../stg_2/attitude/version_for_sasoa/datacards/datacards.txt", ofstream::out | ofstream::trunc);
outfile << "################################################################"<< endl;
outfile << "#" << endl;
outfile << "#   L. Pacciani                                            F. Lazzarotto"<< endl;
outfile << "#   30/5/2006                                            15/07/2007     "<< endl;
outfile << "#   "+tmr.getDateString() << endl;
outfile << "#   luigi.pacciani@iasf-roma.inaf.it                    francesco.lazzarotto@iasf-roma.inaf.it"<< endl;
outfile << "#"<< endl;
outfile << "# esempio di file di input per sal2_to_l3 "<< endl;
outfile << "#"<< endl;
outfile << "# this file is automatically generated by sasoa"<< endl;
outfile << "#"<< endl;
outfile << "###############################################################"<< endl;
outfile << "# sintassi:"<< endl;
outfile << "#"<< endl;
outfile << "# KEYWORD 'valore'    /commento"<< endl;
outfile << "#"<< endl;
outfile << "# Il simbolo  #  ad inizio riga"<< endl;
outfile << "# serve per commentare la riga stessa"<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# lista dei file con eventi L2."<< endl;
outfile << "# La lista deve essere ordinata in tempo"<< endl;
string ts; ts = getSasoaWorkDir()+"/data/L2";
commandlist.setDefaultInDir(ts);

if (commandlist.isPathAbsolute()){
    tempstring = "L2EVL   '"+commandlist.getInputFilename()+"'";  
}

if(isAuto()){
  tempstring = "L2EVL   '"+commandlist.getInputdir()+"/"+getInputFileName()+"'";
} else {
  tempstring = "L2EVL   '"+commandlist.getInputdir()+"/"+commandlist.getInputFilename()+"'";
}

if (verbose) cout <<"going to write the following instruction"<< endl;
cout << "" << tempstring << endl;
outfile << tempstring << endl;
outfile << "#FINE: lista dei ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# nome del file L3 di output al programma"<< endl;
//tempstring = "L3EVL   '"+arc->get_L3_Dir()+"/"+arc->filenamer.getOutputFileName(AttitudeCorrection)+"'";
//tempstring = "L3EVL   '"+arc->get_L3_Dir()+"/"+"prova_outfile_L3.evt"+"'";
tempstring = "L3EVL   './prova_outfile_L3.evt'";
//outfile << "L3EVL   './prova_outfile_L3.evt'"<< endl;
outfile << tempstring << endl;
outfile << "#FINE: nome del file L3 ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "#################################################################"<< endl;
outfile << "# Il puntamento nominale e' in lat, long dell'asse ottico di superagile."<< endl;
outfile << "# In aggiunta c'e' l'angolo di roll rispetto all'asse ottico."<< endl;
outfile << "# Tutti gli angoli in radianti."<< endl;
outfile << "# Un apposito modulo puo' calcolarlo."<< endl;
outfile <<  endl;
outfile << "SALAT_RAD  '-0.5049813'  /rad"<< endl;
outfile << "SALONG_RAD '+4.6495571'  /rad, dove punti?"<< endl;
outfile << "SAROLL_RAD '-2.6011732'  /rad"<< endl;
outfile << "T0_QUAT_S '+1451606400.'       /per usare 39.14 non corretti insieme ai sal3"<< endl;
outfile <<  endl;
outfile << "# FINE: Il puntamento ... "<< endl;
outfile <<  endl;
outfile << "#################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# lista file 39.14 per i quaternioni"<< endl;
outfile << "# La lista deve essere ordinata in tempo"<< endl;
outfile <<  endl;
if(!commandlist.isAttFileSet()){
  outfile <<  "AG3914   '"<< "../../sal2_to_l3_ex_short/ag3914_gc.fits" << "'"<< endl;
} else {
  outfile <<  "AG3914   '"<< arc->get_SAL1Cor_Dir() +"/"+commandlist.getAttitudeFileName() << "'"<< endl;  
}
outfile << "#FINE: lista file 39.14 ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# DTMAX_NOATT_S definisce l'intervallo di tempo massimo accettabile (in secondi)"<< endl;
outfile << "#               di buco tra dati consecutivi di attitude contenuti"<< endl;
outfile << "#               nei file 39.14."<< endl;
outfile << "#"<< endl;
outfile <<  endl;
outfile << "DTMAX_NOATT_S  '2.'"<< endl;
outfile <<  endl;
outfile << "#FINE: DTMAX_NOATT_S definisce ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# lista file con i good time intervals"<< endl;
outfile <<  endl;
outfile << "#GTI   'mygti.fits'"<< endl;
outfile <<  endl;
outfile << "#FINE: lista file con i good ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# se i file con le gti non sono stati definiti,"<< endl;
outfile << "# si puo' dare uno start ed uno stop"<< endl;
outfile << "# con le seguenti due KEYWORD"<< endl;
outfile << "# i tempi sono in secondi, l'origine dei tempi e' la stessa che per le gti "<< endl;
outfile <<  endl;
outfile << "TSTART_S '108227200.000' "<< endl;
outfile << "TSTOP_S  '108233536.000'"<< endl;
outfile <<  endl;
outfile << "#FINE: se i file con le gti ...  "<< endl;
outfile << "################################################################ "<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################# "<< endl;
outfile << "# di seguito si definisce l'origine dei tempi per "<< endl;
outfile << "# GTI / T_START & T_STOP"<< endl;
outfile << "# eventi L2"<< endl;
outfile << "# dati di attitude"<< endl;
outfile <<  endl;
outfile << "T0_GTI_S   '0.'       /non conosco ancora l'origine dei tempi delle GTI "<< endl;
outfile << "T0_EVL_S   '0.'       /non conosco ancora l'origine dei tempi della event list L2 "<< endl;
outfile << "T0_QUAT_S  '+1451606400.'       /per cambiare l'origine dei tempi dei quaternioni nei file 39.14"<< endl;

outfile << "#FINE: di seguito si definisce l'origine ... "<< endl;
outfile << "AVOID_TIMEREF_CHECK 'dummy'    /scommentare per usare 39.14 non corretti insieme ai sal3"<< endl;
outfile << "#################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile.close();                     

}
void SApipeline::SourcesExtractor::launchAttitudeCorrection(double tstart, double tstop){
// retrieve contact_min contact_max from DB
// launchAttitudeCorrection(contact_min, contact_max)
}
void SApipeline::SourcesExtractor::launchAttitudeCorrection(int cmin, int cmax){
  //AGILEDBConnector mydatabase;
  //database = (dbconnector *)&mydatabase;
  string dc("../stg_2/attitude/version_for_sasoa/datacards/datacard_new.card");
  //string l2f(mydatabase.getL2fileName(cmin));
  string l2f(arc->get_L2_Filename(cmin));
  string atf(arc->get_Att_Filename(cmin));
  createAttitudeBatchScript();
  if (cmin==cmax){
  	cout << "SourcesExtractor::launchAttitudeCorrection() cmin = cmax" << endl;
  	createAttitudeDatacard(dc, l2f, atf);
  } else {
  string m("launchAttitudeCorrection() TO handle contact_min contact_max !");
  se.setMsg(m); throw(e);
  }
  launchAttitudeCorrection();
/*
int ccur(0); // contact cursor
while (ccur < cmax+1){

// create datacard 
// launch attitude correction routine

}
*/
}
/** No descriptions */
void SApipeline::SourcesExtractor::launchAttitudeCorrection(){
    if (verbose) cout << "[stage 2] SourcesExtractor::launchAttitudeCorrection()" << endl;  
	try{
	    tempstring.assign("rm -f ag3914_sal3_bti.fits");
    	syscon.execCommand(tempstring);	
	    tempstring.assign("rm -f  ../stg_2/attitude/version_for_sasoa/src/ag3914_sal3_bti.fits");
    	syscon.execCommand(tempstring);				
	    tempstring.assign("./launchSourcesExtraction.bash");
    	syscon.execCommand(tempstring);
	    tempstring.assign("rm -f  ../stg_2/attitude/version_for_sasoa/src/ag3914_sal3_bti.fits");
    	syscon.execCommand(tempstring);				
	    tempstring.assign("./launchSourcesExtraction.bash");
    	syscon.execCommand(tempstring);
        } catch(const SAexception &se){
		cerr << "SourcesExtractor::launchAttitudeCorrection() error "<< se.getMsg() << endl;
	} catch(const exception &e){
		cerr << "SourcesExtractor::launchAttitudeCorrection() error "<< e.what() << endl;
	} catch(...){
		cerr << "SourcesExtractor::launchAttitudeCorrection() error "<< endl;
	}	
}
/** No descriptions */
void SApipeline::SourcesExtractor::passOutputFile(const string &toutdir){

  if(verbose)  cout << "executing SourcesExtractor::passOutputFile()"<< endl;
  if(verbose)  cout << "SourcesExtractor::passOutputFile() the output file from stage 2 is generated in "  << getOutputDir() << endl;
  if(verbose)  cout << "SourcesExtractor::passOutputFile()  i'm going to copy output file in "<< toutdir << endl;
  string yt(arc->filenamer.getOutputFileName(SourcesExtraction));
  if(verbose)  cout << "SourcesExtractor::passOutputFile() would you like to call the file "<<  yt << endl;

  string temps;
  string tl3name("prova_outfile_L3.evt");
  temps = "cp ";
  temps.append(arc->getSasoaHome());temps.append("/stg_2/attitude/version_for_sasoa/bin/");temps.append(tl3name);
  temps.append(" ");temps.append(toutdir);temps.append("/");temps.append(yt);
  syscon.execCommand(temps);
  temps = "ls ";
  temps.append(arc->getSasoaHome());temps.append("/stg_2/attitude/version_for_sasoa/bin/");temps.append(tl3name);
  temps.append(" ");temps.append(toutdir);temps.append("/");temps.append(yt);
  syscon.execCommand(temps);

  if(verbose) cout << "SourcesExtractor::passOutputFile()  shell command: " << temps << endl;
  if(verbose)  cout << "ended SourcesExtractor::passOutputFile()"<< endl;
}
/** No descriptions */
void SApipeline::SourcesExtractor::setOutputDir(const string &od){
  //  tempstring = getSasoaHome()+"/stg_2/";
  PipelineModule::setOutputDir(od);
}
/** No descriptions */
void SApipeline::SourcesExtractor::setDefaultOutputDir(){
  tempstring = arc->getSasoaHome()+"/stg_2/attitude/version_for_sasoa/bin/";
  if (verbose) cout << "SourcesExtractor::setDefaultOutputDir default output dir = "<< tempstring << endl;
  setOutputDir(tempstring);
  setProductPath(tempstring);  
  if (verbose) cout << "SourcesExtractor::setDefaultOutputDir default products path = "<< tempstring << endl;
}
/** No descriptions */
void SApipeline::SourcesExtractor::setProductPath(const string &prodp){
    products_path = prodp;
}
/** No descriptions */
string SApipeline::SourcesExtractor::getProductPath(){
  return products_path;
}

void SApipeline::SourcesExtractor::launchIros(const string &mapdir, const string &pilotfile, const string &pointpilotfile){  
  try{
    string temp = "../stg_2";
    irospilot.setBaseDir(temp);
    //passIrosMap(mapfilename, irospilot.getBaseDir());
    cout << "launchIros(const string &mapdir, const string &pilotfile, const string &pointpilotfile) launching IROS on files contained in " << mapdir << endl;
    arc->setIrosMapFileName(mapdir);
    setIrosMapFileName(mapdir);
    temp =  "../stg_2/IROS_Multi-D/launchIrosIDLBatch";
    setIROS_IDLBatchFileName(temp);
    irospilot.createPointingPilot();
    printPointingBatch(cout);
    string pstring = "../stg_2/.MD_IROS_Pilot";
    for(int i=0; i<4; i++) {
	irospilot.createPilot(i);
      //createIrosBatch(i, pstring, mapfilename); // create the internal iros pilot file
      //createPointingBatch(l3file); // create the internal iros pilot file
      showIrosBatch();
      irospilot.setDetector(i);
      createIrosIDLBatch(getIROS_IDLBatchFileName());  // create the IDL batch
      launchIros();
    }
    
    } catch(const exception &e){
        cerr << "error in launching iros "<< se.getMsg()<< endl;
      } catch(const SAexception &se){
        cerr << "error in creating iros "<< e.what()<< endl;
      } catch(...){
        cerr << "error in creating iros "<< endl;
      } 

}

  /** No descriptions */

/** No descriptions */
void SApipeline::SourcesExtractor::launchIrosMapBuilder(){

    try{
      if (verbose) cout << "SourcesExtractor::launchIrosMapBuilder() executing L3 eventlist processing" << endl;

    tempstring2 = "../stg_2/attitude/version_for_sasoa/bin/prova_outfile_L3.evt";
    SAL3Eventlist sal3;

    sal3.init();string ii("png");
  	sal3.setPlotTerm(ii);
    sal3.setInputFilename(tempstring2);string hdn0("PACKETS"); 
    string hdn("EVENTS");  string fn(tempstring2);try{
    sal3.readHeaders(hdn0);
} catch (const exception &e){
	cerr << "error in reading the l3 evlist header" << e.what() << endl;
} catch (...){
	cerr << "error in reading the l3 evlist header" << endl;
}

    if (verbose) cout << "SourcesExtractor::launchIrosMapBuilder() read dim = " << sal3.getInputDimension() << endl;
    try{
    sal3.readDebug(fn);
    //  sal3.read(fn);
    } catch (...){
	cerr << "error in reading the eventlist "<< endl;
    }

	//	energy filter
	sal3.filterEnergy(20, 55);
	sal3.effect();
  /*
 		string nn("E_min_20_E_MAX_55");
		string newfn = arc->filenamer.getOutputFileName(SourcesExtraction);
		string ots = newfn.insert(newfn.find_last_of("."), nn);
		//newfn.insert(newfn.find_last_of("."), getFilterTarget());
		sal3.save(ots);       */

// TIME FILTER

// exposure gti filter



     /*
    cout << "SourcesExtractor::launchIrosMapBuilder() filtering for Earth Occultation GTI " << endl; 
	tempstring = arc->getCurrentExposureGTI_FileName();

	sal3.filterAllGTI(tempstring);
	sal3.effect();

 		nn = "EARTH";
		newfn = arc->filenamer.getOutputFileName(SourcesExtraction);
		ots = newfn.insert(newfn.find_last_of("."), nn);
		//newfn.insert(newfn.find_last_of("."), getFilterTarget());
		sal3.save(ots);
// saga gti filter
/*
    cout << "SourcesExtractor::launchIrosMapBuilder() filtering for Saga GTI " << endl; 
	tempstring = arc->getCurrentSagaGTI_FileName();
	sal3.filterAllGTI(tempstring);
	sal3.effect(); 
 		nn = "SAGA";
		newfn = arc->filenamer.getOutputFileName(SourcesExtraction);
		ots = newfn.insert(newfn.find_last_of("."), nn);
		sal3.save(ots);
                                   */
	
    sal3.createPointHistos();
    sal3.setProdSetDir(arc->filenamer.getContact());
//    sal3.fixProdSetDir();
    sal3.createProdSetDir();

    sal3.setImageType(0);
    sal3.setFCounter(0);
    sal3.setDebug(false);
    sal3.getAllDetImages();

    string imf1 = "../stg_2/default_im_fn.dat";
    //string imf1 = "../stg_2/"; imf1.append(arc->filenamer.getFileName( IrosMapBuilding));
    //irospilot.setInputFileName(imf1);
         if (verbose) cout << "SourcesExtractor::launchIrosMapBuilder() saving irosmap on file "<< imf1 << endl;

    try{
//      system("rm test_irosmap.dat");
    }catch(...){cerr << "I/O error in removing dat file"<< endl;}


         if (verbose) cout << "SourcesExtractor::launchIrosMapBuilder() going to exec saveIrosMap3 "<< endl;
       try{
         sal3.saveIrosMap3(imf1);
         if (verbose) cout << "SourcesExtractor::launchIrosMapBuilder() executed saveIrosMap3 "<< endl;
      } catch(const exception &e){
          cerr << "exception in saving the iros map" << e.what() << endl;
      }


    sal3.setFCounter(0);
    sal3.setImageType(1);
    sal3.setDebug(false);
    sal3.plotMDImage();

    //  plot pointing histograms

    if (verbose) cout << "SourcesExtractor::plotting pointing histograms"<< endl;
    sal3.setDebug(false);
    sal3.setFCounter(0);
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');

     cout << "SasoaUserInterface::launchIrosMapBuilder ended"<< endl;
  } catch(exception &e){
    cerr << "SasoaUserInterface::handle_l3test() error in processing L3 eventlist" << endl;
    cerr << e.what() << endl;
  } catch (FitsException&) {
    cerr << "SasoaUserInterface::handle_l3test() FITS error in processing L3 eventlist" << endl;
}   catch(...){
    cerr << "SasoaUserInterface::handle_l3test() error!" << endl;

}

}



void SApipeline::SourcesExtractor::launchAttitude(const string &inputL2Filename, const string &inputAttFilename, const string &outputL3Filename){
  int status = 0;   bool verbose = false;
  cout.setf(ios::fixed,ios::floatfield);
  exception e; SAexception se;
  Timer mytime;  mytime.start();  SystemConnector mysystem;
  mysystem.execCommand("");

  if (verbose) cout << "SourcesExtractor::launchAttitude()  here 1" << endl;
  try{
  system("rm -f *.evt");  system("rm -f *.fits");
  system("rm attitude_datacard.txt");  system("rm -f quat_to_sapoi*.log");
  system("rm -f quat_to_sapoi*.log");  system("rm -f sal2_to_l3*.log");
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchAttitude(): errror in removing files datacard" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "errror in removing temp files" << e.what() << endl;
  } catch (...){
    cerr << "errror in removing temp files" << endl;
  }

  if (verbose)cout << "SourcesExtractor::launchAttitude() here 2" << endl;

  OrbitRebuilder orbilder;  string ff("../../plain3914files.txt");
  IrosPilot irospilot;  stringstream ss; 
  int emi = 21; int ema = 57;  SourcesExtractor srcx;  ArchiveHandler ark;
  string yyff("SA");	srcx.setDetNam(yyff);  int cmi(1), cma(2); 
 // h = infile, j = outfile
//  define attitude datacard filename
  string attdfn("attitude_datacard.txt"); 
//  define l2 input filename
  string l2fn(inputL2Filename);
  // obtain the current version of sal2_to_l3
  // add controls if necessary
  // obtain the SASOA_HOME environment var
  if (verbose) cout << "SourcesExtractor::launchAttitude()  here 3" << endl;
  string sh_varname; string sh_value;
  sh_varname = "SASOA_HOME"; 
  try{
   sh_value = mysystem.getEnvVar(sh_varname);
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting SASOA_HOME env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting SASOA_HOME env var" << e.what() << endl;
  } catch (...){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting SASOA_HOME env var" << endl;
  }
  if (verbose) cout << "here 3.25" << endl;
  string bb = sh_value; bb += "/stg_2/attitude/version_for_sasoa/script/sal2_to_l3.sh " ;
  bb += attdfn;
  string cof(inputL2Filename), sof(inputAttFilename), att(inputAttFilename);  
  string l3outf(outputL3Filename), dtemp, sf; 
  dtemp = sh_value;  dtemp += "/stg_2";
  string here("PWD");
  if (verbose) cout << "SourcesExtractor::launchAttitude()  here 3.30" << endl;
  try{
    irospilot.setBaseDir(dtemp);  
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting setting IrosPilot base dir" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting setting IrosPilot base dir" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting setting IrosPilot base dir" << endl;
  }
  if (verbose) cout << "SourcesExtractor::launchAttitude()  here 3.5" << endl;

  try{
    sf = mysystem.getEnvVar(here) ; 
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting PWD env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting PWD env var" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchAttitude(): errror in getting PWD env var" << endl;
  }

  if (verbose) cout << "SourcesExtractor::launchAttitude() here 4" << endl;
  // create attitude datacard and launch attitude correction
  // to produce dataset L3 file
  // filling a filelist 
  // containing input files to be processed
  try{
    srcx.fillFilelist(ff);
  // create attitude datacard
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchAttitude(): errror in filling the filelist datacard" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchAttitude(): errror in filling the filelist datacard" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchAttitude(): errror in filling the filelist datacard" << endl;
  }

  if (verbose) cout << "SourcesExtractor::launchAttitude() here 5" << endl;
	// create datacard

  try{
    srcx.createDefaultAttitudeDatacard(l2fn, att, l3outf);
  } catch (const SAexception &se){
    cerr << "attlaunch: errror in creating the attitude datacard" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "attlaunch: errror in creating the attitude datacard" << e.what() << endl;
  }catch (...){
    cerr << "attlaunch: errror in creating the attitude datacard" << endl;
  }
  // remember to adapt


//./launchIros "/home/lazza/.MD_IROS_Pilot_v4" "/home/lazza/projects/attitude_launcher/MD_IROS_Pilot_v4_test_0" "iros_out.log" "thisprefix"
//  srcx.launchIros(const string &mapdir, const string &pilotfile, const string &pointpilotfile);


	// remove temp files
  if (verbose) cout << "SourcesExtractor::launchAttitude() here 6" << endl;
  try{ 
    ss.str(""); ss << irospilot.getBaseDir() << "/attitude/version_for_sasoa/analisi/mdmap_tmp"; 
    string adf = "rm -rf " + ss.str(); system(adf.c_str());
    string hfh("rm -f ei_outfile_L3.evt"); system(hfh.c_str());
    string bfh("rm -f ei_sapoifile.fits"); system(bfh.c_str());
    string tfh("rm -f ag3914_sal3_bti.fits"); system(tfh.c_str());
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchAttitude() errror in removing temp files" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchAttitude() errror in removing temp files" << endl;
  }

  //---------------------------------------------------------------> 

  // launch  generation of attitude corrected L3 data file
  if (verbose) cout << "SourcesExtractor::launchAttitude() here 7: going to exec attitude correction " << endl;

try { 
  	system(bb.c_str());
 } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchAttitude(): exception occurred in executing attitude correction " << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchAttitude(): exception occurred in executing attitude correction " << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchAttitude(): exception occurred in executing attitude correction " << endl;
  }
int cc = arc->getCurrentContactNumber(); tempstring = "attitude";
cout << "SourcesExtractor::launchAttitude() executing agiledb.setSasoaStatusOnDB(" << cc << ", " << tempstring << ")"<< endl;
agiledb->setSasoaStatusOnDB(cc, tempstring);
}
// inputL2Filename inputL2Filename
// inputAttFilename inputAttFilename
// outputL3Filename outputL3Filename

/** No descriptions */
void SApipeline::SourcesExtractor::launchIrosV4(const string &inputL2Filename, const string &inputAttFilename, const string &outputL3Filename){
  int status = 0;   bool verbose = false;
  cout.setf(ios::fixed,ios::floatfield);
  exception e; SAexception se;
  Timer mytime;  mytime.start();  SystemConnector mysystem;
  mysystem.execCommand("");

  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 1" << endl;
  try{
  system("rm -f *.evt");  system("rm -f *.fits");
  system("rm attitude_datacard.txt");  system("rm -f quat_to_sapoi*.log");
  system("rm -f quat_to_sapoi*.log");  system("rm -f sal2_to_l3*.log");
  } catch (const SAexception &se){
    cerr << "attlaunch: errror in removing tempfiles" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "errror in removing temp files" << e.what() << endl;
  } catch (...){
    cerr << "errror in removing temp files" << endl;
  }

  if (verbose)cout << "SourcesExtractor::launchIrosV4() here 2" << endl;

  OrbitRebuilder orbilder;  string ff("../../plain3914files.txt");
  IrosPilot irospilot;  stringstream ss; 
  int emi = 21; int ema = 57;  SourcesExtractor srcx;  ArchiveHandler ark;
  string yyff("SA");	srcx.setDetNam(yyff);  int cmi(1), cma(2); 
 // h = infile, j = outfile
//  define attitude datacard filename
  string attdfn("attitude_datacard.txt"); 
//  define l2 input filename
  string l2fn(inputL2Filename);
  // obtain the current version of sal2_to_l3
  // add controls if necessary
  // obtain the SASOA_HOME environment var
  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 3" << endl;
  string sh_varname; string sh_value;
  sh_varname = "SASOA_HOME"; 
  try{
   sh_value = mysystem.getEnvVar(sh_varname);
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting SASOA_HOME env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting SASOA_HOME env var" << e.what() << endl;
  } catch (...){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting SASOA_HOME env var" << endl;
  }
  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 3.25" << endl;
  string bb = sh_value; bb += "/stg_2/attitude/version_for_sasoa/script/sal2_to_l3.sh " ;
  bb += attdfn;
  string cof(inputL2Filename), sof(inputAttFilename), att(inputAttFilename);  
  string l3outf(outputL3Filename), dtemp, sf; 
  dtemp = sh_value;  dtemp += "/stg_2";
  string here("PWD");
  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 3.30" << endl;
  try{
    irospilot.setBaseDir(dtemp);  
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting setting IrosPilot base dir" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting setting IrosPilot base dir" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting setting IrosPilot base dir" << endl;
  }
  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 3.5" << endl;

  try{
    sf = mysystem.getEnvVar(here) ; 
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting PWD env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting PWD env var" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchIrosV4() : errror in getting PWD env var" << endl;
  }

  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 4" << endl;
  // create attitude datacard and launch attitude correction
  // to produce dataset L3 file
  // filling a filelist 
  // containing input files to be processed
  try{
    srcx.fillFilelist(ff);
  // create attitude datacard
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchIrosV4() : errror in filling the filelist datacard" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchIrosV4() : errror in filling the filelist datacard" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchIrosV4() : errror in filling the filelist datacard" << endl;
  }

  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 5" << endl;
	// create datacard

  try{
    srcx.createDefaultAttitudeDatacard(l2fn, att, l3outf);
  } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchIrosV4() : errror in creating the attitude datacard" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchIrosV4() : errror in creating the attitude datacard" << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchIrosV4() : errror in creating the attitude datacard" << endl;
  }
  // remember to adapt


//./launchIros "/home/lazza/.MD_IROS_Pilot_v4" "/home/lazza/projects/attitude_launcher/MD_IROS_Pilot_v4_test_0" "iros_out.log" "thisprefix"
//  srcx.launchIros(const string &mapdir, const string &pilotfile, const string &pointpilotfile);


	// remove temp files
  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 6" << endl;
  try{ 
    ss.str(""); ss << irospilot.getBaseDir() << "/attitude/version_for_sasoa/analisi/mdmap_tmp"; 
    string adf = "rm -rf " + ss.str(); system(adf.c_str());
    string hfh("rm -f ei_outfile_L3.evt"); system(hfh.c_str());
    string bfh("rm -f ei_sapoifile.fits"); system(bfh.c_str());
    string tfh("rm -f ag3914_sal3_bti.fits"); system(tfh.c_str());
  } catch (const exception &e){
    cerr << "errror in removing temp files" << e.what() << endl;
  }catch (...){
    cerr << "errror in removing temp files" << endl;
  }

  //---------------------------------------------------------------> 

  // launch  generation of attitude corrected L3 data file
  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 7: going to exec attitude correction " << endl;

try { 
  	system(bb.c_str());
 } catch (const SAexception &se){
    cerr << "SourcesExtractor::launchIrosV4() : exception occurred in executing attitude correction " << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchIrosV4() : exception occurred in executing attitude correction " << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchIrosV4() : exception occurred in executing attitude correction " << endl;
  }

  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 8: going to exec mdmap creation correction " << endl;

  string mymapdir("");  string mymapfilename;  string mypilotfile;
  string myiroslogfilename; string myprefix; 
  string mypointpilotfile; //<-- testing 28/05/2008
  string hj("HOME");
  string homevar = mysystem.getEnvVar(hj);
  mypointpilotfile = homevar + "/.MD_IROS_Point_Pilot_v4";  
  //launchIros "/home/lazza/.MD_IROS_Pilot_v4" "/home/lazza/.MD_IROS_Point_Pilot_v4" "iros_out.log" "thisprefix"
   string catalogname("integral2006_catalog.txt");
   irospilot.setPointPilotFilename(mypointpilotfile);
   irospilot.createPointingPilot(mypointpilotfile, catalogname);
   string mtst, mrsr, sff;

try{
    mtst = "SASOA_LIB";    sf = mysystem.getEnvVar(mtst); 
    mtst = "PWD";    sff = mysystem.getEnvVar(mtst);
    mypointpilotfile = sf + "/../.MD_IROS_Point_Pilot_v4"; //<-- cambiare
 
    ss.str(""); ss << sf << "/../createIrosMDMap" << " " << sff << "/outL3.evt" << " " << "mdmap_tmp" << " " << 20 << " " << 55 << endl;
    if (verbose) cout << "executing " << ss.str() << endl;
    mrsr = ss.str(); mysystem.execCommand(mrsr);    ss.str("");
}  catch (const SAexception &se){
    cerr << "SourcesExtractor::launchIrosV4() : exception occurred in creating mdmap & histograms " << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "SourcesExtractor::launchIrosV4() : exception occurred in creating mdmap & histograms " << e.what() << endl;
  }catch (...){
    cerr << "SourcesExtractor::launchIrosV4() : exception occurred in creating mdmap & histograms " << endl;
  }

  if (verbose) cout << "SourcesExtractor::launchIrosV4() here 8: going to perform iros processing " << endl;



try { 
  char i=0; string thtk;
  while(i<4){ 
    //ss.str(); ss << "mkdir "<< irospilot.getBaseDir() << "/thisdir" << endl;
    //thtk = ss.str(); mysystem.execCommand(thtk);
    ss.str("");ss << "outL3_D"<< int(i) <<".imdmap"; 
    mymapfilename = ss.str();
    irospilot.setFileName(mymapfilename);
    ss.str("");ss << sf << "/../";
    mypilotfile = ss.str() + "MD_IROS_Pilot_v4_test";
    ss.str("");ss << "_" << int(i); 
    mypilotfile += ss.str();
    myiroslogfilename = "iros_out";
    ss.str("");ss << "_" << int(i)<< ".log"; 
    myiroslogfilename += ss.str(); irospilot.setLogfileName(myiroslogfilename);
    myprefix = "thisprefix";
    ////ss.str("");ss << "_" << int(i); 
    //myprefix += ss.str(); 
    irospilot.setOutfilePrefix(myprefix);
    irospilot.createPilot(i, mypilotfile);
    //ss.str("");ss << sf << "/../" << irospilot.getPilotFilename(); 
    //mypilotfile = ;irospilot.setPilotFilename(mypilotfile);
    irospilot.launchIros(i++);
  }
 } catch (const SAexception &se){
    cerr << "attlaunch: exception occurred in running iros " << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "attlaunch: exception occurred in running iros " << e.what() << endl;
  }catch (...){
    cerr << "attlaunch: exception occurred in running iros " << endl;
  }

  ark.deliveryIrosProducts(myprefix);

  cout << "bye, bye."<< endl;
  system("date");


}

/** No descriptions */
void SApipeline::SourcesExtractor::launchIros(){
  if (verbose) cout << "SourcesExtractor::launchIros() started "<< endl;
    if (commandlist.getIrosMode()) system("./launchIROS.bash");
    else cout << "omitting launching iros"<< endl; 
  if (verbose) cout << "SourcesExtractor::launchIros() ended "<< endl;
}
/** No descriptions */
void SApipeline::SourcesExtractor::createIrosBatch(byte det){
  ofstream of;  string fn;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
            fn = arc->getSasoaHome() + "/stg_2/.MD_IROS_Pilot";
            if (verbose) cout << "SourcesExtractor::createIrosBatch() on file "<< fn << endl;
            of.open (fn.c_str(), ofstream::out | ofstream::trunc);
            of << ";#####################################################" << endl;
            of << ";# This is a sample pilot file for the MD_IROS" << endl;
            of << ";# For the SuperAGILE pipeline SASOA " << endl;
            of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
            of << ";#####################################################" << endl;
            of << "BASE_DIR    = "<<arc->getSasoaHome()<<"/stg_2/	      ; Base directory" << endl;
             if (verbose) cout << "SourcesExtractor::createIrosBatch() BASE_DIR    = "<<irospilot.getBaseDir()<<"	      ; Base directory" << endl;
            of << "FILE	    = "+irospilot.getFileName()+"    ; Input file name " << endl;
             if (verbose) cout << "SourcesExtractor::createIrosBatch() iros PilotFile name    = "<<irospilot.getFileName()<<"	      ; Base directory" << endl;         
          of << "DETECTOR    = "<<  int(det)  <<"			          ; -- Detector number" << endl;
          of << "LAD_GAP	    = 18			       ; Gap between ladders" << endl;
          of << "GAP_START   = 767			   ; Strip No. after gap" << endl;
          of << "MAX_ROUNDS  = 5				   ; No. of IROS rounds" << endl;
          of << "MIN_SIGMAS  = 4.5		       ; Number of STDs." << endl;
          of << "USE_CAT	    = 0 			          ; Set to 1 if catalog is to be used. " << endl;
			of <<"USE_DEFF_MASK = 1     ; 1 to use efficiency arrays" << endl;
			of <<"DEFF_MASK_NAME  = "<< arc->getSasoaHome() <<"/stg_2/DEff_Mask_updated_070704.eff"<< endl;
			of <<"SAFE_MODE   = 1        ; 1 if to use a safe mode"<< endl;
			of <<"S_MODE_LEVEL = 0.01 ; Fractional change of chi2 in safe mode"<< endl;
			of <<"GROUND_MASK  = 0    ; Set to 1 if need to use magnified array"<< endl;
			of <<"BKGR_MODEL   = 2    ; 1, 2, etc. for different BKGR models"<< endl;
          of.close();
      } catch (ofstream::failure e)      {
        cout << "SourcesExtractor::SourcesExtractor::createIrosBatch() Exception opening/writing file"<< e.what() << endl;    
      }
}
/** No descriptions */
void SApipeline::SourcesExtractor::createPointingBatch(){
   tempstring2 = "../stg_2/attitude/version_for_sasoa/bin/prova_outfile_L3.evt";
    sal3.init();
    sal3.setInputFilename(tempstring2);string hdn0("PACKETS"); 
    string hdn("EVENTS");  
try{
    sal3.readHeaders(hdn0);
} catch (const exception &e){
	cerr << "createPointingBatch() error in reading the l3 evlist header" << e.what() << endl;
} catch (...){
	cerr << "createPointingBatch() error in reading the l3 evlist header" << endl;
}
    ofstream of;  string fn;
    stringstream ss; string ts;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
        fn = arc->getSasoaHome() + "/stg_2/.MD_IROS_Point_Pilot";
        if (verbose) cout << "SourcesExtractor::createIrosBatch() iros point pilot file name =  "<< fn << endl;
        of.open (fn.c_str(), ofstream::out | ofstream::trunc);
        of << ";#####################################################" << endl;
        of << ";# This is a sample pointing pilot file for the MD_IROS" << endl;
        of << ";# For the SuperAGILE pipeline SASOA " << endl;
        of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
        //of << ";# "+tmr.getDateString() << endl;
        of << ";#####################################################" << endl;
        of << "CATALOG_DIR  = "<<arc->getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
        if (verbose) cout << "SourcesExtractor::createIrosBatch() CATALOG_DIR  = "<<arc->getSasoaHome()<<"/stg_2/catalog/     ; Catalog repository " << endl;
        of << "CATALOG_NAME  =  integral2006_catalog.txt    ; Catalog Name " << endl;
        ss.str("");ss << sal3.sapoint.getAlfa(); ts = ss.str();  
        of << "ALFA = "+ts+"            ; Alfa 2000 in radians " << endl;
        ss.str("");ss << sal3.sapoint.getDelta(); ts = ss.str();        
        of << "DELTA = "+ts+"           ; Delta 2000 in radians " << endl;
        ss.str("");ss << sal3.sapoint.getRoll(); ts = ss.str(); 
        of << "ROLL = "+ts+"            ; Roll in radians  " << endl;
        of.close();
  } catch (ofstream::failure e)  {
        cout << "SourcesExtractor::createIrosBatch() Exception opening/writing file"<< e.what()<< endl;
  }
}

void SApipeline::SourcesExtractor::createPointingBatch(const string &templ3){

    sal3.init();
    sal3.setInputFilename(templ3);string hdn0("PACKETS"); 
    string hdn("EVENTS");  
try{
    sal3.readHeaders(hdn0);
} catch (const exception &e){
	cerr << "createPointingBatch() error in reading the l3 evlist header" << e.what() << endl;
} catch (...){
	cerr << "createPointingBatch() error in reading the l3 evlist header" << endl;
}
    ofstream of;  string fn;
    stringstream ss; string ts;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
        fn = arc->getSasoaHome() + "/stg_2/.MD_IROS_Point_Pilot";
        if (verbose) cout << "SourcesExtractor::createIrosBatch() iros point pilot file name =  "<< fn << endl;
        of.open (fn.c_str(), ofstream::out | ofstream::trunc);
        of << ";#####################################################" << endl;
        of << ";# This is a sample pointing pilot file for the MD_IROS" << endl;
        of << ";# For the SuperAGILE pipeline SASOA " << endl;
        of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
        //of << ";# "+tmr.getDateString() << endl;
        of << ";#####################################################" << endl;
        of << "CATALOG_DIR  = "<<arc->getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
        if (verbose) cout << "SourcesExtractor::createIrosBatch() CATALOG_DIR  = "<<arc->getSasoaHome()<<"/stg_2/catalog/     ; Catalog repository " << endl;
        of << "CATALOG_NAME  =  integral2006_catalog.txt    ; Catalog Name " << endl;
        ss.str("");ss << sal3.sapoint.getAlfa(); ts = ss.str();  
        of << "ALFA = "+ts+"            ; Alfa 2000 in radians " << endl;
        ss.str("");ss << sal3.sapoint.getDelta(); ts = ss.str();        
        of << "DELTA = "+ts+"           ; Delta 2000 in radians " << endl;
        ss.str("");ss << sal3.sapoint.getRoll(); ts = ss.str(); 
        of << "ROLL = "+ts+"            ; Roll in radians  " << endl;
        of.close();
  } catch (ofstream::failure e)  {
        cout << "SourcesExtractor::createIrosBatch() Exception opening/writing file"<< e.what()<< endl;
  }
}
/** No descriptions */
void SApipeline::SourcesExtractor::rmTempInputFiles(){
   arc->clear_L2_Data();
}
/** No descriptions */
void SApipeline::SourcesExtractor::saveIrosMap(){

  ss.str("");
  if (verbose) cout << "SourcesExtractor::launchIrosMapBuilder() started"<< endl;
  if (!commandlist.isPathAbsolute()){
          if (verbose) cout << "selected path type is auto generated"<< endl;
          tempstring =  getInputDataPath()+"/L3";
          if (verbose) cout << "filename = " +retrieveFilename("evt", tempstring, 1) << endl;
          cout << "SourcesExtractor::launchIrosMapBuilder() filename='" << retrieveFilename("evt", tempstring, 1 ) << "'" << endl;
  }  else {
          if (verbose) cout << "selected path type is absolute"<< endl;
          cout << "SourcesExtractor::launchIrosMapBuilder() filename='" << commandlist.getInputFilename() << "'" << endl;
  }
  ss <<  retrieveFilename("evt", tempstring, 1 );
  cout << "created the string " << ss.str() << endl;
  fitsfilename =  ss.str();
  sal3.init();
  sal3.setInputFilename(fitsfilename);
  string hdn("EVENTS");  string fn(fitsfilename);
  cout << "read dim = " << sal3.getInputDimension() << endl;
  sal3.readHeaders(hdn);
  sal3.read(fn);
  sal3.getAllDetImages();
  sal3.setIrosMapData();
  IrosMap imp(sal3);
  imp.getL3EvlistData();  imf2 = "test2.dat";
  imp.saveBinary(imf2);
  if (verbose) cout << "SourcesExtractor::launchIrosMapBuilder() ended"<< endl;

}

/** No descriptions */
void SApipeline::SourcesExtractor::setIrosMapFileName(const string &fn){
  tempstring1 = fn.substr(0, fn.find_last_of("/")); 
  cout << "SourcesExtractor::setIrosMapFileName() path = " << tempstring1 << endl;
  tempstring2 = fn.substr(fn.find_last_of("/")+1, -1);
  cout << "SourcesExtractor::setIrosMapFileName() filename = " << tempstring2 << endl;
  irosmapfilename = fn;
  // copy MultiD file in the base dir
  tempstring = "cp "+fn+" "+irospilot.getBaseDir();
  cout << "SourcesExtractor::setIrosMapFileName() executing string " << tempstring << endl;
  syscon.execCommand(tempstring);
  // set the Base Dir

  irospilot.setFileName(tempstring2);
    
  // set the filename... 
}
        /** No descriptions */
string SApipeline::SourcesExtractor::getIrosMapFileName(){
  return irosmapfilename;
}
/** No descriptions */
void SApipeline::SourcesExtractor::showPointingBatch(){
  cout << "SourcesExtractor::showPointingBatch() start"<< endl;
  printPointingBatch(cout);
  cout << "SourcesExtractor::showPointingBatch() stop"<< endl;
}
/** No descriptions */
void SApipeline::SourcesExtractor::showIrosBatch(){
  cout << "SourcesExtractor::showIrosBatch() start"<< endl;
  printIrosBatch(cout);
  cout << "SourcesExtractor::showIrosBatch() stop"<< endl;
}
/** No descriptions */
void SApipeline::SourcesExtractor::printPointingBatch(ostream &os){
      try {
        os << ";#####################################################" << endl;
        os << ";# This is a sample pointing pilot file for the MD_IROS" << endl;
        os << ";# For the SuperAGILE pipeline SASOA " << endl;
        os << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
        os << ";# "+tmr.getDateString() << endl;
        os << ";#####################################################" << endl;
        os << "CATALOG_DIR  = "<<arc->getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
        cout << "SourcesExtractor::createIrosBatch() CATALOG_DIR  = "<<arc->getSasoaHome()<<"/catalog/     ; Catalog repository " << endl;
        os << "CATALOG_NAME  =  integral2006_catalog.txt    ; Catalog Name " << endl;
        ss.str("");  ss << sal3.sapoint.getAlfa(); ts = ss.str();
        os << "ALFA = "+ts+"            ; Alfa 2000 in radians " << endl;
        ss.str(""); ss << sal3.sapoint.getDelta(); ts = ss.str();
        os << "DELTA = "+ts+"           ; Delta 2000 in radians " << endl;
        ss.str(""); ss << sal3.sapoint.getRoll(); ts = ss.str();
        os << "ROLL = "+ts+"            ; Roll in radians  " << endl;
  } catch (ostream::failure e)  {
    cerr << e.what();
        cerr << " printPointingBatch()  Exception opening/writing file"<< e.what()<< endl;
  }
}
/** No descriptions */
void SApipeline::SourcesExtractor::printIrosBatch(ostream &os){
    string fn;
      try {
            fn = getIrosBaseDir()+"/.MD_IROS_Pilot";
            os << ";#####################################################" << endl;
            os << ";# This is a sample idl batch file for the MD_IROS" << endl;
            os << ";# For the SuperAGILE pipeline SASOA " << endl;
            os << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
            os << ";# "+tmr.getDateString() << endl;
            os << ";#####################################################" << endl;
      } catch (ostream::failure e)      {
        cerr << "SourcesExtractor::printIrosBatch() Exception opening/writing file"<< e.what()<< endl;
      }
}
/** No descriptions */
void SApipeline::SourcesExtractor::createIrosIDLBatch(const string &fn){
    ofstream of;  string hhh("..");
	arc->setSasoaHome(hhh);
    cout << "SourcesExtractor::createIrosIDLBatch() on file " << fn << endl;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
        of.open (fn.c_str(), ofstream::out | ofstream::trunc);
        of << ";#####################################################" << endl;
        of << ";# This is a sample pointing pilot file for the MD_IROS" << endl;
        of << ";# For the SuperAGILE pipeline SASOA " << endl;
        of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
        of << ";# "+tmr.getDateString() << endl;
        of << ";#####################################################" << endl;
        of << ".run drive_MD_IROS_v3.pro"  << endl;
        of << ".run drive_MD_IROS_v3.pro"  << endl;
		cout << "getSasoaHome() = "<< getSasoaHome() << endl;
		cout << "arc->getSasoaHome() = "<< arc->getSasoaHome() << endl;
        of <<"drive_MD_IROS_v3, VERBOSE_FILE="+getIrosLogFileName()+",  INPUT_PILOT_FILE=\"" +arc->getSasoaHome()+"/stg_2/.MD_IROS_Pilot\", INPUT_POINT_PILOT_FILE=\""+arc->getSasoaHome()+"/stg_2/.MD_IROS_Point_Pilot\""+", FITS_FILES_PREFIX = \""+arc->filenamer.getNameRoot()+"\"" << endl;
        of <<"exit" << endl;
        of.close();
  } catch (ofstream::failure e)  {
    cerr << e.what();
        cerr << "SourcesExtractor::createIrosIDLBatch() Exception opening/writing file"<< e.what() << endl;
  }

}
/** No descriptions */
void SApipeline::SourcesExtractor::setIROS_IDLBatchFileName(const string &fn){
  iros_idl_batch_fn = fn;
}
/** No descriptions */
string SApipeline::SourcesExtractor::getIROS_IDLBatchFileName(){
  return iros_idl_batch_fn;
}
/** No descriptions */
string SApipeline::SourcesExtractor::getIrosLogFileName(){
  try{
    ss.str("");  ss << int(irospilot.getDetector());
    tempstring =  ss.str();
    iroslogfilename = "\"iros_log_det"+tempstring+".txt\"";
  } catch (...){
    cerr << "SourcesExtractor::getIrosLogFileName() error "<< endl;
  }
    return iroslogfilename;
}


/*!
    \fn SApipeline::SourcesExtractor::retrieveIrosMapFilename()
 */
string SApipeline::SourcesExtractor::retrieveIrosMapFilename()
{
    SATask tt = IrosMapBuilding; 
    tempstring = filenamer.getFileName(tt);
    return tempstring;
}

/*!
    \fn SApipeline::SourcesExtractor::setIrosBaseDir()
 */
void SApipeline::SourcesExtractor::setIrosBaseDir(const string &ibd)
{
  irospilot.setBaseDir(ibd);
}


/*!
    \fn SApipeline::SourcesExtractor::getIrosBaseDir()
 */
string SApipeline::SourcesExtractor::getIrosBaseDir()
{
  return irospilot.getBaseDir();    
}


/*!
    \fn SApipeline::SourcesExtractor::setDefault()
 */
void SApipeline::SourcesExtractor::setDefault()
{
  try{
    irosmapfilename = "../stg_2/default_im_fn.dat";
    iroslogfilename = "default_iroslog.txt";
    iros_idl_batch_fn = getSasoaHome()+"/stg_2/IROS_Multi-D/launchIrosIDLBatch";  
  } catch (...){
    cerr << "SourcesExtractor::setDefault() " << endl;
    throw e;
  }
}


/*!
    \fn SApipeline::SourcesExtractor::passIrosMap()
 */
void SApipeline::SourcesExtractor::passIrosMap()
{
  ArchiveHandler *arc2 = new ArchiveHandler();
  cout << "SourcesExtractor::passIrosMap() moving irosmap file " << irospilot.getFileName() << endl;
  cout << "SourcesExtractor::passIrosMap() to dir " << irospilot.getBaseDir() << endl;
  arc2->moveFile(irospilot.getFileName(), irospilot.getBaseDir());
  delete arc2;
}
void SApipeline::SourcesExtractor::passIrosMap(const string &mapfilename, const string &destdir)
{
  ArchiveHandler *arc2 = new ArchiveHandler();
  cout << "SourcesExtractor::passIrosMap() moving irosmap file " << irospilot.getFileName() << endl;
  cout << "SourcesExtractor::passIrosMap() to dir " << irospilot.getBaseDir() << endl;
  arc2->moveFile(mapfilename, destdir);
  delete arc2;
}
/** No descriptions */
string SApipeline::SourcesExtractor::getInputFileName(){
    return arc->filenamer.getInputFileName(SourcesExtraction);
}

/** No descriptions */
string SApipeline::SourcesExtractor::getAbsoluteInputFileName(){
    tempstring = arc->get_L2_Dir(); tempstring += "/";
    tempstring += arc->filenamer.getInputFileName(SourcesExtraction);
    return tempstring;
}
/** No descriptions */
string SApipeline::SourcesExtractor::getDefaultInputDir(){
  return  arc->get_L2_Dir();
}
/** No descriptions */

/** No descriptions */
void SApipeline::SourcesExtractor::launchIrosMapBuilder(bool debug){
  try{
        if (debug){
           system("./sasoa_0_0_6 -b \"create_irosmap /home/agile/SASOA/SA/data/L3/prova_outfile_L3.evt\"");
        } else {
         launchIrosMapBuilder(); 
        }
        
  } catch (...) {
    cerr << "SourcesExtractor::launchIrosMapBuilder() error: general exception "  << endl;
  }
}


/*!
    \fn SApipeline::SourcesExtractor::createExposureBatch()
 */
void SApipeline::SourcesExtractor::createExposureBatch()
{
    ofstream of;  string fn;
    stringstream ss; string ts;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
        fn =   "./launchExposure.bash";
    of.open (fn.c_str(), ofstream::out | ofstream::trunc);
	of << "#!/bin/sh" << endl;
	of << "cd ../stg_2/EXP_DELIVERY" << endl;
	of << "idl exposure_idl_batch" << endl;
	of << "exit" << endl;
        of.close();
  } catch (ofstream::failure e)  {
        cerr << "SourcesExtractor::createExposureBatch() Exception opening/writing file"<< e.what()<< endl;
  }
}

/*!
    \fn SApipeline::SourcesExtractor::createExposureDatacard()
 */
void SApipeline::SourcesExtractor::createExposureDatacard()
{
	cout << "SourcesExtractor::createExposureDatacard() start"  << endl;
    ofstream of;  string fn("../stg_2/EXP_DELIVERY/testcard.card");
    stringstream ss; string ts;
	of.setf(ios::fixed,ios::floatfield);
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
    of.open (fn.c_str(), ofstream::out | ofstream::trunc);
	tempstring = arc->getAttitudeDir();
	tempstring2 = arc->get_SAL1Cor_Dir(); 
	tempstring3 = arc->getExposureDir();
	of << "SAPOI_FILE         '../attitude/version_for_sasoa/testfiles/sapoi_sasoa.fits'" << endl;
	of << "AG3914_FILE        '"<<tempstring2 << "/" << arc->getLoaded3914FileName() <<"'" << endl;
	of << "AG3916_FILE        '"<<tempstring2 << "/"	<< arc->getLoaded3916FileName()<<"'" << endl;
	of << "EARTHGTI_FILE      'EARTH_OCCULTATION.gti'" << endl;
	of << "EXPMODE            'field'" << endl;
	of << "TSTART_S            '"<<getTstart() <<"'" << endl;
	of << "TSTOP_S             '"<<getTstop() <<"'" << endl;
	of << "EXPOSURE_BOX_SUCCESS_FILE 'exp_box_file'" << endl;
    of.close();
  } catch (ofstream::failure e)  {
        cerr << "SourcesExtractor::createExposureDatacard() Exception opening/writing file"<< e.what() << endl;
  }
	  cout << "SourcesExtractor::createExposureDatacard() end"  << endl;
}


/*!
    \fn SApipeline::SourcesExtractor::launchExposureIDLBatch()
 */
void SApipeline::SourcesExtractor::launchExposureIDLBatch()
{
    tempstring.assign("./launchExposure.bash");
    syscon.execCommand(tempstring);
}


/*!
    \fn SApipeline::SourcesExtractor::launchExposure()
 */
void SApipeline::SourcesExtractor::launchExposure()
{
	try{
    tempstring.assign("./launchExposure.bash");
    syscon.execCommand(tempstring);
	} catch(...){
		cerr << "SourcesExtractor::launchExposure() error in launching the exposure GTI calculatiion "<< endl;
	}
}


/*!
    \fn SApipeline::SourcesExtractor::launchSaga()
 */
void SApipeline::SourcesExtractor::launchSaga()
{
	try{
    tempstring.assign("./launchSaga.bash");
    syscon.execCommand(tempstring);
	} catch(...){
		cerr << "SourcesExtractor::launchSaga() error in launching the exposure GTI calculatiion "<< endl;
	}
}

/*!sasoa_0_0_6/launchSaga.bash
    \fn SApipeline::SourcesExtractor::createSagaBatch()
 */
void SApipeline::SourcesExtractor::createSagaBatch()
{
    ofstream of;  string fn;
    fn =   "./launchSaga.bash";
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
    try {
    	of.open (fn.c_str(), ofstream::out | ofstream::trunc);
		of << "#!/bin/sh" << endl;
		of << "cd ../stg_2/sagagti" << endl;
		of << "idl sagagti_idl_batch" << endl;
		of << "exit" << endl;
    	of.close();
  	} catch (ofstream::failure e)  {
    	cerr << e.what();
        cerr << "SourcesExtractor::createSagaBatch() Exception opening/writing file"<< e.what() << endl;
  	}
}

/*!
    \fn SApipeline::SourcesExtractor::createSapoiLaunchBatch()
 */
void SApipeline::SourcesExtractor::createSapoiLaunchBatch()
{
    ofstream of;  string fn;
	string dir(arc->getAttitudeDir());
	cout << "SourcesExtractor::createSapoiLaunchBatch() attitude proc. base dir " << dir << endl;
	dir+="/src";
    stringstream ss; string ts;
        fn =   "./launchSapoi.bash";
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
    of.open (fn.c_str(), ofstream::out | ofstream::trunc);
	of << "#!/bin/sh" << endl;
	of << "rm ../stg_2/attitude/version_for_sasoa/testfiles/sapoi_sasoa.fits " << endl;
	of << "cd " << dir << endl;
	of << "../bin/quat_to_sapoi.exe ../datacards/quat_to_sapoi_fixed-time.card" << endl;
	of << "exit" << endl;
        of.close();
  } catch (ofstream::failure e)  {
        cerr << "SourcesExtractor::createSapoiLaunchBatch() Exception opening/writing file "<< e.what() << endl;
  }
}

void SApipeline::SourcesExtractor::launchSapoiCreator(){
	try{
	tempstring.assign("rm ");tempstring.append(arc->getAttitudeDir());tempstring.append("/testfiles/sapoi_sasoa.fits");
    syscon.execCommand(tempstring);
    tempstring.assign("./launchSapoi.bash");
    syscon.execCommand(tempstring);
	} catch(...){
		cerr << "SourcesExtractor::launchSapoiCreator() error in calculating exposure GTI"<< endl;
	}

}
void SApipeline::SourcesExtractor::createSapoiDatacard(){
if (verbose) cout << "[stage 2] SourcesExtractor::createSapoiDatacard" << endl;
if (verbose) cout << "SourcesExtractor::createSapoiDatacard() inputfilename to write in the sapoi datacard is "<< commandlist.getInputFilename()  << endl;;
ofstream outfile;
outfile.open ("../stg_2/attitude/version_for_sasoa/datacards/quat_to_sapoi_fixed-time.card", ofstream::out | ofstream::trunc);
outfile << "################################################################"<< endl;
outfile << "#" << endl;
outfile << "#   L. Pacciani                                            F. Lazzarotto"<< endl;
outfile << "#   30/5/2006                                            15/07/2007     "<< endl;
outfile << "#   "+tmr.getDateString() << endl;
outfile << "#   luigi.pacciani@iasf-roma.inaf.it                    francesco.lazzarotto@iasf-roma.inaf.it"<< endl;
outfile << "#"<< endl;
outfile << "# input example for quat_to_sapoi "<< endl;
outfile << "#"<< endl;
outfile << "# this file is automatically generated by sasoa"<< endl;
outfile << "#"<< endl;
outfile << "###############################################################"<< endl;
outfile << "# syntax:"<< endl;
outfile << "#"<< endl;
outfile << "# KEYWORD 'value'    /comment"<< endl;
outfile << "#"<< endl;
outfile << "# The symbol  #  at the start of the line"<< endl;
outfile << "# is aimed to comment the line"<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# SA Pointing output file ."<< endl;
string ts; ts = getSasoaWorkDir()+"/data/L1";
commandlist.setDefaultInDir(ts);

tempstring = "SAPOI_FILE   '../testfiles/sapoi_sasoa.fits'";  

if (verbose) cout <<"SourcesExtractor::createSapoiDatacard() going to write the following instruction"<< endl;
cout << "" << tempstring << endl;
outfile << tempstring << endl;
outfile << "#FINE: lista dei ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# file list 39.14 per i quaternioni"<< endl;
outfile << "# the list has to be time ordered "<< endl;
outfile <<  endl;
outfile <<  "AG3914   '"<< arc->get_L1_Dir()+"/"+arc->getLoaded3914FileName() << "'"<< endl;
outfile << "#END: 39.14 file list ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# DTMAX_NOATT_S definisce l'intervallo di tempo massimo accettabile (in secondi)"<< endl;
outfile << "#               di buco tra dati consecutivi di attitude contenuti"<< endl;
outfile << "#               nei file 39.14."<< endl;
outfile << "#"<< endl;
outfile <<  endl;
outfile << "DTMAX_NOATT_S  '2.'"<< endl;
outfile <<  endl;
outfile << "#FINE: DTMAX_NOATT_S definisce ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# lista file con i good time intervals"<< endl;
outfile <<  endl;
outfile << "#GTI   'mygti.fits'"<< endl;
outfile <<  endl;
outfile << "#FINE: lista file con i good ... "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################"<< endl;
outfile << "# si puo' dare uno start ed uno stop"<< endl;
outfile << "# with following  KEYWORD"<< endl;
outfile << "# the time unit is seconds, time origin is defined by Chen "<< endl;
outfile << "################################################################"<< endl;
outfile <<  endl;
outfile << "OPEMODE            'fixed-time'"<< endl;
outfile << "CELL_RANGE_RAD     '0.004'"<< endl;
outfile << "RANGE_POI_CUT_RAD  '0.035'"<< endl;
outfile << "RANGE_SLEW_CUT_RAD '0.053'"<< endl;
outfile <<  endl;
outfile << "#END: se i file con le gti ...  "<< endl;
outfile << "################################################################ "<< endl;
outfile <<  endl;
outfile <<  endl;
outfile << "TSTEP_S  '600.'       /step "<< endl;
outfile << "#END of the datacard "<< endl;
outfile << "#################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile.close(); 
}

/*!
    \fn SApipeline::SourcesExtractor::createSagaIDLBatch()
 */
void SApipeline::SourcesExtractor::createSagaIDLBatch()
{
   ofstream of; string fn("../stg_2/sagagti/sagagti_idl_batch");
    cout << "SourcesExtractor::createIrosIDLBatch() on file " << fn << endl;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
        of.open (fn.c_str(), ofstream::out | ofstream::trunc);
        of << ";#####################################################" << endl;
        of << ";# This is the launcher file for SAGA GTI calculator" << endl;
        of << ";# For the SuperAGILE pipeline SASOA " << endl;
        of << ";# by Imma Donnarumma & Francesco Lazzarotto " << endl;
        of << ";# "+tmr.getDateString() << endl;
        of << ";#####################################################" << endl;
		of << ".run sagagti_soe.pro" << endl;
		of << "sagagti_soe, '"<<arc->getCurrentSOE_Name()<<"'" << endl;
//		of << "sagagti_soe, 'agile_2007_157_09_34.SOE'" << endl;
		of << "exit" << endl;
        of.close();
  } catch (ofstream::failure e)  {
         cerr << "SourcesExtractor::createSagaIDLBatch() Exception opening/writing file"<< e.what() << endl;
  }
}
void SApipeline::SourcesExtractor::createAttitudeBatchScript(){
    ofstream of;  string fn;
	string dir(arc->getAttitudeDir());
	cout << "SourcesExtractor::createAttitudeBatchScript() attitude proc. base dir " << dir << endl;
	dir+="/src";
    stringstream ss; string ts;
        fn =   "launchSourcesExtraction.bash";
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
    of.open (fn.c_str(), ofstream::out | ofstream::trunc);
	of << "#!/bin/sh" << endl;
	of << "rm ../stg_2/attitude/version_for_sasoa/bin/prova_outfile_L3.evt " << endl;
	of << "cd " << dir << endl;
	of << "../script/run_sal2_to_l3 ../datacards/datacard_new.card" << endl;
	of << "exit" << endl;
        of.close();
  } catch (ofstream::failure e)  {
        cerr << "SourcesExtractor::createAttitudeBatchScript() Exception opening/writing file "<< e.what() << endl;

}
}
/*!
    \fn SApipeline::SasoaHandler::createAttitudeDatacard()
 */
void SApipeline::SourcesExtractor::createAttitudeDatacard(){
try{
if (verbose) cout << "[stage 2] SourcesExtractor:::createAttitudeDatacard()" << endl;
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
outfile.open ("../stg_2/attitude/version_for_sasoa/datacards/datacard_new.card", ofstream::out | ofstream::trunc);
if (commandlist.isPathAbsolute()){
    tempstring = "L2EVL   '"+commandlist.getInputFilename()+"'";  
    cout << "executing path absolute" << endl;
} else {
  tempstring = "L2EVL   '"+arc->get_L2_Dir()+"/"+commandlist.getInputFilename()+"'";
    cout << "executing with path not absolute" << endl;
}
outfile << tempstring << endl;
outfile << "L3EVL '../bin/prova_outfile_L3.evt'"<< endl;
outfile <<  "AG3914   '"<< arc->get_SAL1Cor_Dir() +"/"+commandlist.getAttitudeFileName() << "'"<< endl; 

outfile << "#T0_QUAT_S '+1451606400.'       /per usare 39.14 non corretti insieme ai sal3"<< endl;
ss.setf(ios::fixed,ios::floatfield);
ss.str("");ss<<getTstart();tempstring2 = ss.str();
tempstring.assign("TSTART_S '");tempstring.append(tempstring2);tempstring.append("'"); 
outfile << tempstring << endl;
ss.str("");ss<<getTstop();tempstring2 = ss.str();
tempstring.assign("TSTOP_S '");tempstring.append(tempstring2);tempstring.append("'"); 
outfile << tempstring << endl;
outfile << "AVOID_TIMEREF_CHECK 'dummy'    /scommentare per usare 39.14 non corretti insieme ai sal3"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile.close();  
} catch(const exception &e) {
	cerr << "error in creating attitude datacard " << e.what() << endl;
} catch (...) {
	cerr << "error in creating attitude datacard "  << endl;
}
}

// function that creates the attitude correction program input datacard
// takes in input (1) datacard file name, (2) L2 eventlist filename, (3) attitude data L1 [3914] filename (4)L3 eventlist output filename
//
void SApipeline::SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f, const string &atf, const string &l3fn){
if (verbose) cout << "[stage 2] SourcesExtractor:::createAttitudeDatacard()" << endl;
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
try{
	outfile.open (dcfn.c_str(), ofstream::out | ofstream::trunc);
if (commandlist.isPathAbsolute()){
    tempstring = "L2EVL   '"+commandlist.getInputFilename()+"'";  
} else {
  ss.str("");ss<<"L2EVL   '"<<l2f<<"'";
  tempstring = ss.str();
}
outfile << tempstring << endl;
outfile << "L3EVL '" << l3fn << "'" << endl;
outfile <<  "AG3914   '"<< atf << "'"<< endl; 

outfile << "#T0_QUAT_S '+1451606400.'       /per usare 39.14 non corretti insieme ai sal3"<< endl;
ss.setf(ios::fixed,ios::floatfield);
ss.str("");ss<<getTstart();tempstring2 = ss.str();
tempstring.assign("TSTART_S '");tempstring.append(tempstring2);tempstring.append("'"); 
outfile << tempstring << endl;
ss.str("");ss<<getTstop();tempstring2 = ss.str();
tempstring.assign("TSTOP_S '");tempstring.append(tempstring2);tempstring.append("'"); 
outfile << tempstring << endl;
outfile << "AVOID_TIMEREF_CHECK 'dummy'    /scommentare per usare 39.14 non corretti insieme ai sal3"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile.close();

} catch(const exception &e) {
	cerr << "SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f) error in creating attitude datacard " << e.what() << endl;
} catch (...) {
	cerr << "SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f) error in creating attitude datacard "  << endl;
}
}



/** 
	create attitude corrected L3 file taking in input
	the l2 input filename, and the 3914 input filename and the 
	l3 output filename
*/

void SApipeline::SourcesExtractor::createDefaultAttitudeDatacard(const string &l2f, const string &atf, const string &l3f)
{
  ss.setf(ios::fixed,ios::floatfield);
try{
  if (verbose) cout << "[stage 2] SourcesExtractor:::createAttitudeDatacard()" << endl;
  ofstream outfile;
  string dcfn("attitude_datacard.txt");
  outfile.setf(ios::fixed,ios::floatfield);
  outfile.open (dcfn.c_str(), ofstream::out | ofstream::trunc);
if (commandlist.isPathAbsolute()){
    tempstring = "L2EVL   '"+commandlist.getInputFilename()+"'";  
} else {
  ss.str("");ss<<"L2EVL   '"<< l2f <<"'";
  tempstring = ss.str();
}
  outfile << tempstring << endl;
  outfile <<  "L3EVL '"<< l3f << "'"<< endl; 
  outfile <<  "AG3914   '"<< atf << "'"<< endl; 
  outfile << "#T0_QUAT_S '+1451606400.'       /per usare 39.14 non corretti insieme ai sal3"<< endl;
  ss.str("");ss<<getTstart();tempstring2 = ss.str();
  tempstring.assign("TSTART_S '");tempstring.append(tempstring2);tempstring.append("'"); 
  outfile << tempstring << endl;
  ss.str("");ss<<getTstop();tempstring2 = ss.str();
  tempstring.assign("TSTOP_S '");tempstring.append(tempstring2);tempstring.append("'"); 
  outfile << tempstring << endl;
  outfile << "AVOID_TIMEREF_CHECK 'dummy'    /scommentare per usare 39.14 non corretti insieme ai sal3"<< endl;
  outfile <<  endl;
  outfile <<  endl;
  outfile.close();  
} catch(const SAexception &se) {
	cerr << "SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f,  const string &l3f) error in creating attitude datacard " << se.getMsg() << endl;
} catch(const exception &e) {
	cerr << "SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f) error in creating attitude datacard " << e.what() << endl;
} catch (...) {
	cerr << "SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f) error in creating attitude datacard "  << endl;
}
}


/** 
	create attitude corrected L3 file taking in input
	the datacard filename, the l2 inputfile, and the 3914 inputfile
	
*/

void SApipeline::SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f, const string &atf){
try{
if (verbose) cout << "[stage 2] SourcesExtractor:::createAttitudeDatacard()" << endl;
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
outfile.open (dcfn.c_str(), ofstream::out | ofstream::trunc);
if (commandlist.isPathAbsolute()){
    tempstring = "L2EVL   '"+commandlist.getInputFilename()+"'";  
} else {
  ss.str("");ss<<"L2EVL   '"<<l2f<<"'";
  tempstring = ss.str();
}
outfile << tempstring << endl;
outfile << "L3EVL '../bin/prova_outfile_L3.evt'"<< endl;
outfile <<  "AG3914   '"<< atf << "'"<< endl; 

outfile << "#T0_QUAT_S '+1451606400.'       /per usare 39.14 non corretti insieme ai sal3"<< endl;
ss.setf(ios::fixed,ios::floatfield);
ss.str("");ss<<getTstart();tempstring2 = ss.str();
tempstring.assign("TSTART_S '");tempstring.append(tempstring2);tempstring.append("'"); 
outfile << tempstring << endl;
ss.str("");ss<<getTstop();tempstring2 = ss.str();
tempstring.assign("TSTOP_S '");tempstring.append(tempstring2);tempstring.append("'"); 
outfile << tempstring << endl;
outfile << "AVOID_TIMEREF_CHECK 'dummy'    /scommentare per usare 39.14 non corretti insieme ai sal3"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile.close();  
} catch(const exception &e) {
	cerr << "SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f) error in creating attitude datacard " << e.what() << endl;
} catch (...) {
	cerr << "SourcesExtractor::createAttitudeDatacard(const string &dcfn, const string &l2f) error in creating attitude datacard "  << endl;
}
}

/*!
    \fn SApipeline::SourcesExtractor::filterAllGTI(const string &gtifn);
 */
void SApipeline::SourcesExtractor::filterAllGTI(const string &gtifn)
{
  sal3.SAEventlist::setSaveFiltered(true);
  sal3.SAEventlist::setArchiveHandler(arc);
  sal3.filterAllGTI(gtifn);
}

/*!
    \fn SApipeline::SourcesExtractor::createFilteredL3List()
 */
void SApipeline::SourcesExtractor::createFilteredL3List()
{
    sal3.saveFiltered(arc->filenamer.getOutputFileName(AttitudeCorrection));
}
/** No descriptions */
void SApipeline::SourcesExtractor::deliverDetImages(){

  SAFileNamer sfn; sfn.setFileName(arc->filenamer.getFileName(OrbitRebuilding));
  string temps0 = sfn.getNameRoot();
  if (verbose) cout << "SourcesExtractor::deliverDetImages() base name for delivered files : " << temps0 << endl;
  if (verbose) cout << "SourcesExtractor::deliverDetImages() source file to copy" << endl;
  string sarg("ls -d saprod* ");
  FileList *soutfilelist = new FileList(sarg);
  soutfilelist->show();

  // create the file list with the destination files
  if (verbose) cout << "SourcesExtractor::deliverProducts() destinations " << endl;

  string sarg2 = "ls -d saprod* ";
  FileList *doutfilelist = new FileList(sarg2);
  doutfilelist->show();

  list<string>::iterator rit1 = soutfilelist->begin();

  while (rit1 != soutfilelist->end()) {
       tempstring = "mv -f "+(*rit1)+" "+getSasoaWorkDir()+"/delivery";
       cout << "SourcesExtractor::deliverProducts() copy command = " << tempstring << endl;
       syscon.execCommand(tempstring);
       rit1++;
  }
  string ts("cp "); string tt(arc->get_L3_Dir());
  ts.append(tt);ts.append("/*_L3.evt ");
  ts.append(getSasoaWorkDir());ts.append("/delivery");
  syscon.execCommand(ts);
  delete soutfilelist;
  delete doutfilelist;

}


/*!
    \fn SApipeline::SourcesExtractor::createExposureDataCard(string cardoutfilename, string sapoifilename, string ephfile)
 */
void SApipeline::SourcesExtractor::createExposureDatacard(const string &cardoutfilename, const string &sapoifilename, const string &ephfilename)
{
	if (verbose )cout << "SourcesExtractor::createExposureDatacard(const string &cardoutfilename, const string &sapoifilename, const string &ephfilename) start"  << endl;
    ofstream of;  string fn(cardoutfilename);
    stringstream ss; string ts;
	of.setf(ios::fixed,ios::floatfield);
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
	if (verbose) cout << "exposure datacard filename = " << fn << endl;
    of.open (fn.c_str(), ofstream::out | ofstream::trunc);
	of << "SAPOI_FILE         '"<<sapoifilename<<"'" << endl;
	of << "AG3914_FILE        '"<<tempstring2 << "/" << "" <<"'" << endl;
	of << "AG3916_FILE        '"<<ephfilename<<"'" << endl;
	of << "EARTHGTI_FILE      'EARTH_OCCULTATION.gti'" << endl;
	of << "EXPMODE            'field'" << endl;
	of << "TSTART_S            '"<<getTstart() <<"'" << endl;
	of << "TSTOP_S             '"<<getTstop() <<"'" << endl;
	of << "EXPOSURE_BOX_SUCCESS_FILE 'exp_box_file'" << endl;
    of.close();
  } catch (ofstream::failure e)  {
        cerr << "SourcesExtractor::createExposureDatacard() Exception opening/writing file"<< e.what() << endl;
  }
	  cout << "SourcesExtractor::createExposureDatacard() end"  << endl;
}
// create an attitude datacard for a temporal data set attitude correction operation
// takes in input
// 1) the output datacard filename (eidatacard)
// 2) the input l2 merged fits filename
// 3) the min contact number
// 4) the max contact number
// ---> tstart and tstop are read from the L2 file

void SApipeline::SourcesExtractor::createAttitudeDatacard(const string &eidatacard, const string &l2filename, int cmin, int cmax){
if (verbose) cout << "[stage 2] SourcesExtractor:::createAttitudeDatacard(string, string , int, int)" << endl;
ofstream outfile;
outfile.setf(ios::fixed,ios::floatfield);
outfile.open (eidatacard.c_str(), ofstream::out | ofstream::trunc);
tempstring = "L2EVL   '"+l2filename+"'";
outfile << tempstring << endl;
outfile << "L3EVL 'ei_outfile_L3.evt'"<< endl;
if (filelist.size()==0){
  tempstring2="SourcesExtractor::createAttitudeDatacard() 3914 file list is not filled \n";se.setMsg(tempstring2);  throw se;
} else{
  cout << "SourcesExtractor::createAttitudeDatacard() n. of 3914 files to be processed  "<< filelist.size() << endl;
}
vector<string>::iterator p; p = filelist.begin();
while (p != filelist.end()){
  outfile <<  "AG3914   '"<< *p++ << "'"<< endl;  
}
outfile << "#T0_QUAT_S '+1451606400.'       /per usare 39.14 non corretti insieme ai sal3"<< endl;
ss.setf(ios::fixed,ios::floatfield);
ss.str("");ss<<getTstart();tempstring2 = ss.str();
tempstring.assign("TSTART_S '");tempstring.append(tempstring2);tempstring.append("'");
outfile << tempstring << endl;
ss.str("");ss<<getTstop();tempstring2 = ss.str();
tempstring.assign("TSTOP_S '");tempstring.append(tempstring2);tempstring.append("'");
outfile << tempstring << endl;
outfile << "AVOID_TIMEREF_CHECK 'dummy'    /scommentare per usare 39.14 non corretti insieme ai sal3"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile.close();  
}
/** create the sapoi datacard for the quaternion to sapoi file conversion
    the 3914 attitude files are taken from the filelist vector that has to
    be filled before
*/
void SApipeline::SourcesExtractor::createSapoiDatacard(const string &cardoutfilename, const string &sapoifilename, int cmin, int cmax){
if (verbose) cout << "[stage 2] SourcesExtractor::createSapoiDatacard" << endl;
if (verbose) cout << "SourcesExtractor::createSapoiDatacard(string, string) inputfilename to write in the sapoi datacard is "<< commandlist.getInputFilename()  << endl;;
try{
ofstream outfile;
outfile.open (cardoutfilename.c_str(), ofstream::out | ofstream::trunc);
outfile << "################################################################################################"<< endl;
outfile << "#" << endl;
outfile << "#   L. Pacciani                                            F. Lazzarotto"<< endl;
outfile << "#   30/5/2006                                              19/10/2007     "<< endl;
outfile << "#   "+tmr.getDateString() << endl;
outfile << "#   luigi.pacciani@iasf-roma.inaf.it                    francesco.lazzarotto@iasf-roma.inaf.it"<< endl;
outfile << "#"<< endl;
outfile << "# input example for quat_to_sapoi "<< endl;
outfile << "#"<< endl;
outfile << "# this file is automatically generated by sasoa"<< endl;
outfile << "#"<< endl;
outfile << "################################################################################################"<< endl;
outfile << "# syntax:"<< endl;
outfile << "#"<< endl;
outfile << "# KEYWORD 'value'    /comment"<< endl;
outfile << "#"<< endl;
outfile << "# The symbol  #  at the start of the line"<< endl;
outfile << "# is aimed to comment the line"<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################################################"<< endl;
outfile << "# SA Pointing output file ."<< endl;
tempstring = "SAPOI_FILE   '"+sapoifilename+"'";
if (verbose) cout <<"SourcesExtractor::createSapoiDatacard(string, string) going to write the following instruction"<< endl;
cout << "" << tempstring << endl;
outfile << tempstring << endl;
outfile << "#FINE: lista dei ... "<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################################################"<< endl;
outfile << "# file list 39.14 per i quaternioni"<< endl;
outfile << "# the list has to be time ordered "<< endl;
outfile <<  endl;
if (filelist.size()==0){
  tempstring2="3914 file list is not filled \n";se.setMsg(tempstring2);  throw se;
} else{
  cout << "n. of 3914 files to be processed  "<< filelist.size() << endl;
}
vector<string>::iterator p; p = filelist.begin();
while (p != filelist.end()){
  outfile <<  "AG3914   '"<< *p++ << "'"<< endl;
}
outfile << "#END: 39.14 file list ... "<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################################################"<< endl;
outfile << "# DTMAX_NOATT_S definisce l'intervallo di tempo massimo accettabile (in secondi)"<< endl;
outfile << "#               di buco tra dati consecutivi di attitude contenuti"<< endl;
outfile << "#               nei file 39.14."<< endl;
outfile << "#"<< endl;
outfile <<  endl;
outfile << "DTMAX_NOATT_S  '2.'"<< endl;
outfile <<  endl;
outfile << "#FINE: DTMAX_NOATT_S definisce ... "<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################################################"<< endl;
outfile << "# lista file con i good time intervals"<< endl;
outfile <<  endl;
outfile << "#GTI   'mygti.fits'"<< endl;
outfile <<  endl;
outfile << "#FINE: lista file con i good ... "<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile <<  endl;
outfile << "################################################################################################"<< endl;
outfile << "# si puo' dare uno start ed uno stop"<< endl;
outfile << "# with following  KEYWORD"<< endl;
outfile << "# the time unit is seconds, time origin is defined by Chen "<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile << "OPEMODE            'fixed-time'"<< endl;
outfile << "CELL_RANGE_RAD     '0.004'"<< endl;
outfile << "RANGE_POI_CUT_RAD  '0.035'"<< endl;
outfile << "RANGE_SLEW_CUT_RAD '0.053'"<< endl;
outfile <<  endl;
outfile << "#END: se i file con le gti ...  "<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
//outfile << "TSTEP_S  '600.'       /step "<< endl;
outfile << "#END of the datacard "<< endl;
outfile << "################################################################################################"<< endl;
outfile <<  endl;
outfile <<  endl;
outfile.close();
} catch(const exception &e){
  cerr << "error in writing sapoi datacard"<< se.getMsg()<< endl;
  
}catch(const SAexception &se){
  cerr << "error in writing sapoi datacard"<< e.what()<< endl;

}catch(...){
  cerr << "error in writing sapoi datacard"<< endl;
}

}
/** Create an IDL batch script to launch
in batch by the operating system the IDL
exposure calculation and related GTI file
production
 */
void SApipeline::SourcesExtractor::createExposureIDLBatch(const string &batchfilename, const string &cardfilename){
    ofstream of;
    cout << "SourcesExtractor::createExposureIDLBatch() on file " << batchfilename << endl;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try {
        of.open (batchfilename.c_str(), ofstream::out | ofstream::trunc);
        of << ".run EXPOSURE_BOX_1.0.pro" << endl;
        of << "EXPOSURE_BOX, '"<<cardfilename<<"'" << endl;
        of << "exit" << endl;
  } catch (ofstream::failure e)  {
        cerr << "SourcesExtractor::createExposureIDLBatch() Exception opening/writing file"<< e.what() << endl;
  } catch(const exception &e){
  cerr << "error in creating exposure IDLBatch()"<< se.getMsg()<< endl;
  } catch(const SAexception &se){
  cerr << "error in creating exposure IDLBatch()"<< e.what()<< endl;
  } catch(...){
  cerr << "error in creating exposure IDLBatch()"<< endl;
}
}

void SApipeline::SourcesExtractor::createIrosMapBuilder(const string & inL3file, const string &outMDfile, const string &gtifile, int emin, int emax){

    try{
      if (verbose) cout << "SourcesExtractor::createIrosMapBuilder( executing L3 eventlist reading, filtering and MDimg creation " << endl;

      tempstring2 = inL3file;
      SAL3Eventlist sal3(inL3file);

      sal3.init();string ii("png");
      sal3.setPlotTerm(ii);
      if (verbose) cout << "SourcesExtractor::createIrosMapBuilder() reading  L3  " << inL3file << endl;
      sal3.setInputFilename(tempstring2);string hdn0("PACKETS");
      string hdn("EVENTS");  string fn(tempstring2);
      try{
        sal3.readHeaders(hdn0);
      } catch (const SAexception &se){
	      cerr << "error in reading the l3 evlist header " << se.getMsg() << endl;
      } catch (const exception &e){
	      cerr << "error in reading the l3 evlist header " << e.what() << endl;
      } catch (...){
	      cerr << "error in reading the l3 evlist header " << endl;
      }

    if (verbose) cout << "SourcesExtractor::createIrosMapBuilder() read dim = " << sal3.getInputDimension() << endl;
    try{
      sal3.readDebug(fn);
    } catch (...){
	    cerr << "error in reading the eventlist "<< endl;
    }

	    //	energy filter
	    sal3.filterEnergy(emin, emax);
	    sal3.effect();

		string nn;string newfn, ots;

    /*
 		nn = "E_min_20_E_MAX_55";
		newfn = arc->filenamer.getOutputFileName(SourcesExtraction);
	    ots = newfn.insert(newfn.find_last_of("."), nn);
		//newfn.insert(newfn.find_last_of("."), getFilterTarget());
		sal3.save(ots);       */

// TIME FILTER

// exposure gti filter

/*
  cout << "SourcesExtractor::createIrosMapBuilder() filtering for Earth Occultation GTI, file " << gtifile << endl;
	
tempstring = gtifile;

	sal3.filterAllGTI(tempstring);
	sal3.effect();
    
 		nn = "_EARTH";
		newfn = arc->filenamer.getOutputFileName(SourcesExtraction);
		ots = newfn.insert(newfn.find_last_of("."), nn);
		//newfn.insert(newfn.find_last_of("."), getFilterTarget());
		sal3.save(ots);
    // saga gti filter
    
    cout << "SourcesExtractor::launchIrosMapBuilder() filtering for Saga GTI " << endl;
	tempstring = arc->getCurrentSagaGTI_FileName();
	sal3.filterAllGTI(tempstring);
	sal3.effect();
 		nn = "SAGA";
		newfn = arc->filenamer.getOutputFileName(SourcesExtraction);
		ots = newfn.insert(newfn.find_last_of("."), nn);
		sal3.save(ots);
  */

    sal3.createPointHistos();
  	sal3.setProdSetDir(arc->filenamer.getContact());
    sal3.createProdSetDir();

    sal3.setImageType(0);
    sal3.setFCounter(0);
    sal3.setDebug(false);
    sal3.getAllDetImages();

    string imf1 = outMDfile;
    //string imf1 = "../stg_2/"; imf1.append(arc->filenamer.getFileName( IrosMapBuilding));
    irospilot.setInputFileName(imf1);
    
	     if (verbose) cout << "SourcesExtractor::createIrosMapBuilder() saving irosmap on file "<< imf1 << endl;
         if (verbose) cout << "SourcesExtractor::createIrosMapBuilder() going to exec saveIrosMap3 "<< endl;
       try{
         sal3.saveIrosMap3(imf1);
         if (verbose) cout << "SourcesExtractor::createIrosMapBuilder() executed saveIrosMap3 "<< endl;
      } catch(const exception &e){
          cerr << "exception in saving the iros map" << e.what() << endl;
      }


    sal3.setFCounter(0);
    sal3.setImageType(1);
    sal3.setDebug(false);
    sal3.plotMDImage();

    //  plot pointing histograms

    if (verbose) cout << "SourcesExtractor::aunchIrosMapBuilder() plotting pointing histograms"<< endl;
    sal3.setDebug(false);
    sal3.setFCounter(0);
    sal3.plotPointingHistogram('x');
    sal3.plotPointingHistogram('z');

      } catch(const exception &e){
        cerr << "error in creating irosmap MultiDetimg "<< se.getMsg()<< endl;
      } catch(const SAexception &se){
        cerr << "error in creating irosmap MultiDetimg"<< e.what()<< endl;
      } catch(...){
        cerr << "error in creating irosmap MultiDetimg"<< endl;
      } 
}

void SApipeline::SourcesExtractor::launchIros(const string &mapfilename){  
  try{
    string temp;
    temp = "../stg_2";
    irospilot.setBaseDir(temp);
    passIrosMap(mapfilename, irospilot.getBaseDir());
    cout << "launchSourcesExtractor() launching IROS on file " << mapfilename << endl;
    arc->setIrosMapFileName(mapfilename);
    setIrosMapFileName(mapfilename);
    temp =  "../stg_2/IROS_Multi-D/launchIrosIDLBatch";
    setIROS_IDLBatchFileName(temp);
    printPointingBatch(cout);
	string pstring = "../stg_2/.MD_IROS_Pilot";
    for(int i=0; i<4; i++) {
      createIrosBatch(i, pstring, mapfilename); // create the internal iros pilot file
      createPointingBatch(); // create the internal iros pilot file
      showIrosBatch();
      irospilot.setDetector(i);
      createIrosIDLBatch(getIROS_IDLBatchFileName());  // create the IDL batch
      launchIros();
    }
    
    } catch(const exception &e){
        cerr << "error in launching iros "<< se.getMsg()<< endl;
      } catch(const SAexception &se){
        cerr << "error in creating iros "<< e.what()<< endl;
      } catch(...){
        cerr << "error in creating iros "<< endl;
      } 
   
}

void SApipeline::SourcesExtractor::launchIros(const string &l3file, const string &mapfilename){  
  try{
    string temp;
    temp = "../stg_2";
    irospilot.setBaseDir(temp);
    passIrosMap(mapfilename, irospilot.getBaseDir());
    cout << "launchSourcesExtractor() launching IROS on file " << mapfilename << endl;
	arc->setIrosMapFileName(mapfilename);
    setIrosMapFileName(mapfilename);
    temp =  "../stg_2/IROS_Multi-D/launchIrosIDLBatch";
    setIROS_IDLBatchFileName(temp);
    printPointingBatch(cout);
	string pstring = "../stg_2/.MD_IROS_Pilot";
    for(int i=0; i<4; i++) {
      createIrosBatch(i, pstring, mapfilename); // create the internal iros pilot file
      createPointingBatch(l3file); // create the internal iros pilot file
      showIrosBatch();
      irospilot.setDetector(i);
      createIrosIDLBatch(getIROS_IDLBatchFileName());  // create the IDL batch
      launchIros();
    }
    
    } catch(const exception &e){
        cerr << "error in launching iros "<< se.getMsg()<< endl;
      } catch(const SAexception &se){
        cerr << "error in creating iros "<< e.what()<< endl;
      } catch(...){
        cerr << "error in creating iros "<< endl;
      } 
   
}

void SApipeline::SourcesExtractor::createIrosBatch(byte det, const string &batchname, const string &mdinputfile){
  ofstream of;  string fn;
    of.exceptions (ofstream::eofbit | ofstream::failbit | ofstream::badbit );
      try { 
            fn = batchname;
            if (verbose) cout << "SourcesExtractor::createIrosBatch() on file "<< fn << endl;
            of.open (fn.c_str(), ofstream::out | ofstream::trunc);
            of << ";#####################################################" << endl;
            of << ";# This is a sample pilot file for the MD_IROS" << endl;
            of << ";# For the SuperAGILE pipeline SASOA " << endl;
            of << ";# Igor Lapshov & Francesco Lazzarotto " << endl;
			of << ";#   "+tmr.getDateString() << endl;
            of << ";#####################################################" << endl;
//            of << "BASE_DIR    = ../stg_2/	      ; Base directory" << endl;
            of << "BASE_DIR    = "<<arc->getSasoaHome()<<"/stg_2/	      ; Base directory" << endl;

             if (verbose) cout << "SourcesExtractor::createIrosBatch() BASE_DIR    = "<<irospilot.getBaseDir()<<"	      ; Base directory" << endl;
            of << "FILE	    = "+mdinputfile+"    ; Input file name " << endl;
             if (verbose) cout << "SourcesExtractor::createIrosBatch() multi detector image File name    = "<<mdinputfile << endl;
			verbose = false;
			cout << "executing IROS for detector " << int(det) << endl;
            of << "DETECTOR    = "<<  int(det)  <<"			          ; -- Detector number" << endl;
            of << "LAD_GAP	    = 18			       ; Gap between ladders" << endl;
            of << "GAP_START   = 767			   ; Strip No. after gap" << endl;
            of << "MAX_ROUNDS  = 5				   ; No. of IROS rounds" << endl;
            of << "MIN_SIGMAS  = 4.5		       ; Number of STDs." << endl;
            of << "USE_CAT	    = 0 			          ; Set to 1 if catalog is to be used. " << endl;
			of <<"USE_DEFF_MASK = 1     ; 1 to use efficiency arrays" << endl;
			of <<"DEFF_MASK_NAME  = "<<" ../stg_2/DEff_Mask_updated_070704.eff"<< endl;
			of <<"SAFE_MODE   = 1        ; 1 if to use a safe mode"<< endl;
			of <<"S_MODE_LEVEL = 0.01 ; Fractional change of chi2 in safe mode"<< endl;
			of <<"GROUND_MASK  = 0    ; Set to 1 if need to use magnified array"<< endl;
			of <<"BKGR_MODEL   = 2    ; 1, 2, etc. for different BKGR models"<< endl;
          of.close();
      } catch (ofstream::failure e)      {
        cout << "SourcesExtractor::SourcesExtractor::createIrosBatch() Exception opening/writing file"<< e.what() << endl;
      }
}


/*!
    \fn SApipeline::SourcesExtractor::getAttitudeFileName()
 */
string SApipeline::SourcesExtractor::getAttitudeFileName()
{

  tempstring = arc->get_L1_Dir() +"/"+commandlist.getAttitudeFileName();
  return tempstring;     
}
