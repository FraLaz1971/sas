#!/bin/sh

. ComDec/zip_utility.sh

createEphFileList ()
{
start_message createEphFileList
centstring $a CENTSTRING
START=$1
LIMITE=$2
rm temp3916files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring $1 CENTSTRING
  temp="/home/agile/SASOA/SA/input/"$CENTSTRING"/00"$a
# create the filename string
  echo "$temp/*3916*.lv1"
  ls $temp/*3916*.lv1 >> temp3916files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo
  else
    echo "the directory $temp is not present"
  fi 
done 
end_message createEphFileList
}