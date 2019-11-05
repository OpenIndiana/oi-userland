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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cups
COMPONENT_VERSION=	1.7.5
COMPONENT_REVISION=	3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.cups.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:18cb4c6847dbaaaa05c8b35af787f19dd5c7686970b46548e72c711c6f26bd02
COMPONENT_ARCHIVE_URL=	https://www.cups.org/software/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/cups

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# don't use LD_Z_IGNORE: causes linker problems
LD_Z_IGNORE=

CONFIGURE_OPTIONS +=	--prefix=/usr
CONFIGURE_OPTIONS +=	--mandir=/usr/share/man
CONFIGURE_OPTIONS +=	--localedir=$(USRSHARELOCALEDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--with-fontpath=/usr/openwin/lib
CONFIGURE_OPTIONS +=	--with-logdir=/var/log/cups
CONFIGURE_OPTIONS +=	--with-domainsocket=/var/run/cups-socket
CONFIGURE_OPTIONS +=	--with-smfmanifestdir=/lib/svc/manifest/application
CONFIGURE_OPTIONS +=	--with-printcap=/etc/printers.conf
CONFIGURE_OPTIONS +=	--with-cups-user=lp
CONFIGURE_OPTIONS +=	--with-cups-group=lp
CONFIGURE_OPTIONS +=	--with-php=no
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-gnutls
CONFIGURE_OPTIONS +=	--disable-libusb
CONFIGURE_OPTIONS +=	--enable-openssl
CONFIGURE_OPTIONS +=	--enable-dbus
CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS += 	--with-archflags="$(CC_BITS)"

CONFIGURE_OPTIONS += 	"ac_cv_search_getifaddrs=no"
CONFIGURE_OPTIONS += 	"ac_cv_func_statfs=no"

$(BUILD_DIR)/%/.installed:	ENV +=	DSTROOT="$(PROTO_DIR)"

PATCH_LEVEL =	0

COMPONENT_PRE_CONFIGURE_ACTION = \
 $(CLONEY) $(SOURCE_DIR) $(@D) ; \
 find $(@D) -name '*.in' | sed -e 's/.in$$//' | xargs $(RM) ; \
 ( cd $(SOURCE_DIR) ; autoconf -f )

# common targets

$(INSTALL_32):	$(INSTALL_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += service/network/dns/mdns
REQUIRED_PACKAGES += service/network/slp

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/network/avahi
