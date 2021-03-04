#! /bin/sh

#sasoa installing script 001
#info @ ftp://vesta.iasf-roma.inaf.it/pub/flazzarotto/UserManual/index.html
#control if it's the first execution
#if yes go on

if ["$1" = ""]; then
  echo 'usage: sasoa_createdirs <detnam>' 
else 
  #create needed directories
  echo  $HOME/SASOA/
  echo  $HOME/SASOA/$1
  echo  $HOME/SASOA/$1/conf
  echo  $HOME/SASOA/$1/data
  echo  $HOME/SASOA/$1/data/L1
  echo  $HOME/SASOA/$1/data/L19
  echo  $HOME/SASOA/$1/data/L2
  echo  $HOME/SASOA/$1/data/L3
  echo  $HOME/SASOA/$1/hk
  echo  $HOME/SASOA/$1/products
  echo  $HOME/SASOA/$1/reio
  echo  $HOME/SASOA/$1/software
  echo  $HOME/SASOA/$1/tables
  #copy IDL edm sources from pipeline directory
  echo -r ../edm_software/* $HOME/SASOA/$1/software
  echo
fi
#save what needed into the directories
