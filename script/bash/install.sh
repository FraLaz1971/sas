#!/bin/bash
rm SasoaPilotBase.o
rm qsasoapilot.o
cd code
### GUI CREATION
uic-qt3 -o SasoaPilotBase.h SasoaPilotBase.ui
uic-qt3 -o SasoaPilotBase.cpp -impl SasoaPilotBase.h SasoaPilotBase.ui
moc-qt3 -o moc_SasoaPilotBase.cpp  SasoaPilotBase.h
cat include_moc_SasoaPilotBase.cpp SasoaPilotBase.cpp > SasoaPilotBase2.cpp
mv SasoaPilotBase2.cpp SasoaPilotBase.cpp
cd $OLDPWD
cp sas.pro temp.pro
rm sas.pro
mv temp.pro sas.pro
qmake-qt3 sas.pro
cd UI
./install.sh
cp config/config.hh config/config.h
cd $OLDPWD
make
cp code/*.sh .
./build_lib.sh sas
mkdir lib
mv libsas.a lib
cp lib/libsas.a $ADC/lib
cp code/*.h $ADC/include

