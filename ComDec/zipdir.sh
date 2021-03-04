#!/bin/sh
#
if [ "$#" != 2 ]
then
  echo "usage: unzipdir <dirname> <zip_type [gz|bz2]> "
else
  if [ $2 == "gz" ]
  then
	  echo "compressing files ... (gzip) "
	  gzip  -f $1/*.*
  else

  if [ $2 == "bz2" ]
  then
	  echo "compressing files ... (bzip2) "
	  bzip2 -f $1/*.*
  else
  	echo "unknown compression type"
  fi
  fi

fi

echo "elapsed seconds: " $SECONDS
date
echo bye bye
