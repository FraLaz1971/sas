#!/bin/sh
mv temp3905files.txt last3905files.log
mv temp3916files.txt last3916files.log
mv temp3914files.txt last3914files.log


. MergeL2/l2list.sh
. MergeAtt/attlist.sh
. MergeEph/ephlist.sh
. messages.sh

echo "executing  $0 : merge L2 SA data, by SuperAGILE software team"

if [ "$#" != 3 ]
then
  echo "usage : tempdataset <start_orbit> <end_orbit> <outfile>"
  echo "prefix will be added to selected outfile"
  echo "input error: you entered "$#" parameter(s) "
else 
  echo "OK running"
if [ -n "$1" ]
then
  echo "starting contact number is $1"
fi

if [ -n "$2" ]
then
  echo "ending contact number is $2"
fi

if [ -n "$3" ]
then
  echo "eph_ prefix will be added to selected outfile"
  echo "output file name is eph_$3"
fi
start_message saenhanced

# create the merged table starting by the input file list 

#( ordina )

#ftmerge @temp3905files.txt l2_$3

createL2FileList $1 $2 $3

createAttFileList $1 $2 $3
#the list is not used to merge 3914 
#but the list is passed to the attitude datacard
./prepareAttFileList.sh temp3914files.txt
let b1=$(( $1 - 1 ))
let b2=$(( $2 + 1 ))
createEphFileList $b1 $b2 $3

echo "going to exec ftmerge @temp3905files.txt l2_$3"
ftmerge @temp3905files.txt l2_$3
echo "going to exec ftmerge @temp3916files.txt eph_$3"
ftmerge @temp3916files.txt eph_$3
 
fi


# control input selection


end_message saenhanced

date
echo "bye bye"
