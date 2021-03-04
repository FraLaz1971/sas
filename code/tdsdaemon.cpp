/***************************************************************************
                          tdsdaemon.cpp  -  description
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

#include "tdsdaemon.h"
namespace SApipeline {
  namespace TDS {

TDSDaemon::TDSDaemon(vector<string> dbc){
tempstring = "/home/agile/projects/AUX/gtbweb.bo.iasf.cnr.it/private/gtb_data/AGILEGS/PREPROCESSING/COMMISS_001/temp_arch/AUX";
	setCotDir(tempstring);
	dbp = new AGILEDBConnector(dbc);
}


TDSDaemon::TDSDaemon(){
	tempstring = "/home/agile/projects/AUX/gtbweb.bo.iasf.cnr.it/private/gtb_data/AGILEGS/PREPROCESSING/COMMISS_001/temp_arch/AUX";
	setCotDir(tempstring);
	vector <string> dbcoords ;
	dbcoords[0] = "QMYSQL3";
	dbcoords[1] = "test2";
	dbcoords[2] = "agiledb";
	dbcoords[3] = "superflight";
	dbcoords[4] = "bigfoot.iasf-roma.inaf.it";

	dbp = new AGILEDBConnector(dbcoords);
}
TDSDaemon::~TDSDaemon(){
}
}
}

/*!
    \fn SApipeline::TDS::TDSDaemon::start()
 */
void SApipeline::TDS::TDSDaemon::start(double tstart, double tstep)
{
tempstring = "mkdir temp";syscon.execCommand(tempstring);
tempstring = "mv *.log temp/";syscon.execCommand(tempstring);
tempstring = getCotDir();
ss.str("");ss << "rm " << tempstring << "/mergedcot*.COT"<< endl; 
tempstring = ss.str();syscon.execCommand(tempstring);
double TSTART = tstart;
double TSTOP = tstart; 
int ccount=1;
int elapsed = 0;
while (true){

	TSTOP = TSTART + tstep;
	cout << "TSTART = " << TSTART <<  " TSTOP = " << TSTOP<<endl;
	cout << atime.AGILETimeToUTC(TSTART) << endl;
	cout << atime.AGILETimeToUTC(TSTOP) << endl;
	//cout << "cotProcess.sh $TSTART $TSTOP" << endl;
	ss.str(""); ss << "cd ../SATemporalDataSet/; ./cotProcess.sh " <<  TSTART << " " << TSTOP << " > tempdataset_"<<ccount<<"_out.log" << " 2> tempdataset_"<<ccount<<"_err.log" << endl;
	tempstring = ss.str();
	cout << tempstring << endl;
	syscon.execCommand(tempstring);
	//tempstring = "	./cotProcess.sh $TSTART $TSTOP >"day_$ccount"_out".log" 2>"day_$ccount"_err".log""; 
	TSTART = TSTOP;
	ccount = ccount + 1;
	cout << "elapsed " << sleep((unsigned int)tstep) << endl;
}
}


/*!
    \fn SApipeline::TDS::TDSDaemon::setCotDir(string cotd)
 */
void SApipeline::TDS::TDSDaemon::setCotDir(string cotd)
{
    cotdir = cotd;
}


/*!
    \fn SApipeline::TDS::TDSDaemon::getCotDir()
 */
string SApipeline::TDS::TDSDaemon::getCotDir()
{
   return cotdir;
}




/*!
    \fn SApipeline::TDS::TDSDaemon::cotProcess()
 */
void SApipeline::TDS::TDSDaemon::cotProcess()
{
/*
 echo download COT file in COT Dir
#cd ../AUX
#wget -m -A.COT  http://gtbweb.bo.iasf.cnr.it/private/gtb_data/AGILEGS/PREPROCESSING/COMMISS_001/temp_arch/AUX/ > out.log 2> err.log
#execute time range reading for all COT files
#cd $OLDPWD
echo "elapsed seconds for updating COT files: " $SECONDS
echo date
echo bye bye

rm *.fits
./extractContactPrevTimeRange.sh ../AUX/gtbweb.bo.iasf.cnr.it/private/gtb_data/AGILEGS/PREPROCESSING/COMMISS_001/temp_arch/AUX "./isTimeRangeContained.sh" "$1" "$2"
./TDSlauncher.sh  "$1" "$2" real.COT
echo "elapsed to process all COT files seconds: " $SECONDS
echo date
echo bye bye
*/
}


/*!
    \fn SApipeline::TDS::TDSDaemon::launch(double tstart, double tstop)
 */
