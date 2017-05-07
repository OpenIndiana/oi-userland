#!/bin/ksh -p
#
# Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, and/or sell copies of the Software, and to permit persons
# to whom the Software is furnished to do so, provided that the above
# copyright notice(s) and this permission notice appear in all copies of
# the Software and that both the above copyright notice(s) and this
# permission notice appear in supporting documentation.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
# OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
# INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# Except as contained in this notice, the name of a copyright holder
# shall not be used in advertising or otherwise to promote the sale, use
# or other dealings in this Software without prior written authorization
# of the copyright holder.
#
###########################################################################
#

PATH=/usr/bin:/usr/sbin

. /lib/svc/share/smf_include.sh

USAGE="Usage: $0 { start | refresh }"

if [ $# -ne 1 ] ; then
    echo $USAGE
    exit 2
fi

CATALOG_INSTALL=/usr/share/sgml/docbook/docbook-catalog-install.sh
CATALOG_UNINSTALL=/usr/share/sgml/docbook/docbook-catalog-uninstall.sh

start_docbook_catalog_update ()
{
  #if [ ! -f /etc/xml/catalog -o $CATALOG_INSTALL -nt /etc/xml/catalog ]; then
      $CATALOG_INSTALL
  #fi
}

refresh_docbook_catalog_update ()
{
  #if [ ! -f /etc/xml/catalog -o $CATALOG_INSTALL -nt /etc/xml/catalog ]; then
      $CATALOG_UNINSTALL > /dev/null 2>&1
      $CATALOG_INSTALL
  #fi
}

METHOD=$1

case "$METHOD" in
    'start')
	# Continue with rest of script
	;;
    'refresh')
	# Continue with rest of script
	;;
    -*)
	echo $USAGE
	exit 2
	;;
    *)
	echo "Invalid method $METHOD"
	exit 2
	;;
esac

${METHOD}_docbook_catalog_update

exit $SMF_EXIT_OK
