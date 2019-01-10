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
# Copyright 2018, Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fish
COMPONENT_VERSION=	3.0.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://fishshell.com
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:ea9dd3614bb0346829ce7319437c6a93e3e1dfde3b7f6a469b543b0d2c68f2cf
COMPONENT_ARCHIVE_URL= \
	https://github.com/fish-shell/fish-shell/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_SUMMARY=	Fish is a smart and user-friendly command line shell
COMPONENT_FMRI=		shell/fish
COMPONENT_CLASSIFICATION=System/Shells

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CMAKE_ACTION = ( \
	$(MV) $(SOURCE_DIR)/tests/invocation/bad-switch.invoke $(SOURCE_DIR)/tests/invocation/bad-switch.invoke.disabled; )

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR="/etc"
CMAKE_OPTIONS += -DPCRE2_INCLUDE_DIR=/usr/include/pcre

COMPONENT_TEST_CMD = gmake

COMPONENT_TEST_TARGETS = test

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += library/pcre2
# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
