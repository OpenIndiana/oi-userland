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
# Copyright (c) 2017, 2018 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsass
COMPONENT_VERSION=	3.5.4
COMPONENT_PROJECT_URL=	http://libsass.org
COMPONENT_SUMMARY=	LibSass is a C/C++ port of the Sass engine
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:5f61cbcddaf8e6ef7a725fcfa5d05297becd7843960f245197ebb655ff868770
COMPONENT_ARCHIVE_URL=	https://github.com/sass/libsass/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =	library/libsass
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_CLASSIFICATION =	System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = \
			( cd $(@D) && $(CONFIG_SHELL) autoreconf --force --install )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated:
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
