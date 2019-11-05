#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 (c) Aurelien Larcher. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		lft
COMPONENT_VERSION=	3.72
COMPONENT_FMRI=		diagnostic/lft
COMPONENT_PROJECT_URL=	http://pwhois.org/lft/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e51535ad0c04c75a76e44db2e38641d1803d0d7c212b7be79580532057c11d88
COMPONENT_ARCHIVE_URL=	http://pwhois.org/dl/index.who?file=$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_LICENSE=	VOSTROM Public License for Open Source
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=	Layer Four Traceroute (LFT) and WhoB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Work around broken Makefile not supporting out of source build
COMPONENT_POST_CONFIGURE_ACTION= $(CP) $(SOURCE_DIR)/*.c $(SOURCE_DIR)/*.h $(SOURCE_DIR)/*.8 $(BUILD_DIR_$(BITS))/

COMPONENT_INSTALL_ARGS=DESTDIR=$(PROTO_DIR)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
