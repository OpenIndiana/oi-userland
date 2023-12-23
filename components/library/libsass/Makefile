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
# Copyright (c) 2017 - 2021 Andreas Wacknitz
#

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsass
COMPONENT_VERSION=	3.6.6
COMPONENT_SUMMARY=	LibSass is a C/C++ port of the Sass engine
COMPONENT_PROJECT_URL=	https://github.com/sass/libsass
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:11f0bb3709a4f20285507419d7618f3877a425c0131ea8df40fe6196129df15d
COMPONENT_ARCHIVE_URL=	https://github.com/sass/libsass/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=	library/libsass
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

TESTi_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && $(CONFIG_SHELL) autoreconf --force --install )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
