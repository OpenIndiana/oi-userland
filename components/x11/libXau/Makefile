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
# Copyright 2015-2019 Aurelien Larcher
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXau
COMPONENT_VERSION= 1.0.9
COMPONENT_FMRI=    x11/library/libxau
COMPONENT_SUMMARY= libXau - X11 Authorization Protocol library
COMPONENT_ARCHIVE_HASH= \
  sha256:ccf8cbf0dbf676faa2ea0a6d64bcc3b6746064722b606c8c52917ed00dcb73ec

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --enable-xthreads
CONFIGURE_OPTIONS+= --without-lint
CONFIGURE_OPTIONS+= --disable-lint-library
CONFIGURE_OPTIONS+= --with-pic

LD_OPTIONS += -M$(COMPONENT_DIR)/mapfile-vers

REQUIRED_PACKAGES += system/library
