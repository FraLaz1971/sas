#! /bin/sh

#sasoa installation script 001
#modified 16/01/2007
#info @ ftp://vesta.iasf-roma.inaf.it/pub/flazzarotto/UserManual/index.html
#control if it's the first execution
#if yes go on
if  [ "$1" == "" ]; then
  echo 'usage: create_workenv.bash <detnam>'
else
  #create needed directories
  mkdir  $HOME/SASOA/
  mkdir  $HOME/SASOA/$1
  mkdir  $HOME/SASOA/$1/conf
  mkdir  $HOME/SASOA/$1/conf/old
  mkdir  $HOME/SASOA/$1/data
  mkdir  $HOME/SASOA/$1/data/L1
  mkdir  $HOME/SASOA/$1/data/L19
  mkdir  $HOME/SASOA/$1/data/L2
  mkdir  $HOME/SASOA/$1/data/L3
  mkdir  $HOME/SASOA/$1/hk
  mkdir  $HOME/SASOA/$1/products
  mkdir  $HOME/SASOA/$1/reio
  mkdir  $HOME/SASOA/$1/input
  mkdir  $HOME/SASOA/$1/software
  mkdir  $HOME/SASOA/$1/tables
  mkdir  $HOME/SASOA/$1/delivery
  mkdir  $HOME/SASOA/$1/archive  
  mkdir  $HOME/SASOA/$1/caldb
  mkdir  $HOME/SASOA/$1/caldb/strip
  mkdir  $HOME/SASOA/$1/caldb/strip/nsl
  mkdir  $HOME/SASOA/$1/caldb/strip/dsl
  mkdir  $HOME/SASOA/$1/caldb/strip/wsl
  mkdir  $HOME/SASOA/$1/caldb/gain
  mkdir  $HOME/SASOA/$1/caldb/address
  mkdir  $HOME/SASOA/$1/caldb/rmf
  mkdir  $HOME/SASOA/$1/catalog
  #copy IDL edm sources from pipeline directory
  cp -r ../stg_0_1/* $HOME/SASOA/$1/software
  cp ../tables/*.* $HOME/SASOA/$1/tables
 #copy input data file for test purpose
  #in default input data directory
  cp ../data/*.lv1 $HOME/SASOA/$1/data
  cd ../stg_2/attitude/
#  tar xvfz sal2_to_l3_ex_short.tar.gz
 # copy all the tables
  cd ..
  cp ../stg_0_1/tables/*.dsl $HOME/SASOA/$1/caldb/strip/dsl
  cp ../stg_0_1/tables/*.nsl $HOME/SASOA/$1/caldb/strip/nsl
  cp ../stg_0_1/tables/*.wsl $HOME/SASOA/$1/caldb/strip/wsl
  cp ../stg_0_1/tables/*.glt $HOME/SASOA/$1/caldb/gain
fi
#save what needed into the directories
