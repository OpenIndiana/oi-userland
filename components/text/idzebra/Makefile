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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= idzebra
COMPONENT_VERSION= 2.2.8
COMPONENT_SUMMARY= idzebra - text indexing and retrieval engine
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:879e402b91912e9074275753f24408ed2ac06b3b7c30b2a2d5a70718c869a542
# The archive of 2.2.8 is missing the contents of the doc/common folder. We provide a patched one in our dlc.
#COMPONENT_ARCHIVE_URL=	https://github.com/indexdata/idzebra/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://dlc.openindiana.org/oi-userland/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.indexdata.com/resources/software/zebra/
COMPONENT_FMRI= text/idzebra
COMPONENT_CLASSIFICATION = System/Text Tools
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= LICENSE.zebra

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -Wno-error=incompatible-pointer-types

# For tests to pass we should be very careful about files
COMPONENT_PRE_CONFIGURE_ACTION = ( CLONEY_MODE=copy $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -fiv )

CONFIGURE_OPTIONS += --enable-static=no

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
