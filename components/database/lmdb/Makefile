#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Rouven Weiler
#

BUILD_BITS= 64_and_32
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =			lmdb
COMPONENT_VERSION =			0.9.31
COMPONENT_SUMMARY =			Lightning memory-mapped database library
COMPONENT_SRC =				openldap-LMDB_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =			$(COMPONENT_SRC).tar.bz2
COMPONENT_PROJECT_URL =		https://www.symas.com/lmdb
COMPONENT_ARCHIVE_URL =		https://git.openldap.org/openldap/openldap/-/archive/LMDB_$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH =	sha256:2132b8261d241876ce5fe10a243b2f7e0127eecaaff30039573eadc09e3acee6
COMPONENT_FMRI =			database/lmdb
COMPONENT_CLASSIFICATION =	System/Databases
COMPONENT_LICENSE =			OpenLDAP Public License

include $(WS_MAKE_RULES)/common.mk

COMPONENT_COPY_ACTION = $(CP) -r $(SOURCE_DIR)/libraries/liblmdb/* $(@D)

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS) -pthread"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ARGS += SOVERSION="$(COMPONENT_VERSION)"

COMPONENT_INSTALL_ARGS += bindir="$(USRBINDIR.$(BITS))"
COMPONENT_INSTALL_ARGS += includedir="$(USRINCDIR)"
COMPONENT_INSTALL_ARGS += libdir="$(USRLIBDIR.$(BITS))"
COMPONENT_INSTALL_ARGS += mandir="$(USRSHAREMANDIR)"
COMPONENT_INSTALL_ARGS += SOVERSION="$(COMPONENT_VERSION)"

COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_ARGS += CC="$(CC)"
COMPONENT_TEST_ARGS += CFLAGS="$(CFLAGS) -pthread"
COMPONENT_TEST_ARGS += LDFLAGS="$(LDFLAGS)"
COMPONENT_TEST_ARGS += SOVERSION="$(COMPONENT_VERSION)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
