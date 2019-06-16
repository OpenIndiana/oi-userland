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
# Copyright 2019 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsexy
COMPONENT_VERSION=	0.1.11
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	libsexy is a collection of GTK+ widgets that extend the functionality of such standard widget
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8c4101a8cda5fccbba85ba1a15f46f2cf75deaa8b3c525ce5b135b9e1a8fe49e
COMPONENT_ARCHIVE_URL= \
  http://releases.chipx86.com/libsexy/libsexy/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://blog.chipx86.com/tag/libsexy/
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_FMRI=		library/desktop/libsexy
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-gtk-doc

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
