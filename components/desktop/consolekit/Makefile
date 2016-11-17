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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ConsoleKit
COMPONENT_VERSION=	0.4.1
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/software/ConsoleKit
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:f032adc6146d745034315054c5822a7a09f30e20a40d6e802221fa977354403e
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/dist/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/consolekit

TPNO=			7882

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	aclocal -I . ; \
	libtoolize --force ; \
	autoheader ; \
	automake -a -c -f ; \
	autoconf )

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--enable-pam-module
CONFIGURE_OPTIONS.32 +=	--with-pam-module-dir=/usr/lib/security
CONFIGURE_OPTIONS.64 +=	--with-pam-module-dir=/usr/lib/security/$(MACH64)
CONFIGURE_OPTIONS +=	--libexecdir="$(USRLIB)"
CONFIGURE_OPTIONS +=	--localstatedir="$(VARDIR)"
CONFIGURE_OPTIONS +=	--enable-rbac-shutdown=solaris.system.shutdown

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/server/xorg
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/polkit
