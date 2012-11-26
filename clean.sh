#!/bin/sh
for i in `ls -1 src/`; do
	if [ -d src/$i -a -f src/$i/Makefile ]; then
		make -sC src/$i clean
	fi
done
