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
# Copyright (c) 2015 Alexander Pyhalov
# Copyright (c) 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libofa
COMPONENT_VERSION=	222128881c792c99055fa0b9cf05e07ae9b5d818
IPS_COMPONENT_VERSION=	0.9.3
COMPONENT_REVISION=	2
# Project was initially at http://code.google.com/p/musicip-libofa/,
# but as Google Code is closing we refer to more up-to-date mirror
COMPONENT_PROJECT_URL=	https://github.com/tanob/libofa
COMPONENT_SUMMARY=	Library for accesing MusicBrainz servers
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	\
    sha256:78707d928c40090f2dce2670d171d6332c014a0613f396b7eb173e8ff2c140fb
COMPONENT_ARCHIVE_URL=	https://github.com/tanob/libofa/archive/$(COMPONENT_VERSION).zip
COMPONENT_CLASSIFICATION=	Development/High Performance Computing
COMPONENT_FMRI=		library/libofa
COMPONENT_LICENSE_FILE=	libofa.license
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
