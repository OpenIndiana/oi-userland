#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Harry Liebel
# Copyright 2022 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		x11vnc
COMPONENT_VERSION=	0.9.17
COMPONENT_SUMMARY=	VNC server for use with real X displays
COMPONENT_DESCRIPTION=	VNC (Virtual Network Computing) is a very useful network graphics protocol which allows multiple simple remote viewers to watch and control a single desktop.  x11vnc differs from traditional UNIX VNC servers in that it is accessing a real X displays that may already be in progress rather than creating its own X server for clients to connect to.
COMPONENT_PROJECT_URL=	https://libvnc.github.io
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3ab47c042bc1c33f00c7e9273ab674665b85ab10592a8e0425589fe7f3eb1a69
COMPONENT_ARCHIVE_URL= https://github.com/LibVNC/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		x11/x11vnc
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && autoreconf -v --install )

CFLAGS  += -I$(OPENSSL_INCDIR)
LDFLAGS += -L$(OPENSSL_LIBDIR)

# Build dependencies
REQUIRED_PACKAGES += library/libvncserver

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/libvncserver
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxtst
