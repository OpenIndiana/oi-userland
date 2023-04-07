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
# Copyright 2016 phorcys@126.com.  All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libplist
COMPONENT_VERSION= 2.2.0
COMPONENT_SUMMARY= A library to handle Apple Property List format in binary or XML
COMPONENT_PROJECT_URL = https://github.com/libimobiledevice/libplist
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7e654bdd5d8b96f03240227ed09057377f06ebad08e1c37d0cfa2abe6ba0cee2
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI = library/libplist
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_LICENSE = GPLv2,LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= \
    ( cd  $(@D) && NOCONFIGURE=true PATH="$(PATH.gnu)" sh autogen.sh )

CFLAGS += $($(COMPILER)_PIC)

CONFIGURE_OPTIONS += --disable-static

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
