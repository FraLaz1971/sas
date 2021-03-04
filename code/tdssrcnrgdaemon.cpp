//
// C++ Implementation: tdssrcnrgdaemon
//
// Description: 
//
//
// Author: TDS src & energy account <TDS_src_nrg@bigfoot>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "tdssrcnrgdaemon.h"

namespace SApipeline {

namespace TDS {


TDSSrcNrgDaemon::TDSSrcNrgDaemon(){
	tempstring = "/home/agile/projects/AUX/gtbweb.bo.iasf.cnr.it/private/gtb_data/AGILEGS/PREPROCESSING/COMMISS_001/temp_arch/AUX";
	setCotDir(tempstring);
	dbp = new AGILEDBConnector();
}

TDSSrcNrgDaemon::TDSSrcNrgDaemon(vector<string> dbc){
tempstring = "/home/agile/projects/AUX/gtbweb.bo.iasf.cnr.it/private/gtb_data/AGILEGS/PREPROCESSING/COMMISS_001/temp_arch/AUX";
	cout << "TDSSrcNrgDaemon() creator" << endl;
	setCotDir(tempstring);
	dbp = new AGILEDBConnector(dbc);
}

TDSSrcNrgDaemon::~TDSSrcNrgDaemon(){
}

/*!
    \fn TDSSrcNrgDaemon::start()
 */
void TDSSrcNrgDaemon::start(double tstart, double tstep)
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
    \fn TDSSrcNrgDaemon::setCotDir(string cotd)
 */
void TDSSrcNrgDaemon::setCotDir(string cotd)
{
    cotdir = cotd;
}


/*!
    \fn TDSSrcNrgDaemon::getCotDir()
 */
string TDSSrcNrgDaemon::getCotDir()
{
   return cotdir;
}


/*!
    \fn TDSSrcNrgDaemon::cotProcess()
 */
void TDSSrcNrgDaemon::cotProcess()
{

}


/*!
    \fn TDSSrcNrgDaemon::launch_TDS_Source(double mtstart, double mtstop, double src_ra, double src_dec, string prefix)
 */

/*

void TDSSrcNrgDaemon::launch_TDS_Source(double mtstart, double mtstop, double msrc_ra, double msrc_dec, string prefix)
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

	//	contint = getContactRange(ntsa, ntso);
	cout << "TDSSrcNrgDaemon::launch_TDS_Source() going on !!! "<< endl;
	
	src_ra = msrc_ra; 

	src_dec = msrc_dec;

	string gf; int nf; gf = "select * from ContactTable";	nf = 1;

	vector<string> sv;	
	//  vector<string>::iterator svi = sv.begin();
    dbp->loadDBDefaults();
    se.setMsg("TDSSrcNrgDaemon::launch_TDS_Source() error in connecting to the database ");
    if (!dbp->createConnection()) throw se;

	contint = getContactRange(tstart, tstop);

	setContactMin(contint[0]);		setContactMax(contint[1]);

	cout << "TDSSrcNrgDaemon::launch_TDS_Source() first value is " << contactmin << " last value is " << contactmax << endl;

	se.setMsg("TDSSrcNrgDaemon::launch_TDS_Source() error in disconnecting the database ");
    if (!dbp->closeConnection()) throw se;

  } catch (const SAexception &se){
 cerr << "error " << se.getMsg() << endl;
  } catch (const exception &e){
   cerr << "error " << e.what() << endl;
  } catch (...){
   cerr << "error " <<  endl;
  }

		src_prefix = prefix;
		tempstring = "rm -f *.fits";syscon.execCommand(tempstring);
		tempstring = "rm cr.txt";syscon.execCommand(tempstring);
		tempstring = "rm -f *L3*.evt";syscon.execCommand(tempstring);


		cout << "TDSSrcNrgDaemon::launch_TDS_Source(): downloading files ..." << endl;

		ss.str("");ss << "./rsync_telemetry.sh " << getLocalHost() << " " << getRemoteHost() << " " << getRemoteUser() << " " << (contint[0] - 1) << " " << (contint[1] + 1) << endl;
		cout << "executing " << ss.str() << endl; 
		syscon.setVerbose(true);
		tempstring = ss.str();syscon.execCommand(tempstring);

		cout << "TDSSrcNrgDaemon::launch_TDS_Source(): downloaded telemetry data  ..." << endl;

		ss.str("");ss << "./rsync_l2file.sh " << getLocalHost() << " " << getRemoteHost() << " " << getRemoteUser() << " " << contint[0] << " " << contint[1] << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);

		cout << "TDSSrcNrgDaemon::launch_TDS_Source(): downloaded l2 data  ..." << endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_Source() echo unzipping files ..." << endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_Source() testing translating functions from " << endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_Source() centint of tstart = " << tdbuilder.getCentString(contint[0])<< endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_Source() centint of tstop = " << tdbuilder.getCentString(contint[1])<< endl;
		
		tdbuilder.unzipAttRange(contint[0]-1, contint[1]+1);
		tdbuilder.unzipEphRange(contint[0]-1, contint[1]+1);
		tdbuilder.unzipL2Range(contint[0], contint[1]);
			
		//./tempdataset.sh $pars testout.fits
		ss.str("");ss << "./tempdataset.sh " << contint[0] << " " << contint[1] << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_Source() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		
			// correcting merged data

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
			//process();
		} catch (const exception &e){
			cerr << " error in correcting the L2 events file" << e.what() << endl;
			//process();
		}
			delete sc2;
	try{
		process();
			} catch (const SAexception &se){
			cerr << " error in processing TDS SRC operations" << se.getMsg() << endl;
			//process();
		} catch (const exception &e){
			cerr << " error in correcting the L2 events file" << e.what() << endl;
			//process();
		}

		// removing local products
				
		int real_contactmin, real_contactmax;
		real_contactmin = contint[0] - 1;
		real_contactmax = contint[1] + 1;

		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_Source() removing local files !"<< endl;

		try{
		ss.str("");ss << "./remove_telemetry.sh " << real_contactmin << " " << real_contactmax << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_Source() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		} catch (const SAexception &se){
			cerr << " error in removing the telemetry" << se.getMsg() << endl;
		} catch (const exception &e){
			cerr << " error in removing the telemetry" << e.what() << endl;
		}
		try{
		ss.str("");ss << "./remove_l2file.sh " << real_contactmin << " " << real_contactmax << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_Source() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		} catch (const SAexception &se){
			cerr << " error in removing the L2 file" << se.getMsg() << endl;
		} catch (const exception &e){
			cerr << " error in removing the L2 file" << e.what() << endl;
		}
		
		exit(0);


}

*/

/*!
    \fn TDSSrcNrgDaemon::getContactRange(double mtstart, double mtstop)
 */
vector<int> TDSSrcNrgDaemon::getContactRange(double mtstart, double mtstop)
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

