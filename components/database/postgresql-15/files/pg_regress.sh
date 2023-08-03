#!/bin/sh
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
#ident	"@(#)pg_regress.sh	1.1	09/10/13 SMI"

# Wrapper to run pg_regress using the test suite installed
# with the PostgreSQL packages

PG_ROOT=/usr/postgres/15

# Default values for arguments

REG_ROOT=${PG_ROOT}/lib/64/regress
PSQL_DIR=/usr/bin
PGREG_BIN=${PG_ROOT}/lib/64/pgxs/src/test/regress/pg_regress
PGREG_TMP=/var/tmp/pg_regress_15

if [ '$1' = '--help' ] ; then
  cat <<EOF
Usage: pg_regress.sh
         [--suite <testsuite>]
         [--bindir <psql-dir>]
         [--driver <pg_regress binary>]
         [<pg_regress args>]

<testsuite> is the path to the installed test suite.
  (default $REG_ROOT)

<psql-dir> - ignored

<pg_regress> is the path to the pg_regress test driver binary.
  (default $PGREG_BIN)

These three options (if used) can be in any order.

Additional arguments are passed on to pg_regress.  Typically, this
will be --schedule=<schedule file>.

The PostgreSQL server must already be running on the same host.
The environment variable PGPORT must be set if the server is not using
the default 5432.

A copy of the testsuite as well as output, will be placed in the directory
/var/tmp/pg_regress_15 and subdirectories; any previous contents will be
removed before the test starts.
EOF
exit 0
fi

if echo $* | grep -- --top-builddir > /dev/null ; then
  echo "\"--top-builddir\" option is not available for this packaged test driver."
  echo "Please start your PostgreSQL server separately."
  exit 1
fi

parse=true

while [ $parse = true ] ; do
  case $1 in
    '--suite' )
      REG_ROOT=$2
      shift 2
      ;;
    '--bindir' )
      PSQL_DIR=$2
      shift 2
      ;;
    '--driver' )
      PGREG_BIN=$2
      shift 2
      ;;
    * )
      parse=false
      ;;
  esac
done

# pg_regress really only works with write permission on input directory,
# so need to create a similar directory structure to satisfy it

if [ -d "$PGREG_TMP" ] ; then
  /usr/bin/rm -rf "${PGREG_TMP}"
fi
mkdir -p "${PGREG_TMP}"


cd "${PGREG_TMP}"
cp -pR $REG_ROOT/* .

chmod o+w sql expected
mkdir results testtablespace

exec $PGREG_BIN $*
