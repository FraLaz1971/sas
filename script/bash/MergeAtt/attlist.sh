#!/bin/sh

. ComDec/zip_utility.sh

createAttFileList ()
{
start_message "createAttFileList"
START=$1
LIMITE=$2
rm temp3914files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring $a CENTSTRING
  temp=$HOME"/SASOA/SA/input/"$CENTSTRING"/00"$a
# create the filename string
  echo "$temp/*3914*.lv1" | sed s/.lv1/.lv1[events]/
  ls $temp/*3914*.lv1 | sed s/.lv1/.lv1[events]/ >> temp3914files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo
  else
    echo "the directory $temp is not present"
  fi
done
end_message "createAttFileList"
}
