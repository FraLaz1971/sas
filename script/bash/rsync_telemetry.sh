#!/bin/sh
. ComDec/zip_utility.sh
. messages.sh
rsync_telemetry ()
{
start_message "rsync_telemetry"
START=$1
LIMITE=$2
rm temp3916files.txt
temp=""
temp2=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring $a CENTSTRING
  temp=$HOME"/SASOA/SA/input/"$CENTSTRING"/00"$a
  temp2=$HOME"/SASOA/SA/input/"$CENTSTRING"/"
  echo rsync_archive.sh $temp $temp2
  ./rsync_archive.sh $temp $temp2

# create the filename string
#  echo "$temp/*3916*.lv1" | sed s/.lv1/.lv1[events]/
#  ls $temp/*3916*.lv1 | sed s/.lv1/.lv1[events]/ >> temp3916files.txt
# control if the directory exists
done
end_message "rsync_telemetry"
}
rsync_telemetry $1 $2