  if (verbose) cout << "TDSSrcNrgDaemon::getContactRange() executing query on DB: " << gf << endl;
  string tempstring;

  int nf = 1;
  //db.testCOTConnection();
  vector<string> sv;
//  vector<string>::iterator svi = sv.begin();
  try{

  
    sv = dbp->executeSQLOpenQuery(gf, nf);

	if (verbose ) cout << "TDSSrcNrgDaemon::getContactRange() first value is " << sv[0] << "TDSSrcNrgDaemon::getContactRange() last value is " << sv[sv.size() - 1]<< endl;
    
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
    \fn TDSSrcNrgDaemon::process()
 */
int TDSSrcNrgDaemon::process()
{
  exception e; SAexception se;
  Timer mytime;
  mytime.start();

  OrbitRebuilder orbilder;
  SystemConnector mysystem;

// if (argc<8) cout << "usage: ./runTDS_SRC <exp_datacard_out_filename> <sapoifilename> <ephfilename> <tstart> <tstop> <contactmin> <contactmax> <src_ra> <src_dec> <src_prefix>" << endl;
  int status = 0;

	// handler $SASOA_HOME variable

  string cof("$SASOA_HOME/stg_2/EXP_DELIVERY/ei_card.txt"), sof("ei_sapoifile.fits"), eph("eph_testout.fits");
  double sta = tstart; double sto = tstop;

  int cmi = contactmin; int cma = contactmax; 


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
  ark.clearDeliverableData();
  initArchiveEnv(&ark, srcx);
  srcx.setArchiveHandler(&ark);
  srcx.setTstart(sta);srcx.setTstop(sto);srcx.init();
  string ff("plain3914files.txt");
  srcx.setVerbose(true);
  string dtemp; IrosPilot irospilot;

 if (verbose) cout << "TDSSrcNrgDaemon::process() here 3" << endl;
  sh_varname = "SASOA_WORKDIR"; 
  try{
   sh_value = mysystem.getEnvVar(sh_varname);
  } catch (const SAexception &se){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_WORKDIR env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_WORKDIR env var" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_WORKDIR env var" << endl;
  }


  thstring = sh_value;
  ark.setSasoaWorkDir(thstring); string sn;
  if (verbose) cout << "SASOA_WORKDIR = "<< ark.getSasoaWorkDir() << endl;

  string dc = "rm -f ";
  dc += jj; 
  dc += " ";
  dc += thstring;
  dc += "/SA/delivery/*.*";

  if (verbose) cout << "TDSSrcNrgDaemon::process() executing "<< dc << endl;

  try{
  system(dc.c_str());
  } catch (const SAexception &se){
    cerr << "TDSSrcNrgDaemon::process() : errror in removing deliverable data" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in removing deliverable data" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in removing deliverable data" << endl;
  }

  string tc = "cp ";
  tc += jj; 
  tc += " ";
  tc += thstring;
  tc += "/SA/delivery/";

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


 if (verbose) cout << "TDSSrcNrgDaemon::process() here 3" << endl;
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

  if (verbose) cout << "TDSSrcNrgDaemon::process() launching attitude correction " << endl;

  try{
  system(bb.c_str());
  } catch (const SAexception &se){
    cerr << "TDSSrcNrgDaemon::process() : errror in attitude correction" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in attitude correction" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in attitude correction" << endl;
  }

  cout << "TDSSrcNrgDaemon::process() executing " << tc << endl;

try{
  system(tc.c_str());
  } catch (const SAexception &se){
    cerr << "TDSSrcNrgDaemon::process() : errror in copying attitude corrected eventlist" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in copying attitude corrected eventlist" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in copying attitude corrected eventlist" << endl;
  }
  


// if (argc<8) cout << "usage: ./runTDS_SRC <exp_datacard_out_filename> <sapoifilename> <ephfilename> <tstart> <tstop> <contactmin> <contactmax> <src_ra> <src_dec> <src_prefix>" << endl;
 

  string ephpath = mysystem.getEnvVar(here) + "/";
  string ephfile = ephpath + "eph_testout.fits";
  if (verbose) cout << "TDSSrcNrgDaemon::process() using ephemeris file " << ephfile << " for earth occultation filtering" << endl;

 //// Insert EXPOSURE_PROFILE
  ss.str(""); ss << src_ra; string ra = ss.str();
  ss.str(""); ss << src_dec; string dec = ss.str();

  string t1(ra), t2(dec); 
  string L3earthFilter="./launchSRCL3filter.sh " + t1; 
  L3earthFilter += " ";  
  L3earthFilter += t2;  
  L3earthFilter += " ";
  L3earthFilter += ephfile;
  L3earthFilter += " ";
  L3earthFilter += jj ;
  L3earthFilter += " " ;

  L3earthFilter += src_prefix ;
  
  if (verbose) cout << "TDSSrcNrgDaemon::process() executing " << L3earthFilter << endl;

  system(L3earthFilter.c_str());

  string l3flted = jj+ src_prefix+ "_earthfiltered";
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

  string mts = "autoEMI_SRC_new "+ts; mts += " "; 
  mts += ta1;  mts += " ";  mts += ta2;
  mts += " ";
  mts += src_prefix;
  mts += " ";
  mts += ra;
  mts += " ";
  mts += dec;

  cout << "executing " << mts.c_str() << endl;
  system(mts.c_str());

//--------------------------------------------
  ark.clearTempData();
  try{
  system(dc.c_str());
  } catch (const SAexception &se){
    cerr << "TDSSrcNrgDaemon::process() : errror in removing deliverable data" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in removing deliverable data" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in removing deliverable data" << endl;
  }
  mytime.stop();mytime.report();

}


/*!
    \fn TDSSrcNrgDaemon::processSRC()
 */
void TDSSrcNrgDaemon::processSRC()
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
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_HOME env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_HOME env var" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_HOME env var" << endl;
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

 if (verbose) cout << "TDSSrcNrgDaemon::process() here 3" << endl;
  sh_varname = "SASOA_WORKDIR"; 
  try{
   sh_value = mysystem.getEnvVar(sh_varname);
  } catch (const SAexception &se){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_HOME env var" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_HOME env var" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in getting SASOA_HOME env var" << endl;
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


 if (verbose) cout << "TDSSrcNrgDaemon::process() here 3" << endl;
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

  if (verbose) cout << "TDSSrcNrgDaemon::process() launching attitude correction " << endl;

  try{
  system(bb.c_str());
  } catch (const SAexception &se){
    cerr << "TDSSrcNrgDaemon::process() : errror in attitude correction" << se.getMsg() << endl;
  } catch (const exception &e){
    cerr << "TDSSrcNrgDaemon::process() : errror in attitude correction" << e.what() << endl;
  } catch (...){
    cerr << "TDSSrcNrgDaemon::process() : errror in attitude correction" << endl;
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
    \fn TDSSrcNrgDaemon::initArchiveEnv()
 */
void TDSSrcNrgDaemon::initArchiveEnv(ArchiveHandler *sarchiver, PipelineModule &pipemodule)
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
	cerr << "TDSSrcNrgDaemon::initArchiveEnv() error in initializing archiver environment "<< se.getMsg()<< endl;
}
catch(const exception & e){
	cerr << "TDSSrcNrgDaemon::initArchiveEnv() error in initializing archiver environment "<< e.what()<< endl;

}
}


/*!
    \fn TDSSrcNrgDaemon::setLocalHost(string lh)
 */
void TDSSrcNrgDaemon::setLocalHost(string lh)
{
    localhost = lh;
}

/*!
    \fn TDSSrcNrgDaemon::getLocalHost()
 */
string TDSSrcNrgDaemon::getLocalHost()
{
    return localhost;
}


/*!
    \fn TDSSrcNrgDaemon::setRemoteUser()
 */
void TDSSrcNrgDaemon::setRemoteUser(string ru)
{
    remoteuser = ru;
}


/*!
    \fn TDSSrcNrgDaemon::setRemoteHost()
 */
void TDSSrcNrgDaemon::setRemoteHost(string rh)
{
    remotehost = rh;
}


/*!
    \fn TDSSrcNrgDaemon::getRemoteHost()
 */
string TDSSrcNrgDaemon::getRemoteHost()
{
    return remotehost;
}


/*!
    \fn TDSSrcNrgDaemon::getRemoteUser()
 */
string TDSSrcNrgDaemon::getRemoteUser()
{
    return remoteuser;
}




/*!
    \fn TDSSrcNrgDaemon::launch_TDS_Src_nrg(double mtstart, double mtstop, double src_ra, double src_dec, string prefix, double emin, double emax)
 */
void TDSSrcNrgDaemon::launch_TDS_src_nrg(double mtstart, double mtstop, double msrc_ra, double msrc_dec, string prefix, double emin, double emax)
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

	//	contint = getContactRange(ntsa, ntso);
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() going on !!! "<< endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() input parameters are: "<< endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() tstart = "<< mtstart << endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() tstop = "<< mtstop << endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() ra = "<< msrc_ra << endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() dec = "<< msrc_dec << endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() src_prefix = "<< prefix << endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() energy min = "<< emin << endl;
	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() energy max = "<< emax << endl;
	src_ra = msrc_ra; 

	src_dec = msrc_dec;

	string gf; int nf; gf = "select * from ContactTable";	nf = 1;

	vector<string> sv;	
	//  vector<string>::iterator svi = sv.begin();
    dbp->loadDBDefaults();
    se.setMsg("TDSSrcNrgDaemon::launch_TDS_src_nrg() error in connecting to the database ");
    if (!dbp->createConnection()) throw se;

	contint = getContactRange(tstart, tstop);

	setContactMin(contint[0]);		setContactMax(contint[1]);

	cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() first value is " << contactmin << " last value is " << contactmax << endl;

	se.setMsg("TDSSrcNrgDaemon::launch_TDS_src_nrg() error in disconnecting the database ");
    if (!dbp->closeConnection()) throw se;

  } catch (const SAexception &se){
 cerr << "error " << se.getMsg() << endl;
  } catch (const exception &e){
   cerr << "error " << e.what() << endl;
  } catch (...){
   cerr << "error " <<  endl;
  }

