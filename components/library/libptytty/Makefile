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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libptytty
COMPONENT_VERSION=      2.0
COMPONENT_PROJECT_URL=  http://software.schmorp.de/pkg/libptytty.html
COMPONENT_SUMMARY=      An offspring of rxvt-unicode that handles pty/tty/utmp/wtmp/lastlog handling in mostly OS-independent ways
COMPONENT_FMRI=         library/libptytty
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:8033ed3aadf28759660d4f11f2d7b030acf2a6890cb0f7926fb0cfa6739d31f7
COMPONENT_ARCHIVE_URL=	http://dist.schmorp.de/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
