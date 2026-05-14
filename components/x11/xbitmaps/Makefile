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
# Copyright 2015 Aurelien Larcher
#

X11_CATEGORY= DATA
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           xbitmaps
COMPONENT_VERSION=        1.1.4
COMPONENT_SUMMARY=        bitmap images from X.Org
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=   sha256:895722f136e21e728c52f2d99fd2dae95018b9ddad1bac1f29d61bcd6593721d
COMPONENT_FMRI=           x11/data/xbitmaps
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=        MIT License
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_INSTALL_ARGS += pkgconfigdir=/usr/share/pkgconfig

# Auto-generated dependencies
