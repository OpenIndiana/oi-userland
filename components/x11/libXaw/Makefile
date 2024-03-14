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

COMPONENT_NAME=    libXaw
COMPONENT_VERSION= 1.0.16
COMPONENT_SUMMARY= libXaw - X Athena Widgets library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:731d572b54c708f81e197a6afa8016918e2e06dfd3025e066ca642a5b8c39c8f
COMPONENT_FMRI=    x11/library/toolkit/libxaw7
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-xaw6
CONFIGURE_OPTIONS += LIB_MAN_SUFFIX=3xaw

# Install additional man page
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTOUSRSHAREMANDIR)/man3lib ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) $(COMPONENT_DIR)/files/libXaw.3lib $(PROTOUSRSHAREMANDIR)/man3lib ;

# Manually added build dependencies
REQUIRED_PACKAGES += text/xmlto
REQUIRED_PACKAGES += x11/documentation/xorg-sgml-doctools

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxt
