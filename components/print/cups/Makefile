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
# Copyright (c) 2011, 2014, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cups
COMPONENT_VERSION=	2.4.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_PROJECT_URL=	https://openprinting.github.io/cups/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7d89f684aace50e17100c78812069168f1bdc06f95623117094f8c47ef867aef
COMPONENT_ARCHIVE_URL=  https://github.com/OpenPrinting/cups/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_LICENSE=	Apache 2.0 with an exception to allow linking against GNU GPL2-only software

include $(WS_MAKE_RULES)/common.mk

$(CONFIGURE_32):    LDFLAGS += -m32
$(CONFIGURE_64):    LDFLAGS += -m64

COMPONENT_PRE_CONFIGURE_ACTION += $(CLONEY) $(SOURCE_DIR) $(@D)

COMPONENT_PREP_ACTION= ( cd $(@D) ; autoconf -f )

# Make sure that "install-sh -s" calls "strip -x" and not "strip";
# we want to remove debugging data but not the symbols.
COMPONENT_INSTALL_ENV += STRIPPROG="strip -x"

CFLAGS += $(CPP_XPG6MODE)
LDFLAGS += -lsocket

# Ensure dynamic shared objects are linked using same LDFLAGS as executables.
CONFIGURE_ENV += DSOFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

CONFIGURE_OPTIONS += --prefix=/usr
CONFIGURE_OPTIONS += --mandir=/usr/share/man
CONFIGURE_OPTIONS += --localedir=$(USRSHARELOCALEDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
# Unlike Solaris 11 which has combined and renamed /var/run and /etc/volatile into /system/volatile
# we still use the traditional state folder:
CONFIGURE_OPTIONS += --with-rundir=/var/run/cups
CONFIGURE_OPTIONS += --with-smfmanifestdir=/lib/svc/manifest/application
CONFIGURE_OPTIONS += --with-printcap=/etc/printers.conf
CONFIGURE_OPTIONS += --with-cups-user=lp
CONFIGURE_OPTIONS += --with-cups-group=lp
CONFIGURE_OPTIONS += --with-tls=gnutls
CONFIGURE_OPTIONS += --without-rcdir
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-dbus
CONFIGURE_OPTIONS += --with-archflags="$(CC_BITS)"

# Dynamically create the license file from its sources:
cups.license: $(SOURCE_DIR)/LICENSE $(SOURCE_DIR)/NOTICE
	cat $? > $@

# Manually added build dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += service/network/slp

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/ca-certificates
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
