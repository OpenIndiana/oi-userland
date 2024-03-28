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
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fish
COMPONENT_VERSION=	3.7.1
COMPONENT_SUMMARY=	Fish is a smart and user-friendly command line shell
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://fishshell.com
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:614c9f5643cd0799df391395fa6bbc3649427bb839722ce3b114d3bbc1a3b250
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

COMPONENT_TEST_ENV += LC_ALL=C.UTF-8
COMPONENT_TEST_CMD= gmake
COMPONENT_TEST_TARGETS= test

# Manually added dependencies (for tests)
PYTHON_REQUIRED_PACKAGES += library/python/pexpect

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
