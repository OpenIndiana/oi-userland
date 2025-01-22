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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libidn2
COMPONENT_VERSION=	2.3.7
COMPONENT_SUMMARY=	An implementation of IDNA2008 internationalized domain names
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:4c21a791b610b9519b9d0e12b8097bf2f359b12f8dd92647611a929e6bfd7d64
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libidn/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libidn/
COMPONENT_FMRI=		library/libidn2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPL-2.0-only AND LGPL-3.0-only

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf -- '--- COPYING ---------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING ; \
		printf '\n--- COPYING.LESSERv3 ------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LESSERv3 ; \
		printf '\n--- COPYING.unicode -------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.unicode ; \
		printf '\n--- COPYINGv2 -------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYINGv2 \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

CONFIGURE_INCLUDEDIR = /usr/include/idn2

CONFIGURE_OPTIONS += --enable-static=no

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) ;
# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += system/library
