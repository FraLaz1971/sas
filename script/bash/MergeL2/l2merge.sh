#!/bin/sh

echo "executing  $0 : merge L2 SA data, by SuperAGILE software team"

if [ "$#" != 3 ]
then
  echo "usage : l2merge <start_orbit> <end_orbit> <outfile>"
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
  echo "output file name is $3"
fi
START=$1
LIMITE=$2
rm temp3905files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  temp="/home/agile/SASOA/SA/products/processed/PKP"$a"_0_3905_000_L1"
# create the filename string
  echo "$temp/*L2.evt"
  ls $temp/*L2.evt >> temp3905files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo
  else
    echo "the directory $temp is not present"
  fi 
done 

# create the merged table starting by the input file list 

#( ordina )

ftmerge @temp3905files.txt $3
 
fi


# control input selection



date
echo "bye bye"
