#!/bin/sh

. messages.sh
rsync_l2file ()
{
start_message "rsync_l2file"
START=$1
LIMITE=$2
temp=""
temp2=$HOME"/SASOA/SA/products/processed/"
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  temp=$HOME"/SASOA/SA/products/processed/PKP"$a"_0_3905_000_L1"
# create the filename string
#  echo "$temp/*L2.evt"
#  ls $temp/*L2.evt >> temp3905files.txt
  echo rsync_archive.sh "$temp" "$temp2"
  rsync_archive.sh "$temp" "$temp2"
# control if the directory exists

done

# create the merged table starting by the input file list

#( ordina )

# control input selection> rsync_l2file  888 999 
end_message "rsync_l2file"

}
rsync_l2file  $1 $2
