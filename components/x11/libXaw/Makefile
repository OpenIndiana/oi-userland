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
COMPONENT_VERSION= 1.0.15
COMPONENT_SUMMARY= libXaw - X Athena Widgets library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:ab35f70fde9fb02cc71b342f654846a74328b74cb3a0703c02d20eddb212754a
COMPONENT_FMRI=    x11/library/toolkit/libxaw7
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) && \
                          cd $(@D) &&  autoreconf -f  -i )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-xaw6

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/toolkit/libxt
