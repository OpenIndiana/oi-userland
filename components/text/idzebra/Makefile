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
# Copyright 2016 Alexander Pyhalov
#
BUILD_BITS=	64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= idzebra
COMPONENT_VERSION= 2.2.3
COMPONENT_SUMMARY= idzebra - text indexing and retrieval engine
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:85ade449d161d97df47d4a8910a53a5ea3bd5e3598b6189d86fc8986a8effea4
COMPONENT_ARCHIVE_URL=	https://ftp.indexdata.com/pub/zebra/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.indexdata.com/resources/software/zebra/
COMPONENT_FMRI= text/idzebra
COMPONENT_CLASSIFICATION = System/Text Tools
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = LICENSE.zebra

include $(WS_MAKE_RULES)/common.mk

# For tests to pass we should be very careful about files
COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D))

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -fi )

# Without this tests fail
unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '

# Remove trailing -2.0 from apps:
COMPONENT_POST_INSTALL_ACTION.32 = \
	( cd $(PROTO_DIR)/usr/bin/$(MACH32) && \
	  $(MV) ./idzebra-config-2.0 ./idzebra-config && \
	  $(MV) ./zebraidx-2.0 ./zebraidx && \
	  $(MV) ./zebrasrv-2.0 ./zebrasrv )

COMPONENT_POST_INSTALL_ACTION.64 = \
	( cd $(PROTO_DIR)/usr/bin && \
	  $(MV) ./idzebra-config-2.0 ./idzebra-config && \
	  $(MV) ./zebraidx-2.0 ./zebraidx && \
	  $(MV) ./zebrasrv-2.0 ./zebrasrv )

# Manually added build dependencies
REQUIRED_PACKAGES += runtime/tcl-8

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/yaz
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
