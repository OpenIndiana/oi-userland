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
BUILD_BITS=	64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= idzebra
COMPONENT_VERSION= 2.2.7
COMPONENT_SUMMARY= idzebra - text indexing and retrieval engine
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b465ffeb060f507316e6cfc20ebd46022472076d0d4e96ef7dab63e798066420
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

CONFIGURE_OPTIONS += --enable-static=no

# Without this tests fail
unexport SHELLOPTS

COMPONENT_POST_INSTALL_ACTION = ( \
	cd $(PROTO_DIR)/usr/bin && \
	$(MV) ./idzebra-config-2.0 ./idzebra-config && \
	$(MV) ./zebraidx-2.0 ./zebraidx && \
	$(MV) ./zebrasrv-2.0 ./zebrasrv )

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/yaz
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
