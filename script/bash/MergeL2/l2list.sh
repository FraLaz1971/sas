#!/bin/sh

. ComDec/zip_utility.sh


createL2FileList ()
{
start_message "createL2FileList"
centstring $a CENTSTRING
START=$1
LIMITE=$2
rm temp3905files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  temp=$HOME"/SASOA/SA/products/processed/PKP"$a"_0_3905_000_L1"
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

# control input selection
end_message "createL2FileList"

}
