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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =			lmdb
COMPONENT_VERSION =			0.9.23
COMPONENT_SUMMARY =			Lightning memory-mapped database library
COMPONENT_SRC =				lmdb-LMDB_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =			LMDB_$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =		sha256:abf42e91f046787ed642d9eb21812a5c473f3ba5854124484d16eadbe0aa9c81
COMPONENT_ARCHIVE_URL =			https://github.com/LMDB/lmdb/archive/LMDB_$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL =			https://github.com/LMDB/lmdb
COMPONENT_FMRI =			database/lmdb
COMPONENT_CLASSIFICATION =		System/Databases
COMPONENT_LICENSE =			OpenLDAP Public License
COMPONENT_LICENSE_FILE =		$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
