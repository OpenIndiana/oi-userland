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
# Copyright 2016-2019 Aurelien Larcher
#
BUILD_BITS=64_and_32

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=     libfontenc
COMPONENT_VERSION=  1.1.4
COMPONENT_FMRI=     x11/library/libfontenc
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  libfontenc - font encoding table parser and mapping library
COMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2cfcce810ddd48f2e5dc658d28c1808e86dcf303eaff16728b9aa3dbc0092079
COMPONENT_ARCHIVE_URL= $(XORG_LIB_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=   MIT License

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_DEFAULT_DIRS=no
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --libdir=$(XORG_LIBDIR)

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
