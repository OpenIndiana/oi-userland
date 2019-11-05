#!/bin/sh

# NB! needs bsdtar/libarchive v2.8+

PATH=/bin:/usr/bin

if [ $# -eq 0 -a ! -t 0 ]; then
	f=/dev/stdin
elif [ $# -eq 1 ]; then
	f=$1
else
	echo Usage: rpm2cpio [file.rpm]
	echo dumps the contents to stdout as a GNU cpio archive
	exit 0
fi

/usr/bin/bsdtar cf - --format=newc @- < ${f}
