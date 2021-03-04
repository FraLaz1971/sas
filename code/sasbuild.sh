#!/bin/sh
rm $1
./sascompile.sh $1
./saslink.sh $1
