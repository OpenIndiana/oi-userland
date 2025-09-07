#!/usr/bin/ksh
#
# Copyright (c) 2008, 2025, Oracle and/or its affiliates.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
###########################################################################
#
#

PATH=/usr/bin:/usr/sbin

. /lib/svc/share/smf_include.sh

if ! is_self_assembly_boot; then
	exit $SMF_EXIT_OK
fi

getprop() {
    PROPVAL=""
    svcprop -q -p $1 application/font/fc-cache
    if [ $? -eq 0 ] ; then
	PROPVAL=$(svcprop -p $1 application/font/fc-cache)
	if [ "$PROPVAL" == "\"\"" ] ; then
	    PROPVAL=""
	fi
	return
    fi
    return
}

ARGS=""
POSTCMD=""
RETVAL=$SMF_EXIT_OK

getprop options/force_rebuild
if [ "$PROPVAL" = "true" ] ; then
    ARGS="$ARGS -f"
    POSTCMD="svccfg -s application/font/fc-cache setprop options/force_rebuild=false"
fi

case "$(uname -p)" in
    sparc)	ARCH32="sparcv7" ARCH64="sparcv9" ;;
    i386)	ARCH32="i86" ARCH64="amd64" ;;
    *)		echo "Unknown architecture $(uname -p)"
    		exit $SMF_EXIT_ERR_FATAL ;;
esac

# Clean out obsolete cache-file versions - current version is *.cache-9
/usr/bin/find /var/cache/fontconfig -name '*.cache-[2-8]' -exec /bin/rm \{\} \+

# Run 32-bit & 64-bit cache builds in parallel
/usr/bin/${ARCH32}/fc-cache $ARGS &
pid32=$!

/usr/bin/fc-cache $ARGS &
pid64=$!

wait $pid32
if [ $? -ne 0 ] ; then
    RETVAL=$SMF_EXIT_MON_DEGRADE
fi

wait $pid64
if [ $? -ne 0 ] ; then
    RETVAL=$SMF_EXIT_MON_DEGRADE
fi

if [ "$POSTCMD" != "" ] ; then
    eval $POSTCMD
fi

exit $RETVAL

