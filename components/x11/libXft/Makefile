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
# Copyright 2015 Alexander Pyhalov
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=	    libXft
COMPONENT_VERSION=  2.3.7
COMPONENT_FMRI=	    x11/library/libxft
COMPONENT_SUMMARY=  libXft - X FreeType library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:79f0b37c45007381c371a790c2754644ad955166dbf2a48e3625032e9bdd4f71
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=  --localstatedir=/var
CONFIGURE_OPTIONS +=  --enable-shared=yes
CONFIGURE_OPTIONS +=  --enable-static=no
CONFIGURE_OPTIONS +=  --with-pic

LD_OPTIONS += -M$(COMPONENT_DIR)/mapfile.scope

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxrender
