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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

set -o errexit

PROTO=$1
MACH64=$2

CONFDIR=${PROTO}/etc/apache2/2.4
MODULES_32_CONF=${CONFDIR}/conf.d/modules-32.load
MODULES_64_CONF=${CONFDIR}/conf.d/modules-64.load
APACHECTL64=${PROTO}/usr/apache2/2.4/bin/${MACH64}/apachectl
APACHE_BUILD_DIR32=${PROTO}/usr/apache2/2.4/build
APACHE_BUILD_DIR64=${PROTO}/usr/apache2/2.4/build/${MACH64}

mkdir -p ${CONFDIR}/conf.d
mkdir -p ${CONFDIR}/samples-conf.d
mkdir -p ${PROTO}/lib/svc/method

cp Solaris/modules-32.load Solaris/modules-64.load ${CONFDIR}/conf.d

# Strip LoadModule directives from httpd.conf. 
grep -v "^LoadModule " ${CONFDIR}/httpd.conf > ${CONFDIR}/original/httpd.conf

# Strip the 32-bit LoadModule directives from httpd.conf and put them in a
# separate file.
grep "^LoadModule " ${CONFDIR}/httpd.conf >> ${MODULES_32_CONF}
sed -f Solaris/loadmodules.sed ${MODULES_32_CONF} > ${MODULES_32_CONF}.new
mv ${MODULES_32_CONF}.new ${MODULES_32_CONF}

# Strip the 64-bit LoadModule directives from httpd.conf and put them in a
# separate file.
grep "^LoadModule " ${CONFDIR}/httpd.conf | sed -e "s;/;/64/;g" >> ${MODULES_64_CONF}
sed -f Solaris/loadmodules.sed ${MODULES_64_CONF} > ${MODULES_64_CONF}.new
mv ${MODULES_64_CONF}.new ${MODULES_64_CONF}

# Remove the bundled but disabled (by default) modules from modules-32.load,
# modules-64.load and create a sample .conf file for each of them.
for i in `sed -e 's/#.*//' -e '/^$/ d' Solaris/disabled-module.list`; do
  sed -e '/LoadModule.*'${i}'.so/ d' ${MODULES_32_CONF} > ${MODULES_32_CONF}.new
  mv ${MODULES_32_CONF}.new  ${MODULES_32_CONF}
  sed -e '/LoadModule.*'${i}'.so/ d' ${MODULES_64_CONF} > ${MODULES_64_CONF}.new
  mv ${MODULES_64_CONF}.new  ${MODULES_64_CONF}
  module_name=`echo ${i} | sed -e 's/^mod_//'`
  sed -e 's/::MODULE_NAME::/'${module_name}'/g' Solaris/sample-module.tmpl \
     > ${CONFDIR}/samples-conf.d/${module_name}.conf
done

# Add MACH64 specific dir info into SMF method.
sed "s/::ISAINFO::/\/${MACH64}/" Solaris/http-apache24 > ${PROTO}/lib/svc/method/http-apache24

# Add "-D 64" argument into 64 bit apachectl (if it's not there yet).
grep OPTS_64 ${APACHECTL64} > /dev/null || ( sed -e '/^case $ACMD in/i\
OPTS_64="-D 64bit"\
HTTPD="$HTTPD $OPTS_64"\
' ${APACHECTL64} > ${APACHECTL64}.new && mv ${APACHECTL64}.new ${APACHECTL64} )

# Since we are delivering mod_sed in separate package we don't want it in
# original httpd.conf file.
grep sed_module ${CONFDIR}/httpd.conf > /dev/null && \
grep -v sed_module ${CONFDIR}/httpd.conf > ${CONFDIR}/httpd.conf.new && \
mv ${CONFDIR}/httpd.conf.new ${CONFDIR}/httpd.conf

# Remove CBE specific paths for C compiler.
for i in ${APACHE_BUILD_DIR32}/config.nice \
	 ${APACHE_BUILD_DIR64}/config.nice \
	 ${APACHE_BUILD_DIR32}/config_vars.mk \
	 ${APACHE_BUILD_DIR64}/config_vars.mk;
do
  sed -e '/^.*CC *=/s,/.*/,,' \
      -e '/^.*CXX *=/s,/.*/,,' \
      -e '/MKDEP *=/s,/.*/,,' \
      -e '/\/configure/s,/.*/,.\/,' < ${i} > ${i}.new
  mv ${i}.new ${i}
done

# 64 bit rules.mk and special.mk should refer also to 64 bit build files.
for i in ${APACHE_BUILD_DIR64}/rules.mk \
	 ${APACHE_BUILD_DIR64}/special.mk
do
  sed -e "s/build\/config_vars/build\/${MACH64}\/config_vars/" \
      -e "s/build\/rules/build\/${MACH64}\/rules/" \
      -e "s/build\/instdso/build\/${MACH64}\/instdso/" < ${i} > ${i}.new
  mv ${i}.new ${i}
done
exit 0
