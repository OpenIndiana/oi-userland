#!/bin/bash

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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

PROTODIR=""
PYTHON=""
INSTALLDIR=""
LIBGCCDIR=""
MACH="`uname -p`"
SED="/usr/gnu/bin/sed"
STRIP="/usr/bin/strip -x"
# Solaris 11 uname does not support -o
UNAME="/usr/gnu/bin/uname"
GCC_FULL_VERSION=""

UNKNOWN_ARG=yes
PRINT_HELP=no

while [ "$#" -gt 0 ] ; do
  UNKNOWN_ARG=no
  case "$1" in
    -protodir=*)
      export PROTODIR=`echo $1 | ${SED} "s,^-protodir=\(.*\),\1,"`
      ;;
    -python=*)
      export PYTHON=`echo $1 | ${SED} "s,^-python=\(.*\),\1,"`
      ;;
    -gccversion=*)
      export GCC_FULL_VERSION=`echo $1 | ${SED} "s,^-gccversion=\(.*\),\1,"`
      ;;
    *)
      UNKNOWN_ARG=yes
      ;;
  esac

  if [ "$UNKNOWN_ARG" = "yes" ] ; then
    echo "$1: Invalid argument"
    PRINT_HELP=yes
    shift
    continue
  fi
  shift
done

if [ "$PRINT_HELP" = "yes" ] || [ "$UNKNOWN_ARG" = "yes" ] ; then
  echo ""
  echo "Usage: `basename $0` -protodir=[ build area prototype directory ]"
  echo "        -python=[ Python interpreter to use ]"
  echo ""
  exit 1
fi

if [ ${MACH} = "i386" ] ; then
  export MACH64="amd64"
  export VENDOR="pc"
else
  export MACH64="sparcv9"
  export VENDOR="sun"
fi

gcc_maj="`echo ${GCC_FULL_VERSION} | cut -d . -f 1`"
gcc_min="`echo ${GCC_FULL_VERSION} | cut -d . -f 2`"
GCC_VERSION="${gcc_maj}.${gcc_min}"

export RELEASE="`${UNAME} -r | cut -d . -f 2`"
export OS="`${UNAME} -o | /usr/gnu/bin/tr -s '[:upper:]' '[:lower:]'`"
export GCC_TRIPLE="${MACH}-${VENDOR}-${OS}2.${RELEASE}"

export MACH MACH64 SED STRIP GCC_VERSION GCC_FULL_VERSION PYTHON

export BINDIR="${PROTODIR}/usr/gcc/${GCC_VERSION}/bin"
export LIBDIR="${PROTODIR}/usr/gcc/${GCC_VERSION}/lib"
export LIB64DIR="${PROTODIR}/usr/gcc/${GCC_VERSION}/lib/${MACH64}"
export GCCSHAREDIR="${PROTODIR}/usr/gcc/${GCC_VERSION}/share"
export GCCUSRSHAREDIR="${PROTODIR}/usr/share/gcc-${GCC_FULL_VERSION}"
export GDBSHAREDIR="${PROTODIR}/usr/share/gdb"
export LIBGCCDIR="${PROTODIR}/usr/gcc/${GCC_VERSION}/lib/gcc"
export GCCTRIPLEDIR="${LIBGCCDIR}/${GCC_TRIPLE}/${GCC_FULL_VERSION}"
export LIBTRIPLEDIR="${LIBDIR}/gcc/${GCC_TRIPLE}/${GCC_FULL_VERSION}"

echo "Stripping GCC binaries ... "

for file in \
  c++ \
  cpp \
  g++ \
  gcc \
  gcc-ar \
  gcc-nm \
  gcc-ranlib \
  gcov \
  gfortran \
  ${GCC_TRIPLE}-c++ \
  ${GCC_TRIPLE}-g++ \
  ${GCC_TRIPLE}-gcc \
  ${GCC_TRIPLE}-gcc-${GCC_FULL_VERSION} \
  ${GCC_TRIPLE}-gcc-ar \
  ${GCC_TRIPLE}-gcc-nm \
  ${GCC_TRIPLE}-gcc-ranlib \
  ${GCC_TRIPLE}-gfortran
do
  ${STRIP} ${BINDIR}/${file}
done

for file in \
  libgfortran.so.3.0.0 \
  libgomp.so.1.0.0 \
  libitm.so.1.0.0 \
  libobjc.so.4.0.0 \
  libssp.so.0.0.0
do
  ${STRIP} ${LIBDIR}/${file}
  ${STRIP} ${LIB64DIR}/${file}
done

# libquadmath is not available on SPARC.
if [ "${MACH}" = "i386" ] ; then
  ${STRIP} ${LIBDIR}/libquadmath.so.0.0.0
  ${STRIP} ${LIB64DIR}/libquadmath.so.0.0.0
fi

for file in \
  cc1 \
  cc1obj \
  cc1plus \
  collect2 \
  f951 \
  liblto_plugin.so.0.0.0 \
  lto-wrapper \
  lto1
do
  ${STRIP} ${GCCTRIPLEDIR}/${file}
done

echo "... Done."
echo ""
echo "Copying GCC's gdb Python files ... "

mkdir -p ${GDBSHAREDIR}/auto-load/usr/lib/${MACH64}
mkdir -p ${GCCUSRSHAREDIR}/python/libstdcxx/v6

cp -p ${LIBDIR}/libstdc++.so.6.0.17-gdb.py ${GDBSHAREDIR}/auto-load/usr/lib/
cp -p ${LIB64DIR}/libstdc++.so.6.0.17-gdb.py ${GDBSHAREDIR}/auto-load/usr/lib/${MACH64}
cp -p ${GCCSHAREDIR}/gcc-${GCC_FULL_VERSION}/python/libstdcxx/__init__.py \
  ${GCCUSRSHAREDIR}/python/libstdcxx/
cp -p ${GCCSHAREDIR}/gcc-${GCC_FULL_VERSION}/python/libstdcxx/v6/__init__.py \
  ${GCCUSRSHAREDIR}/python/libstdcxx/v6/
cp -p ${GCCSHAREDIR}/gcc-${GCC_FULL_VERSION}/python/libstdcxx/v6/printers.py \
  ${GCCUSRSHAREDIR}/python/libstdcxx/v6/printers.py

cd ${GDBSHAREDIR}/auto-load/usr/lib/
${PYTHON} -m compileall .

cd ${GCCUSRSHAREDIR}/python/libstdcxx/
${PYTHON} -m compileall .

cd ${GCCUSRSHAREDIR}/python/libstdcxx/v6/
${PYTHON} -m compileall .

echo "... Done."
echo""
exit 0
