#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2015 Alexander Pyhalov
# Copyright (c) 2019 Michal Nowak
#

X11_CATEGORY=LIB
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=	   libpciaccess
COMPONENT_VERSION= 0.18.1
COMPONENT_SUMMARY= scanpci and libpciaccess - generic PCI access software
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:4af43444b38adb5545d0ed1c2ce46d9608cc47b31c2387fc5181656765a6fa76
COMPONENT_FMRI=	   diagnostic/scanpci
COMPONENT_CLASSIFICATION=System/Hardware
COMPONENT_LICENSE_FILE=	COPYING

DROP_STATIC_LIBRARIES= yes
include $(WS_MAKE_RULES)/common.mk


# scanpci is missing in the prototype area so manually copy it over.
COMPONENT_POST_INSTALL_ACTION.64 += ( \
	$(MKDIR) $(PROTOUSRBINDIR) ; \
	$(CP) $(BUILD_DIR_64)/scanpci/scanpci $(PROTOUSRBINDIR)/ ; ) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
