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
# Copyright 2017, Longrin Wischnewski.
# Copyright 2019, Michal Nowak
# Copyright 2021, Nona Hansel
# Copyright 2022 Niklas Poslovski
#

BUILD_BITS= 64
BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fish
COMPONENT_VERSION=	3.6.1
COMPONENT_SUMMARY=	Fish is a smart and user-friendly command line shell
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://fishshell.com
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:55402bb47ca6739d8aba25e41780905b5ce1bce0a5e0dd17dca908b5bc0b49b2
COMPONENT_ARCHIVE_URL=	https://github.com/fish-shell/fish-shell/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		shell/fish
COMPONENT_CLASSIFICATION=	System/Shells
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk
PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR="/etc"
CMAKE_OPTIONS += -DSYS_PCRE2_INCLUDE_DIR=/usr/include/pcre
CMAKE_OPTIONS += -DFISH_USE_SYSTEM_PCRE2=ON
CMAKE_OPTIONS += -DWITH_GETTEXT=ON

COMPONENT_TEST_CMD= gmake
COMPONENT_TEST_TARGETS= test
# Just keep the failing test results, even it doesn't make the results reproducable:
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9]*\.[0-9]* sec//" ' \
	'-e "s/[0-9]*\/[0-9]*//" ' \
	'-n' \
	'-e "/Failed/p"'

# Manually added dependencies (for tests)
PYTHON_REQUIRED_PACKAGES += library/python/pexpect

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
