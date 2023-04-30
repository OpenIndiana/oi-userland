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
# Copyright 2016 Aurelien Larcher
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS= 32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           xorg-cf-files
COMPONENT_VERSION=        1.0.8
COMPONENT_SUMMARY=  X.Org platform configuration files for imake
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:7408955defcfab0f44d1bedd4ec0c20db61914917ad17bfc1f1c9bf56acc17b9
COMPONENT_ARCHIVE_URL=	https://www.x.org/releases/individual/util/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.x.org/
COMPONENT_FMRI=           developer/build/imake/xorg-cf-files
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Auto-generated dependencies
