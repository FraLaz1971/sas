#!/bin/sh
rm ../stg_2/attitude/version_for_sasoa/testfiles/sapoi_sasoa.fits 
cd ../stg_2/attitude/version_for_sasoa/src
../bin/quat_to_sapoi.exe ../datacards/quat_to_sapoi_fixed-time.card
exit
