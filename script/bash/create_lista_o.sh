#!/bin/bash
ls *.o > lista_o.txt
rm create_saslib.sh
./script_lista_o.sh lista_o.txt
chmod +x create_saslib.sh
