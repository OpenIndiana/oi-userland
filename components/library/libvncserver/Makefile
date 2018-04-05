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
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvncserver
COMPONENT_VERSION=	0.9.10
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://libvnc.github.io
COMPONENT_SRC=		$(COMPONENT_NAME)-LibVNCServer-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	LibVNCServer-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:ed10819a5bfbf269969f97f075939cc38273cc1b6d28bccfb0999fba489411f7
COMPONENT_ARCHIVE_URL= \
  https://github.com/LibVNC/$(COMPONENT_NAME)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libvncserver
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_SUMMARY=	VNC server and client C libraries
COMPONENT_DESCRIPTION=	LibVNCServer/LibVNCClient are cross-platform C libraries that allow you to easily implement VNC server or client functionality in your program.
COMPONENT_CLASSIFICATION= Development/C

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
	( cd $(@D) && autoreconf -fiv )

LD_OPTIONS += $(LD_Z_DEFS)

# Use OpenSSL
CONFIGURE_OPTIONS += --without-gnutls

CFLAGS +=	$(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
LDFLAGS +=	$(JPEG_LDFLAGS)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
