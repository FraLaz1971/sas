#!/bin/sh
#
if [ "$#" != 2 ]
then
  echo "usage: unzipdir <dirname> <zip_type [gz|bz2]> "
else
  if [ $2 == "gz" ]
  then
	  echo "uncompressing files ... (gzip) "
	  gzip -d -f $1/*.gz
  else

  if [ $2 == "bz2" ]
  then
	  echo "uncompressing files ... (bzip2) "
	  bunzip2 -f $1/*.bz2
  else
  	echo "unknown compression type"
  fi
  fi

fi

echo "elapsed seconds: " $SECONDS
date
echo bye bye
