#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2013, Aurelien Larcher. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cunit
COMPONENT_VERSION=      2.1.3
COMPONENT_FMRI=         developer/cunit
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_SUMMARY=     	Automated testing framework for C
COMPONENT_SRC_NAME=	CUnit
COMPONENT_SRC_VERSION=  2.1-3
COMPONENT_SRC=          $(COMPONENT_SRC_NAME)-$(COMPONENT_SRC_VERSION)
COMPONENT_PROJECT_URL=	http://cunit.sourceforge.net/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:f5b29137f845bb08b77ec60584fdb728b4e58f1023e6f249a464efa49a40f214
COMPONENT_ARCHIVE_URL= \
    http://sourceforge.net/projects/cunit/files/CUnit/$(COMPONENT_SRC_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      LGPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && \
                          aclocal -I m4 --install && \
                          libtoolize -i && \
                          autoheader  && \
                          automake --add-missing --include-deps --copy && \
                          autoconf && \
                          chmod u+x configure && \
                          $(RM) config.status)

CONFIGURE_OPTIONS+= --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-memtrace
CONFIGURE_OPTIONS+= --enable-automated
CONFIGURE_OPTIONS+= --enable-basic
CONFIGURE_OPTIONS+= --enable-console
CONFIGURE_OPTIONS+= --enable-examples
CONFIGURE_OPTIONS+= --enable-test

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

CUNIT_TESTDIR=CUnit/Sources/Test
CUNIT_TESTBIN=test_cunit

test: $(TEST_32_and_64)
	pushd $(BUILD_DIR_32)/$(CUNIT_TESTDIR); ./$(CUNIT_TESTBIN); popd; 
	pushd $(BUILD_DIR_64)/$(CUNIT_TESTDIR); ./$(CUNIT_TESTBIN); popd; 

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