void SApipeline::TDS::TDSDaemon::launchTDS(double mtstart, double mtstop)
{

	tstart = mtstart; tstop = mtstop;
        int argc = 0; char **argv = (char **)new char[2];
	QApplication *aa = new QApplication(argc, argv);
  	dbp->setQappPoint(aa);
	vector<int> contint;

  try{

	double ntsa, ntso;
// ################################
	ntsa = tstart + 86400;	ntso = tstop + 86400;
// ################################

	//delete aa;
	//	contint = getContactRange(ntsa, ntso);
	cout << "TDSDaemon::launchTDS() going on !!! "<< endl;

	string gf; int nf; gf = "select * from ContactTable";	nf = 1;

	  vector<string> sv;	
	//  vector<string>::iterator svi = sv.begin();
    dbp->loadDBDefaults();
    se.setMsg("TDSDaemon::launchTDS()) error in connecting to the database ");
    if (!dbp->createConnection()) throw se;

	contint = getContactRange(tstart, tstop);

	setContactMin(contint[0]);		setContactMax(contint[1]);

	cout << "first value is " << contactmin << " last value is " << contactmax << endl;

	se.setMsg("TDSDaemon::launchTDS() error in disconnecting the database ");
    if (!dbp->closeConnection()) throw se;

  } catch (const SAexception &se){
 cerr << "error " << se.getMsg() << endl;
  } catch (const exception &e){
   cerr << "error " << e.what() << endl;
  } catch (...){
   cerr << "error " <<  endl;
  }



		tempstring = "rm -f *.fits";syscon.execCommand(tempstring);
		tempstring = "rm cr.txt";syscon.execCommand(tempstring);
		tempstring = "rm -f *L3*.evt";syscon.execCommand(tempstring);


		cout << "TDSDaemon::launchTDS(): downloading files ..." << endl;

		ss.str("");ss << "./rsync_telemetry.sh " << getLocalHost() << " " << getRemoteHost() << " " << getRemoteUser() << " " << (contint[0] - 1) << " " << (contint[1] + 1) << endl;
		cout << "executing " << ss.str() << endl; 
		syscon.setVerbose(true);
		tempstring = ss.str();syscon.execCommand(tempstring);

		cout << "TDSDaemon::launchTDS(): downloaded telemetry data  ..." << endl;

		ss.str("");ss << "./rsync_l2file.sh " << getLocalHost() << " " << getRemoteHost() << " " << getRemoteUser() << " " << contint[0] << " " << contint[1] << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);

		cout << "TDSDaemon::launchTDS(): downloaded l2 data  ..." << endl;

		cout << "TDSDaemon::launchTDS() echo unzipping files ..." << endl;

		cout << "TDSDaemon::launchTDS() testing translating functions from " << endl;
		cout << "TDSDaemon::launchTDS() centint of tstart = " << tdbuilder.getCentString(contint[0])<< endl;
		cout << "TDSDaemon::launchTDS() centint of tstop = " << tdbuilder.getCentString(contint[1])<< endl;
		
		tdbuilder.unzipAttRange(contint[0]-1, contint[1]+1);
		tdbuilder.unzipEphRange(contint[0]-1, contint[1]+1);
		tdbuilder.unzipL2Range(contint[0], contint[1]);
			
		//./tempdataset.sh $pars testout.fits
		ss.str("");ss << "./tempdataset.sh " << contint[0] << " " << contint[1] << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSDaemon::launchTDS() executing " << tempstring << endl;
		syscon.execCommand(tempstring);

			string h("temp_eph.fits"), j("eph_testout.fits");
		  	SADataCorrector *sc = new SADataCorrector(); 
			double ephtstart, ephtstop;
			ephtstart = tstart + 756950400;
			ephtstop = tstop + 756950400;
		try{
			tempstring = "mv eph_testout.fits temp_eph.fits";syscon.execCommand(tempstring);		
			sc->CorrectTDS(h, j, ephtstart, ephtstop);
		} catch (const SAexception &se){
			cerr << " error in correcting the ephemeris file " << se.getMsg() << endl;
		} catch (const exception &e){
			cerr << " error in correcting the ephemeris file " << e.what() << endl;
		}
			delete sc;

		  	SADataCorrector *sc2 = new SADataCorrector(); 
		try{
			tempstring = "mv l2_testout.fits temp_l2.fits";syscon.execCommand(tempstring);
			h = "temp_l2.fits"; j = "l2_testout.fits";
			sc2->CorrectTDS(h, j, tstart, tstop);
		} catch (const SAexception &se){
			cerr << " error in correcting the L2 events file" << se.getMsg() << endl;
			process();
		} catch (const exception &e){
			cerr << " error in correcting the L2 events file" << e.what() << endl;
			process();
		}
			delete sc2;

		process();
		
		//"./remove_telemetry.sh $pars"
		//"./remove_l2file.sh $pars"
		
		int real_contactmin, real_contactmax;
		real_contactmin = contint[0] - 1;
		real_contactmax = contint[1] + 1;
		try{
		ss.str("");ss << "./remove_telemetry.sh " << real_contactmin << " " << real_contactmax << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSDaemon::launchTDS() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		} catch (const SAexception &se){
			cerr << " error in removing the telemetry" << se.getMsg() << endl;
		} catch (const exception &e){
			cerr << " error in removing the telemetry" << e.what() << endl;
		}
		try{
		ss.str("");ss << "./remove_l2file.sh " << real_contactmin << " " << real_contactmax << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSDaemon::launchTDS() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		} catch (const SAexception &se){
			cerr << " error in removing the L2 file" << se.getMsg() << endl;
		} catch (const exception &e){
			cerr << " error in removing the L2 file" << e.what() << endl;
		}
		
		exit(0);

}


