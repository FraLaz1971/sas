#!/bin/sh
rm ../stg_2/attitude/version_for_sasoa/bin/prova_outfile_L3.evt 
cd ../stg_2/attitude/version_for_sasoa/src
../script/run_sal2_to_l3 ../datacards/datacard_new.card
exit