		src_prefix = prefix;
		tempstring = "rm -f *.fits";syscon.execCommand(tempstring);
		tempstring = "rm cr.txt";syscon.execCommand(tempstring);
		tempstring = "rm -f *L3*.evt";syscon.execCommand(tempstring);


		cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg(): downloading files ..." << endl;

		ss.str("");ss << "./rsync_telemetry.sh " << getLocalHost() << " " << getRemoteHost() << " " << getRemoteUser() << " " << (contint[0] - 1) << " " << (contint[1] + 1) << endl;
		cout << "executing " << ss.str() << endl; 
		syscon.setVerbose(true);
		tempstring = ss.str();syscon.execCommand(tempstring);

		cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg(): downloaded telemetry data  ..." << endl;

		ss.str("");ss << "./rsync_l2file.sh " << getLocalHost() << " " << getRemoteHost() << " " << getRemoteUser() << " " << contint[0] << " " << contint[1] << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);

		cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg(): downloaded l2 data  ..." << endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() echo unzipping files ..." << endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() testing translating functions from " << endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() centint of tstart = " << tdbuilder.getCentString(contint[0])<< endl;
		cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() centint of tstop = " << tdbuilder.getCentString(contint[1])<< endl;
		
		tdbuilder.unzipAttRange(contint[0]-1, contint[1]+1);
		tdbuilder.unzipEphRange(contint[0]-1, contint[1]+1);
		tdbuilder.unzipL2Range(contint[0], contint[1]);
			