/*!
    \fn SApipeline::TDS::TDSDaemon::getContactRange(double mtstart, double mtstop)
 */
vector<int> SApipeline::TDS::TDSDaemon::getContactRange(double mtstart, double mtstop)
{
  tstart = mtstart; tstop = mtstop; 
  cout.setf(ios::fixed,ios::floatfield);
  int status = 0;

  dbp->setVerbose(false);

  string tsta, tsto;
//  string gf = "select contactnumber from ContactTable where (tstop > \"2008-02-05 17:00:33\") AND (tstop < \"2008-02-05 22:42:48\") ";
	if (verbose) cout << "input mtstart = " << mtstart << endl;
	if (verbose) cout << "input tstop =  "<< tstop << endl;

	if (verbose) cout << "i retrieve this datetime values for the previous time interval " << endl;	

	tsta = atime.AGILETimeToUTCDateTime(mtstart);
	tsto = atime.AGILETimeToUTCDateTime(tstop);

	if (verbose) cout << "mtstart datetime "<< tsta << endl;
	if (verbose) cout << "tstop datetime "<< tsto << endl;

  stringstream gfss; gfss.str("");

  gfss << "select contactnumber from ContactTable where (tstop > \""<<tsta<<"\") AND (tstop < \""<< tsto <<"\") ";
  
  
  string gf = gfss.str(); gfss.str("");

  if (verbose) cout << "TDSDaemon::getContactRange() executing query on DB: " << gf << endl;
  string tempstring;

  int nf = 1;
  //db.testCOTConnection();
  vector<string> sv;
//  vector<string>::iterator svi = sv.begin();
  try{

  
    sv = dbp->executeSQLOpenQuery(gf, nf);

	if (verbose ) cout << "TDSDaemon::getContactRange() first value is " << sv[0] << "TDSDaemon::getContactRange() last value is " << sv[sv.size() - 1]<< endl;
    
	se.setMsg("DBConnector::executeSQLQuery() error in disconnecting the database ");

  } catch (const SAexception &se){
 cerr << "error " << se.getMsg() << endl;
  } catch (const exception &e){
   cerr << "error " << e.what() << endl;
  } catch (...){
   cerr << "error " <<  endl;
  }

	myiv.push_back(atoi(sv[0].c_str()));
	myiv.push_back(atoi(sv[sv.size() - 1].c_str()));
	return myiv;

}


/*!
    \fn SApipeline::TDS::TDSDaemon::process()
 */
