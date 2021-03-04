#!/bin/sh

# returns the cent string of sasoa archive
# in the variable passed as second parameter

function centstring ()
{
v=$1
let "n=6-${#1}"
v=0
stringa="$1"
#n="#1"
while [ "$v" -lt "$n"  ]
do
 let "v+=1"
 stringa="0"$stringa
done
finale="XX"
stringa=${stringa:0:4}${finale}
 eval "$2"='$stringa'
}


#. ../messages.sh
unzipAttRange()
{
# unzip attitude files from contact $1 to contact $2
start_message "unzipAttRange"
START=$1
LIMITE=$2
rm temp3914files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring "$a" CENTSTRING
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
    echo "executing ./unzipdir.sh $temp bz2"
    ComDec/unzipdir.sh $temp bz2
    ls $temp/*.*

    # unzippa tutti (i 3914 solo ?) in quella directory
  else
    echo "the directory $temp is not present"
  fi
done
end_message "unzipAttRange"
}

unzipEphRange()
{
# unzip ephemeredes files from contact $1 to contact $2
start_message "unzipEphRange"
START=$1
LIMITE=$2
rm temp3916files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring "$a" CENTSTRING
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
    echo "executing ./unzipdir.sh $temp bz2"
    ComDec/unzipdir.sh $temp bz2
    ls $temp/*.*

    # unzippa tutti (i 3916 solo ?) in quella directory
    #unzippa tutto in quella directory
  else
    echo "the directory $temp is not present"
  fi
done
end_message "unzipEphRange"

}

unzipL2Range()
{
# unzip L2 files from contact $1 to contact $2
start_message "unzipL2Range"
START=$1
LIMITE=$2
rm temp3905files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring "$a" CENTSTRING
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
    echo "executing ./unzipdir.sh $temp gz"
    ComDec/unzipdir.sh $temp gz
    ls $temp/*.*
  else
    echo "the directory $temp is not present"
  fi

done

# create the merged table starting by the input file list

#( ordina )

# control input selection
end_message "unzipL2Range"
}
zipAttRange()
{
# unzip attitude files from contact $1 to contact $2
START=$1
LIMITE=$2
rm temp3914files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring "$a" CENTSTRING
  temp=$HOME"/SASOA/SA/input/"$CENTSTRING"/00"$a
# create the filename string
#  echo "$temp/*3914*.lv1" | sed s/.lv1/.lv1[events]/
#  ls $temp/*3914*.lv1 | sed s/.lv1/.lv1[events]/ >> temp3914files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo "zipping in " $temp
    echo "executing ./zipdir.sh $temp gz"
    ComDec/zipdir.sh $temp gz
    ls $temp/*.gz
    # unzippa tutti (i 3914 solo ?) in quella directory
  else
    echo "the directory $temp is not present"
  fi
done
end_message "unzipL2Range"
}

zipEphRange()
{
# unzip ephemeredes files from contact $1 to contact $2
start_message "zipEphRange"
START=$1
LIMITE=$2
rm temp3916files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring "$a" CENTSTRING
  temp=$HOME"/SASOA/SA/input/"$CENTSTRING"/00"$a
# create the filename string
#  echo "$temp/*3916*.lv1" | sed s/.lv1/.lv1[events]/
#  ls $temp/*3916*.lv1 | sed s/.lv1/.lv1[events]/ >> temp3916files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo "zipping in " $temp
    ComDec/zipdir.sh $temp gz
    ls $temp/*.gz
    echo "executing ./zipdir.sh $temp gz"
    # unzippa tutti (i 3916 solo ?) in quella directory
    #unzippa tutto in quella directory
  else
    echo "the directory $temp is not present"
  fi
done
end_message "zipEphRange"

}

zipL2Range()
{
# unzip L2 files from contact $1 to contact $2
start_message "zipL2Range"
START=$1
LIMITE=$2
rm temp3905files.txt
temp=""
for ((a=$START; a <= LIMITE; a++)) # Doppie parentesi, e "LIMITE" senza "$".
do
  centstring "$a" CENTSTRING
  temp=$HOME"/SASOA/SA/products/processed/PKP"$a"_0_3905_000_L1"
# create the filename string
  #echo "$temp/*L2.evt"
  #ls $temp/*L2.evt >> temp3905files.txt
# control if the directory exists
  if [ -e  "$temp" ]
  then
    echo "zipping in " $temp
    echo "executing ./zipdir.sh $temp bz2"
    ComDec/zipdir.sh $temp bz2
    ls $temp/*.bz2
  else
    echo "the directory $temp is not present"
  fi

done

# create the merged table starting by the input file list

#( ordina )

# control input selection
end_message "zipL2Range"
}

#getAttContactDir () {
#take contact in input and gives Attitude dir for that contact
#}

#getEphContactDir () {
#take contact in input and gives Ephemeredes dir for that contact

#}

#getL2ContactDir () {
#take contact in input and gives L2 dir for that contact

#}


#unzipAttRange $1 $2
#unzipEphRange $1 $2
#unzipL2Range $1 $2
#zipAttRange $1 $2
#zipEphRange $1 $2
#zipL2Range $1 $2
