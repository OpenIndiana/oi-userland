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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_DIR=$1
COMPONENT_SRC=$2

export PATH=/bin:$PATH

# Replace the path to that under component build dir
gsed -i 's|\"etc\"|'\""$BUILD_DIR"'/etc\"|g' $COMPONENT_SRC/src/tests/test6.c
gsed -i 's|\"etc\"|'\""$BUILD_DIR"'/etc\"|g' $COMPONENT_SRC/src/tests/test8.c

# Make dirs under component build dir and copy necessary files under them
rm -rf $BUILD_DIR/etc/hsm.d
mkdir $BUILD_DIR/etc/hsm.d
cp $COMPONENT_SRC/etc/hsm.d/etoken-engine.xml $BUILD_DIR/etc/hsm.d
rm $BUILD_DIR/etc/objectIdentifiers.xml
cp $COMPONENT_SRC/etc/objectIdentifiers.xml $BUILD_DIR/etc
rm -rf $BUILD_DIR/etc/token.d
mkdir $BUILD_DIR/etc/token.d
cp $COMPONENT_SRC/etc/token.d/test.xml $BUILD_DIR/etc/token.d

# Replace the path to that under component build dir
sed -e 's|/$HOME|'"$BUILD_DIR"'/etc|g' $COMPONENT_SRC/etc/token.d/default.xml > $BUILD_DIR/etc/token.d/default.xml

# Copy .libpki dir under component build dir
rm -rf $BUILD_DIR/etc/.libpki
cp -R $COMPONENT_SRC/etc/.libpki $BUILD_DIR/etc

# Make results dir under component build dir
rm -rf $BUILD_DIR/results
mkdir $BUILD_DIR/results

# Build test scripts
gmake -C $BUILD_DIR/src/tests check-am

# Test scripts need escapes because they are executed indirectly
for i in {1..9}
do
	gsed -i 's|$libtool_install_magic|$$libtool_install_magic|g' $BUILD_DIR/src/tests/test$i
	gsed -i 's|$libtool_execute_magic|$$libtool_execute_magic|g' $BUILD_DIR/src/tests/test$i
	gsed -i 's|:$LD_LIBRARY_PATH|:$$LD_LIBRARY_PATH|g' $BUILD_DIR/src/tests/test$i
done
