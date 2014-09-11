#!/usr/bin/ksh93

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

#
# Copyright (c) 2014, Oracle and/or its affiliates. All rights reserved.
#

set -o errexit

PROTO=$1

CONFDIR=${PROTO}/etc/apache2/2.4
APACHE_BUILD_DIR=${PROTO}/usr/apache2/2.4/build

# Postprocess list of DSO modules.
sed -f Solaris/loadmodules.sed ${CONFDIR}/httpd.conf > ${CONFDIR}/original/httpd.conf
cp ${CONFDIR}/original/httpd.conf ${CONFDIR}/httpd.conf

# Remove CBE specific paths for C compiler.
for i in ${APACHE_BUILD_DIR}/config.nice \
	 ${APACHE_BUILD_DIR}/config_vars.mk;
do
  sed -e '/^.*CC *=/s,/.*/,,' \
      -e '/^.*CXX *=/s,/.*/,,' \
      -e '/MKDEP *=/s,/.*/,,' \
      -e '/\/configure/s,/.*/,.\/,' < ${i} > ${i}.new
  mv ${i}.new ${i}
done

exit 0
