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
#

BUILD_BITS=			64
BUILD_STYLE=		cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fish
COMPONENT_VERSION=	3.3.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://fishshell.com
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b5b4ee1a5269762cbbe993a4bd6507e675e4100ce9bbe84214a5eeb2b19fae89
COMPONENT_ARCHIVE_URL= https://github.com/fish-shell/fish-shell/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_SUMMARY=	Fish is a smart and user-friendly command line shell
COMPONENT_FMRI=		shell/fish
COMPONENT_CLASSIFICATION=System/Shells

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR="/etc"
CMAKE_OPTIONS += -DPCRE2_INCLUDE_DIR=/usr/include/pcre

COMPONENT_TEST_CMD = gmake

COMPONENT_TEST_TARGETS = test_fishscript test_interactive

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += library/pcre2
# test dependency
REQUIRED_PACKAGES += library/python/pexpect-39

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
