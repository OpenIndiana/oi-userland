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
# Copyright 2016 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=	dconf-editor
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=    https://wiki.gnome.org/Projects/dconf
COMPONENT_SUMMARY=        GNOME Configuration Editor
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=        \
    sha256:6579b8b216b068acae7d8301b5e2d57054c85a3f147c92355ffa46a62c052534
COMPONENT_ARCHIVE_URL=        http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.18/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI= gnome/config/dconf/dconf-editor
COMPONENT_CLASSIFICATION = Applications/Configuration and Preferences

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CFLAGS += -std=c99
CFLAGS += -D__EXTENSIONS__

CONFIGURE_OPTIONS+=        --sysconfdir=/etc
CONFIGURE_OPTIONS+=        --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

# common targets
build:	$(BUILD_32)

install:	$(INSTALL_32)

test:	$(NO_TESTS)

REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
