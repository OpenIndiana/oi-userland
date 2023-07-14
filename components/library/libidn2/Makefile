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
COMPONENT_VERSION=	2.3.4
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	An implementation of IDNA2008 internationalized domain names
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:93caba72b4e051d1f8d4f5a076ab63c99b77faee019b72b9783b267986dbb45f
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/libidn/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libidn/
COMPONENT_FMRI=		library/libidn2
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPLv3, GPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --includedir=/usr/include/idn2

# Without the following one test (libidn2) fails: 
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += system/library
