#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		evince
COMPONENT_VERSION=	2.30.3
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Evince
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:1ac6fb056c50a6298b31f696e196b5b940098c46f35dec85e69ea0c5d5b015de
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/evince
TPNO=			8693

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Need to pick up the GNU version of xgettext.
PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	libtoolize --force ; \
	intltoolize --force --copy --automake ; \
	aclocal -I . ; \
	autoheader ; \
	automake -a -c -f ; \
	autoconf )

CFLAGS +=	"-I/usr/include/libxml2"
LDFLAGS +=	$(CC_BITS) -lgmodule-2.0 -lm
CXX +=		$(studio_NORUNPATH)

CONFIGURE_OPTIONS +=	CXX="$(CXX)"
CONFIGURE_OPTIONS +=    CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=    LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS +=	--libexecdir="$(USRLIB)"
CONFIGURE_OPTIONS +=	--sysconfdir="$(ETCDIR)"
CONFIGURE_OPTIONS +=   --disable-comics
CONFIGURE_OPTIONS +=   --enable-thumbnailer

# Assumes GNU msgfmt is in PATH.
COMPONENT_BUILD_ENV += PATH="$(PATH)"

COMPONENT_BUILD_ENV += LDFLAGS="$(studio_NORUNPATH)"

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS += V=1

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)

REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-keyring
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
