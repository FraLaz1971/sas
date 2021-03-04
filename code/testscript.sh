#/bin/sh

./sasoa 2> error.txt 1> out.txt &
xterm -T "SASOA error monitor"  &
xterm -T "SASOA output monitor" &
