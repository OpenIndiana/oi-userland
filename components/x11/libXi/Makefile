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
# Copyright 2016 Alexander Pyhalov
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXi
COMPONENT_VERSION= 1.8.1
COMPONENT_FMRI =   x11/library/libxi
COMPONENT_SUMMARY= libXi - X Input extension client library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:89bfc0e814f288f784202e6e5f9b362b788ccecdeb078670145eacd8749656a7
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && PATH="$(PATH)" autoreconf -f -i )

CONFIGURE_OPTIONS +=  --localstatedir=/var
CONFIGURE_OPTIONS +=  --enable-shared=yes
CONFIGURE_OPTIONS +=  --enable-static=no
CONFIGURE_OPTIONS +=  --with-pic
CONFIGURE_OPTIONS +=	LIB_MAN_SUFFIX=3xi

LD_OPTIONS += -M$(COMPONENT_DIR)/mapfile-vers

# Packages needed to generate documentation
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += text/xmlto
REQUIRED_PACKAGES += x11/documentation/xorg-sgml-doctools

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
