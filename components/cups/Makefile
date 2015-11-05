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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cups
COMPONENT_VERSION=	1.4.5
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.cups.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:0450d6d8e6e8af225d2a3319c848737d76473a6c7579cf97c52086d0371c0efe
COMPONENT_ARCHIVE_URL=	http://ftp.easysw.com/pub/cups/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/cups

TPNO=			17705

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXX +=	$(studio_NORUNPATH)

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
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-gnutls
CONFIGURE_OPTIONS +=	--disable-libusb
CONFIGURE_OPTIONS +=	--enable-labeling
CONFIGURE_OPTIONS +=	--enable-openssl
CONFIGURE_OPTIONS +=	--enable-dbus
CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	--enable-64bit
CONFIGURE_OPTIONS +=	--enable-auditing

CONFIGURE_OPTIONS += 	ARCH64FLAGS=-m64
CONFIGURE_OPTIONS += 	DSO64FLAGS="$(LDLIBS) -G"
CONFIGURE_OPTIONS += 	"ac_cv_search_getifaddrs=no"
CONFIGURE_OPTIONS += 	"ac_cv_func_statfs=no"

$(BUILD_DIR)/%/.installed:	ENV +=	DSTROOT="$(PROTO_DIR)"

PATCH_LEVEL =	0

COMPONENT_PRE_CONFIGURE_ACTION = \
 $(CLONEY) $(SOURCE_DIR) $(@D) ; \
 find $(@D) -name '*.in' | sed -e 's/.in$$//' | xargs $(RM) ; \
 ( cd $(SOURCE_DIR) ; autoconf -f )

# install the default config file
COMPONENT_POST_INSTALL_ACTION = \
	$(TOUCH) $(PROTOETCDIR)/cups/command.types ; \
	$(MV) $(PROTOUSRLIBDIR)/64 $(PROTOUSRLIBDIR)/$(MACH64)

# common targets
configure:	$(CONFIGURE_32)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += driver/parallel/ecpp
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += service/network/slp
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
