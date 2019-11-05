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
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libFS
COMPONENT_VERSION= 1.0.8
COMPONENT_FMRI=    x11/library/libfs
COMPONENT_SUMMARY= libFS - X Font Servers library
COMPONENT_ARCHIVE_HASH= \
  sha256:c8e13727149b2ddfe40912027459b2522042e3844c5cd228c3300fe5eef6bd0f

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

LD_OPTIONS_SO = -M $(PWD)/mapfile-vers

# Build dependencies
REQUIRED_PACKAGES += x11/library/xtrans

REQUIRED_PACKAGES += system/library