int SApipeline::TDS::TDSDaemon::process()
{
  exception e; SAexception se;
  Timer mytime;
  mytime.start();

  OrbitRebuilder orbilder;
  SystemConnector mysystem;
  //if (argc<5) cout << "usage: ./runTDS <exp_datacard_out_filename> <sapoifilename> <ephfilename> <mtstart> <tstop> <contactmin> <contactmax>" << endl;
  int status = 0;

	// handler $SASOA_HOME variable

  string cof("$SASOA_HOME/stg_2/EXP_DELIVERY/ei_card.txt"), sof("ei_sapoifile.fits"), eph("eph_testout.fits");
  double sta = tstart; double sto = tstop;

  int cmi = contactmin; int cma = contactmax; 


/*
/sadaslibsproject "$SASOA_HOME/stg_2/EXP_DELIVERY/ei_card.txt" "ei_sapoifile.fits" "$PWD/../../eph_testout.fits" $1 $2 $pars
*/


/*
  ArchiveScanner scanner; string covfile;
  covfile = "../../test_temp3905files.txt";	scanner.readEventsCoverage(covfile);
  covfile = "../../test_temp3914files.txt";	scanner.readAttCoverage(covfile);
  covfile = "../../test_temp3916files.txt";	scanner.readEphCoverage(covfile);

  exit(0);

*/

  string sdf("ei_sapoidatacard.txt"), sf;
  string jj("ei_outfile_L3.evt"), gtgt("/home/agile/projects/sasoa/stg_2/EXP_DELIVERY/EARTH_OCCULTATION.gti"), md("ei_MultiDimg.dat");
  int emi = 21; int ema = 57;
  SourcesExtractor srcx;  ArchiveHandler ark;
  string yyff("SA");	srcx.setDetNam(yyff);
  string sh_varname; string sh_value;
  sh_varname = "SASOA_HOME"; 
  try{
   sh_value = mysystem.getEnvVar(sh_varname);
  } catch (const SAexception &se){
    cerr << "TDSDaemon::process() : errror in getting SASOA_HOME env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSDaemon::process() : errror in getting SASOA_HOME env var" << e.what() << endl;
  } catch (...){
    cerr << "TDSDaemon::process() : errror in getting SASOA_HOME env var" << endl;
  }

  string dfn("/stg_2/EXP_DELIVERY/ei_card.txt"); 
  dfn += sh_value;

  string attdfn("eit_attitude_datacard.txt");   string l2fn("l2_testout.fits");

  string bb = sh_value; bb += "/stg_2/attitude/version_for_sasoa/script/sal2_to_l3.sh " ;
  bb += attdfn;
  
  string thstring = sh_value;
  ark.setSasoaHome(thstring);ark.setIrosMapFileName(md);
  cout << "ark.getSasoaHome() = " << ark.getSasoaHome() << endl;
  initArchiveEnv(&ark, srcx);
  srcx.setArchiveHandler(&ark);
  srcx.setTstart(sta);srcx.setTstop(sto);srcx.init();
  string ff("plain3914files.txt");
  srcx.setVerbose(true);
  string dtemp; IrosPilot irospilot;

 if (verbose) cout << "TDSDaemon::process() here 3" << endl;
  sh_varname = "SASOA_WORKDIR"; 
  try{
   sh_value = mysystem.getEnvVar(sh_varname);
  } catch (const SAexception &se){
    cerr << "TDSDaemon::process() : errror in getting SASOA_HOME env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSDaemon::process() : errror in getting SASOA_HOME env var" << e.what() << endl;
  } catch (...){
    cerr << "TDSDaemon::process() : errror in getting SASOA_HOME env var" << endl;
  }


  thstring = sh_value;
  ark.setSasoaWorkDir(thstring); string sn;
  
  ss.str(""); ss << contactmin; string ccmin = ss.str();
  string ta1 = ccmin;
  ss.str(""); ss << contactmax; string ccmax = ss.str();
  string ta2 = ccmax;

  int n = 0; string jju("_"); 
  ss.str(""); ss << n;  sn = ss.str();
  thstring = ta1 + jju  + sn + jju + ta2 ;
  cout << "old archivedir = " << thstring << endl;
  cout << "TDSarchivedir = " << ark.getTDSArchiveDir(sta, sto) << endl;
  thstring = ark.getTDSArchiveDir(sta, sto);
  ark.setArchiveDir(thstring);
/*
  thstring = ta1 + jju  + sn + jju + ta2 ;
  ark.setArchiveDir(thstring);
*/


 if (verbose) cout << "TDSDaemon::process() here 3" << endl;
 // string sh_varname; string sh_value;


  dtemp = thstring + "/stg_2";
  irospilot.setBaseDir(dtemp);  
  string here("PWD");
  //cout << "sono qui : " << mysystem.getEnvVar(here) << endl;
  sf = mysystem.getEnvVar(here) + "/" + sof; 
  // create attitude datacard and launch attitude correction
  // to produce dataset L3 file
  srcx.fillFilelist(ff);
  // create attitude datacard, the requested input parameters are:
  // attitude output file name (attdfn) l2 eventlist input filename file name (attdfn)
  // min. contact number max contact number 
  // the l3 output filename is fixed to ei_outfile_L3.evt

  srcx.createAttitudeDatacard(attdfn, l2fn, cmi, cma);

 // remove old temp files
  string hfh("rm -f ei_outfile_L3.evt"); system(hfh.c_str());
  string bfh("rm -f ei_sapoifile.fits"); system(bfh.c_str());
  string tfh("rm -f ag3914_sal3_bti.fits"); system(tfh.c_str());
//---------> 

  // launch L3 generation

  if (verbose) cout << "TDSDaemon::process() launching attitude correction " << endl;

  try{
  system(bb.c_str());
  } catch (const SAexception &se){
    cerr << "TDSDaemon::process() : errror in attitude correction" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSDaemon::process() : errror in attitude correction" << e.what() << endl;
  } catch (...){
    cerr << "TDSDaemon::process() : errror in attitude correction" << endl;
  }

  //string tempstring = srcx.getUserHome()+"/SASOA/"+srcx.getDetnam()+"/data/L3";
  string tempstring = ark.get_L3_Dir();
  srcx.passOutputFile(tempstring); // control: generalize?
  srcx.deliverProducts();
  srcx.announceDelivery();
  srcx.finalizeLaunch();  
  srcx.setVerbose(false);
  orbilder.setOrbitString(ta1, ta2);
  ark.retrieveArchiveDir(orbilder.getOrbitString());
  ark.setArchiveDir(ark.getTDSArchiveDir(sta, sto));	
  ark.createCurrentArchiveDir();
  ark.moveDeliverableData(ark.getArchiveDir());
  string ts = ark.getArchiveDir();

  string cmd = "cp eph_testout.fits " + ts;
  cout << "executing " << cmd.c_str() << endl;
  system(cmd.c_str());
  string cmd2 = "cp ag3914_sal3_bti.fits " + ts;
  cout << "executing " << cmd2.c_str() << endl;
  system(cmd2.c_str());

  cout << "ta1 = " << ta1 << " ta2 = "<< ta2 << endl;

  string mts = "autoEMIDaily "+ts; mts += " "; 
  mts += ta1;  mts += " ";  mts += ta2;

  cout << "executing " << mts.c_str() << endl;
  system(mts.c_str());

  ark.clearTempData();
  mytime.stop();mytime.report();

}


