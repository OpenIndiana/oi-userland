#!/bin/sh
#
# Pass the source directory and get a list of driver aliases in return.

eval "$(egrep '^A[1-9][0-9]*=|^ALIASES=' $1/NVDAgraphicsr/install/postinstall)"

FIRST=yes
for i in $ALIASES; do
	[ "$FIRST" = no ] && printf " \\\\\n" || FIRST=no
	printf "\talias=$i"
done
echo ""
