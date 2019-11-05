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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gmtp
COMPONENT_VERSION=	1.3.11
COMPONENT_PROJECT_URL=	http://gmtp.sourceforge.net/
COMPONENT_SUMMARY=	A simple MP3 and Media player client for UNIX and UNIX like systems
COMPONENT_FMRI=		system/media/gmtp
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:5a830c9c448aa2caf7a844aaa9ba38c2ac0239547366c1e6874e0080bd5f0613
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/gmtp/files/gMTP-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--with-gtk3

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += library/audio/libid3tag
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libmtp
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += system/library
