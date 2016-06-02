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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cups
COMPONENT_VERSION=	1.4.5
COMPONENT_PROJECT_URL=	http://www.cups.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-source.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:0450d6d8e6e8af225d2a3319c848737d76473a6c7579cf97c52086d0371c0efe
COMPONENT_ARCHIVE_URL=	http://ftp.easysw.com/pub/cups/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			17705

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Ensure CC-based linking does not embed runpaths.
LDFLAGS += $(studio_NORUNPATH)

# don't use LD_Z_IGNORE: causes linker problems
LD_Z_IGNORE=

# cups has an unusual hybrid-build system to support 32-bit and 64-bit
# libraries in a single build; avoid confusing it by stripping $(CC_BITS) from
# all related flag variables.
CONFIGURE_CPPFLAGS.stripped := $(patsubst -m32,,$(CONFIGURE_CPPFLAGS))
CONFIGURE_CPPFLAGS= $(CONFIGURE_CPPFLAGS.stripped)
CFLAGS.stripped := $(patsubst -m32,,$(CFLAGS))
CFLAGS= $(CFLAGS.stripped)
CXXFLAGS.stripped := $(patsubst -m32,,$(CXXFLAGS))
CXXFLAGS= $(CXXFLAGS.stripped)

CONFIGURE_ENV += "ac_cv_search_getifaddrs=no"
CONFIGURE_ENV += "ac_cv_func_statfs=no"
# Ensure dynamic shared objects are linked using same LDFLAGS as executables.
CONFIGURE_ENV += DSOFLAGS="$(LDFLAGS)"

CONFIGURE_OPTIONS +=	--localedir=$(USRSHARELOCALEDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS +=	--with-fontpath=$(USRSHAREFONTSDIR)
CONFIGURE_OPTIONS +=	--with-logdir=$(VARDIR)/log/cups
CONFIGURE_OPTIONS +=	--with-domainsocket=$(VARDIR)/run/cups-socket
CONFIGURE_OPTIONS +=	--with-smfmanifestdir=$(LIBDIR)/svc/manifest/application
CONFIGURE_OPTIONS +=	--with-printcap=$(ETCDIR)/printers.conf
CONFIGURE_OPTIONS +=	--with-cups-user=lp
CONFIGURE_OPTIONS +=	--with-cups-group=lp
CONFIGURE_OPTIONS +=	--disable-slp
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--disable-gnutls
CONFIGURE_OPTIONS +=	--disable-libusb
CONFIGURE_OPTIONS +=	--enable-labeling
CONFIGURE_OPTIONS +=	--enable-openssl
CONFIGURE_OPTIONS +=	--enable-dbus
CONFIGURE_OPTIONS +=	--enable-threads
CONFIGURE_OPTIONS +=	--enable-64bit
CONFIGURE_OPTIONS +=	--enable-auditing
CONFIGURE_OPTIONS +=	--without-php

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

REQUIRED_PACKAGES += driver/parallel/ecpp
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += system/network/ldap/openldap
