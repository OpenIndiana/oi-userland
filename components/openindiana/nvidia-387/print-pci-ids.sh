#!/bin/sh
#
# Pass the source directory and get a list of driver aliases in return.

eval "$(egrep '^A[1-9][0-9]*=|^ALIASES=' $1/NVDAgraphicsr/install/postinstall)"

for i in $ALIASES; do
	printf "\talias=$i \\\\\n"
done
