#!/bin/sh

eval `grep ^A $1/NVDAgraphicsr/install/postinstall`

for i in $ALIASES; do
	printf "\talias=$i \\\\\n"
done


