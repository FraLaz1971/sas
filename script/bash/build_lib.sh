#!/bin/sh
ls *.o > lista_o.txt
rm create_lib.sh
./script_lista_o.sh lista_o.txt $1
chmod +x create_lib.sh
./create_lib.sh