/*!
    \fn SApipeline::TDS::TDSDaemon::processSRC()
 */
void SApipeline::TDS::TDSDaemon::processSRC()
{
    /// @todo implement me
}


/*!
    \fn SApipeline::TDS::TDSDaemon::initArchiveEnv()
 */
void SApipeline::TDS::TDSDaemon::initArchiveEnv(ArchiveHandler *sarchiver, PipelineModule &pipemodule)
{
try{
  string temp;
  sarchiver->setSasoaHome(pipemodule.getSasoaHome());
  sarchiver->setSasoaWorkDir(pipemodule.getSasoaWorkDir());
  temp = pipemodule.getSasoaWorkDir()+"/delivery";
  sarchiver->setDeliveryDir(temp);
  temp = pipemodule.getSasoaWorkDir()+"/archive";
  sarchiver->setArchiveRoot(temp);

  /** set all data level dirs L1, L2 , L3 ... */
  sarchiver->setDataDirs();
} catch(const SAexception & se){
	cerr << "TDSDaemon::initArchiveEnv() error in initializing archiver environment "<< se.getMsg()<< endl;
}
catch(const exception & e){
	cerr << "TDSDaemon::initArchiveEnv() error in initializing archiver environment "<< e.what()<< endl;

}
}


/*!
    \fn SApipeline::TDS::TDSDaemon::setLocalHost(string lh)
 */
void SApipeline::TDS::TDSDaemon::setLocalHost(string lh)
{
    localhost = lh;
}

/*!
    \fn SApipeline::TDS::TDSDaemon::getLocalHost()
 */
string SApipeline::TDS::TDSDaemon::getLocalHost()
{
    return localhost;
}


/*!
    \fn SApipeline::TDS::TDSDaemon::setRemoteUser()
 */
void SApipeline::TDS::TDSDaemon::setRemoteUser(string ru)
{
    remoteuser = ru;
}


/*!
    \fn SApipeline::TDS::TDSDaemon::setRemoteHost()
 */
void SApipeline::TDS::TDSDaemon::setRemoteHost(string rh)
{
    remotehost = rh;
}


/*!
    \fn SApipeline::TDS::TDSDaemon::getRemoteHost()
 */
string SApipeline::TDS::TDSDaemon::getRemoteHost()
{
    return remotehost;
}


/*!
    \fn SApipeline::TDS::TDSDaemon::getRemoteUser()
 */
string SApipeline::TDS::TDSDaemon::getRemoteUser()
{
    return remoteuser;
}