		//./tempdataset.sh $pars testout.fits
		ss.str("");ss << "./tempdataset.sh " << contint[0] << " " << contint[1] << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		
			// correcting merged data

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
			//process();
		} catch (const exception &e){
			cerr << " error in correcting the L2 events file" << e.what() << endl;
			//process();
		}
			delete sc2;
	try{
		process();
			} catch (const SAexception &se){
			cerr << " error in processing TDS SRC operations" << se.getMsg() << endl;
			//process();
		} catch (const exception &e){
			cerr << " error in correcting the L2 events file" << e.what() << endl;
			//process();
		}

		// removing local products
				
		int real_contactmin, real_contactmax;
		real_contactmin = contint[0] - 1;
		real_contactmax = contint[1] + 1;

		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() removing local files !"<< endl;

		try{
		ss.str("");ss << "./remove_telemetry.sh " << real_contactmin << " " << real_contactmax << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		} catch (const SAexception &se){
			cerr << " error in removing the telemetry" << se.getMsg() << endl;
		} catch (const exception &e){
			cerr << " error in removing the telemetry" << e.what() << endl;
		}
		try{
		ss.str("");ss << "./remove_l2file.sh " << real_contactmin << " " << real_contactmax << " " << outfile << endl;
		tempstring = ss.str();
		if (verbose) cout << "TDSSrcNrgDaemon::launch_TDS_src_nrg() executing " << tempstring << endl;
		syscon.execCommand(tempstring);
		} catch (const SAexception &se){
			cerr << " error in removing the L2 file" << se.getMsg() << endl;
		} catch (const exception &e){
			cerr << " error in removing the L2 file" << e.what() << endl;
		}
		
		exit(0);


}
}
}