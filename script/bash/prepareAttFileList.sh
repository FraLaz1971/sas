#!/bin/sh
# read each riga in the input file
rm plain3914files.txt	 
FILE=$1
{
while read riga
do
  echo $riga | sed s/"\[events\]"//  >> plain3914files.txt
done
}<$FILE
