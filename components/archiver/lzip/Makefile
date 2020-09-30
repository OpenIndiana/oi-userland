#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2018 Michal Nowak
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lzip
COMPONENT_VERSION=	1.21
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://lzip.nongnu.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e48b5039d3164d670791f9c5dbaa832bf2df080cb1fbb4f33aa7b3300b670d8b
COMPONENT_ARCHIVE_URL=	https://download.savannah.gnu.org/releases/lzip/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	http://download.savannah.gnu.org/releases/lzip/$(COMPONENT_ARCHIVE).sig
COMPONENT_FMRI=		compress/lzip
COMPONENT_SUMMARY=	'Lzip - a lossless data compressor with a user interface similar to the one of gzip or bzip2'
COMPONENT_LICENSE=	GPLv2+
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION= Applications/System Utilities

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/testing|tests/'"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
