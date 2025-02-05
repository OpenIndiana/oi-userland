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
# Copyright 2024 Till Wegmüller
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libxxhash
COMPONENT_VERSION= 0.8.3
COMPONENT_SUMMARY= Extremely fast non-cryptographic hash algorithm
COMPONENT_PROJECT_URL= http://www.xxhash.com/
COMPONENT_SRC=		xxHash-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL= https://github.com/Cyan4973/xxHash/archive/refs/tags/v$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= sha256:db2c12e6f05d45546d3581b6881b25090fd65ab5194891da0b2a1a9c49beda66
COMPONENT_FMRI= library/$(COMPONENT_NAME)
COMPONENT_FMRI.xxhsum = sysutils/xxhsum
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= BSD 2-Clause License

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_INSTALL_ENV += PREFIX=$(USRDIR)
COMPONENT_INSTALL_ENV += LIBDIR=$(USRLIBDIR.64)
COMPONENT_INSTALL_ENV += MANDIR=$(USRSHAREMAN1DIR)

# For some reason the Makefile generates output under both usr and usr/local prefixes...
# For simplicity and cleaniness remove the usr/local version before the sample-manifest script
# generates it's output.
COMPONENT_POST_INSTALL_ACTION += rm -rf $(PROTO_DIR)/usr/local

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
