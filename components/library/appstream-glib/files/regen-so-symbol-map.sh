#! /bin/sh

#
# Author  : Tim Mooney <Tim.Mooney@ndsu.edu>
# Purpose : run this against the libappstream.glib.so.* to generate an ld
#           map that works with the OI linker.
# Requires: /usr/bin/nm, /usr/bin/awk, /usr/bin/grep, /usr/bin/sort
#
# appstream-glib ships with a ld "version script" to control symbol
# visibility in the SO, but it apparently is using a Linux-ism for
# the symbols that should be global:
#
#	{
#	global:
#	    as_*;
#	local:
#	    *;
#	};
#
# Since libappstream-glib will undoubtedly add symbols that should be visible
# as development continues, this script can be used to regenerate the map
# file.
#

PATH=/usr/bin; export PATH

if test $# -ne 1 ; then
	echo "$0: usage: $0 path/to/libappstream-glib.so.#.*" >&2
	exit 1
fi

echo '{'           > appstream-glib.map
echo 'global:'    >> appstream-glib.map 

for g in `nm -p "$1" | awk '{ print $3 }' | grep '^as_.*' | sort -u`
do
	# skip as_* as a literal symbol, it should only incorrectly appear
	# the first time you use the broken map file.
	if test X"$g" = X'as_*' ; then
		continue
	fi
	echo "    $g;" >> appstream-glib.map
done

echo 'local:'     >> appstream-glib.map 
echo '    *;'     >> appstream-glib.map 
echo '};'         >> appstream-glib.map

echo 'Regenerated appstream-glib.map, please review'
exit 0
