#!/bin/sh
echo "removing CVS "
rm -r CVS
rm -r */CVS
rm -r */*/CVS
rm -r */*/*/CVS
echo "done"
