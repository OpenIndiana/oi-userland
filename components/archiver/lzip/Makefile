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

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		lzip
COMPONENT_VERSION=	1.20
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://lzip.nongnu.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c93b81a5a7788ef5812423d311345ba5d3bd4f5ebf1f693911e3a13553c1290c
COMPONENT_ARCHIVE_URL=	http://download.savannah.gnu.org/releases/lzip/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	http://download.savannah.gnu.org/releases/lzip/$(COMPONENT_ARCHIVE).sig
COMPONENT_FMRI=		compress/lzip
COMPONENT_SUMMARY=	'Lzip - a lossless data compressor with a user interface similar to the one of gzip or bzip2'
COMPONENT_LICENSE=	GPLv2+
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION= Applications/System Utilities

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/testing|tests/'"

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
