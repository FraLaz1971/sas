/***************************************************************************
                          tempdatasetbuilder.cpp  -  description
                             -------------------
    begin                : Wed Dec 12 2007
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

#include "tempdatasetbuilder.h"

namespace SApipeline{
namespace TDS {
TempDataSetBuilder::TempDataSetBuilder(){
}
TempDataSetBuilder::~TempDataSetBuilder(){
}
}
}

/*!
    \fn SApipeline::TDS::TempDataSetBuilder::unzipAttRange()
 */
void SApipeline::TDS::TempDataSetBuilder::unzipAttRange(int contactmin, int contactmax)
{
	try{
		ss.str("");ss << "./unzipAttRange.sh " << contactmin << " " << contactmax << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);
	} catch (const exception &e){
		cerr << "TempDataSetBuilder::unzipAttRange() error in " << e.what() << endl;
	}
/*
# unzip attitude files from contact $1 to contact $2
start_message "unzipAttRange"
START=$1
LIMITE=$2
rm temp3914files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring $a CENTSTRING
  temp=$HOME"/SASOA/SA/input/"$CENTSTRING"/00"$a
# create the filename string
#  echo "$temp/*3914*.lv1" | sed s/.lv1/.lv1[events]/
#  ls $temp/*3914*.lv1 | sed s/.lv1/.lv1[events]/ >> temp3914files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo "unzipping in " $temp
    echo "executing ./unzipdir.sh $temp gz"
    ComDec/unzipdir.sh $temp gz
    ls $temp/*.*

    # unzippa tutti (i 3914 solo ?) in quella directory
  else
    echo "the directory $temp is not present"
  fi
done
end_message "unzipAttRange"
*/

}


/*!
    \fn SApipeline::TDS::TempDataSetBuilder::unzipEphRange()
 */
void SApipeline::TDS::TempDataSetBuilder::unzipEphRange(int contactmin, int contactmax)
{
	try{
		ss.str("");ss << "./unzipEphRange.sh " << contactmin << " " << contactmax << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);
	} catch (const exception &e){
		cerr << "TempDataSetBuilder::unzipAttRange() error in " << e.what() << endl;
	}

/*
# unzip ephemeredes files from contact $1 to contact $2
start_message "unzipEphRange"
START=$1
LIMITE=$2
rm temp3916files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring $a CENTSTRING
  temp=$HOME"/SASOA/SA/input/"$CENTSTRING"/00"$a
# create the filename string
#  echo "$temp/*3916*.lv1" | sed s/.lv1/.lv1[events]/
#  ls $temp/*3916*.lv1 | sed s/.lv1/.lv1[events]/ >> temp3916files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo "unzipping in " $temp
    echo "executing ./unzipdir.sh $temp gz"
    ComDec/unzipdir.sh $temp gz
    ls $temp/*.*

    # unzippa tutti (i 3916 solo ?) in quella directory
    #unzippa tutto in quella directory
  else
    echo "the directory $temp is not present"
  fi
done
end_message "unzipEphRange"

*/

}


/*!
    \fn SApipeline::TDS::TempDataSetBuilder::unzipL2Range()
 */
void SApipeline::TDS::TempDataSetBuilder::unzipL2Range(int contactmin, int contactmax)
{
	try{
		ss.str("");ss << "./unzipL2Range.sh " << contactmin << " " << contactmax << endl;
		tempstring = ss.str();syscon.execCommand(tempstring);
	} catch (const exception &e){
		cerr << "TempDataSetBuilder::unzipAttRange() error in " << e.what() << endl;
	}


/*
# unzip L2 files from contact $1 to contact $2
start_message "unzipL2Range"
START=$1
LIMITE=$2
rm temp3905files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring $a CENTSTRING
  temp=$HOME"/SASOA/SA/products/processed/PKP"$a"_0_3905_000_L1"
# create the filename string
  #echo "$temp/*L2.evt"
  #ls $temp/*L2.evt >> temp3905files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo "unzipping in " $temp
    echo "executing ./unzipdir.sh $temp bz2"
    ComDec/unzipdir.sh $temp bz2
    ls $temp/*.*
  else
    echo "the directory $temp is not present"
  fi

done

# create the merged table starting by the input file list

#( ordina )

# control input selection
end_message "unzipL2Range"
*/
}


/*!
    \fn SApipeline::TDS::TempDataSetBuilder::getCentString(int contact)
 */
string SApipeline::TDS::TempDataSetBuilder::getCentString(int contact)
{
	ss.str("");	ss << contact;
	string cs(ss.str());
	int n = 6 - cs.size();
	string z("0");
	int v = 0;
	while (v < n){
		v++;	cs = "0" + cs; 
	}
	string finale("XX");
	cs = cs.substr(0, 4) + finale; 
	cout << "TempDataSetBuilder::getCentString() returning " << cs << endl;
	return cs;
}
