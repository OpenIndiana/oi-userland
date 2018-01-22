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

COMPONENT_NAME=		ConsoleKit
COMPONENT_VERSION=	0.4.1
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/ConsoleKit
COMPONENT_SUMMARY=	Framework for tracking users, login sessions, and seats
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:f032adc6146d745034315054c5822a7a09f30e20a40d6e802221fa977354403e
COMPONENT_ARCHIVE_URL=	http://www.freedesktop.org/software/ConsoleKit/dist/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Sessions
COMPONENT_FMRI=		library/xdg/consolekit

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					glib-gettextize -f &&\
					libtoolize --copy --force &&\
					aclocal -I . &&\
					automake -c -f -a &&\
					autoconf )

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--localstatedir=/var
CONFIGURE_OPTIONS+=	--enable-pam-module
CONFIGURE_OPTIONS+=	--with-pam-module-dir=/usr/lib/security
CONFIGURE_OPTIONS+=	--with-pam-module-dir=/usr/lib/security
CONFIGURE_OPTIONS+=	--enable-rbac-shutdown=solaris.system.shutdown

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES+= x11/header/xproto
REQUIRED_PACKAGES+= x11/header/kbproto
REQUIRED_PACKAGES+= x11/library/libpthread-stubs

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libx11
