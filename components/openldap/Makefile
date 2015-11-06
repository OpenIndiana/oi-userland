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

COMPONENT_NAME=		openldap
COMPONENT_VERSION=	2.4.30
COMPONENT_PROJECT_URL=	http://www.openldap.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fc013e528616f8578d9f221409c48af9b8937a62005e0bec88f6f1c4c8ff3d81
COMPONENT_ARCHIVE_URL=	ftp://ftp.openldap.org/pub/OpenLDAP/openldap-release/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	service/openldap

TPNO=			5295

SDFVER=			sdf-2.001
SDFBLIB=		$(BUILD_DIR_32)/${SDFVER}/blib

COMPONENT_ARCHIVE_1= $(SDFVER).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:6f9bcdc884a9f450208c740e45effdfeb7e65c689f57b05d3c15208193a8a6ea
COMPONENT_ARCHIVE_URL_1= ftp://ftp.eenet.ee/pub/cpan/authors/id/I/IA/IANC/$(COMPONENT_ARCHIVE_1)


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk

# This depends on libsasl which cannot be installed on S11.
ifeq ($(BUILD_TYPE), evaluation)
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_PRE_BUILD_ACTION = \
	 (cd $(BUILD_DIR_32); \
	 gzip -dc ../../$(SDFVER).tar.gz | tar xopf -; \
	  cd $(SDFVER); $(PERL) Makefile.PL; \
		$(GMAKE))

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC) $(studio_NORUNPATH)

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"
CONFIGURE_ENV += "ac_cv_lib_net_main=no"
CONFIGURE_ENV += "ac_cv_lib_net_socket==no"
CONFIGURE_ENV += "ac_cv_lib_inet_socket==no"

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --localstatedir=/var/openldap
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/openldap
CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-overlays
CONFIGURE_OPTIONS += --enable-dynamic
CONFIGURE_OPTIONS += --enable-crypt
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-bdb
CONFIGURE_OPTIONS += --enable-hdb
CONFIGURE_OPTIONS += --enable-null
CONFIGURE_OPTIONS += --enable-passwd	 
CONFIGURE_OPTIONS += --enable-shell
CONFIGURE_OPTIONS += --enable-ldap
CONFIGURE_OPTIONS += --with-cyrus-sasl
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-tls=openssl

PROTOULD = $(PROTOUSRLIBDIR)
COMPONENT_TEST_ENV += LD_LIBRARY_PATH="$(PROTOULD):$(PROTOULD)/$(MACH64):"
COMPONENT_TEST_ARGS += -e

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

#
# OpenLDAP must be built with cyrus-sasl out of the gate instead of the
# installed copy.
#
CYRUS_SASL_ROOT = $(WS_COMPONENTS)/cyrus-sasl/build/prototype/$(MACH)
LDFLAGS.32 +="-L$(CYRUS_SASL_ROOT)/usr/lib"
LDFLAGS.64 +="-L$(CYRUS_SASL_ROOT)/usr/lib/$(MACH64)"
LDFLAGS +=$(LDFLAGS.$(BITS))
CPPFLAGS +="-I$(CYRUS_SASL_ROOT)/usr/include"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
# make sure that we don't add the cyrus-sasl proto area to the RUNPATH
LD_UNSET.32="-R$(CYRUS_SASL_ROOT)/usr/lib"
LD_UNSET.64="-R$(CYRUS_SASL_ROOT)/usr/lib/$(MACH64)"
LD_UNSET += $(LD_UNSET.$(BITS))
COMPONENT_BUILD_ENV += LD_UNSET="$(LD_UNSET)"
COMPONENT_INSTALL_ENV += LD_UNSET="$(LD_UNSET)"

# special targets due to dependency on cyrus-sasl
../cyrus-sasl/build/%/.installed:
	(cd ../cyrus-sasl && $(GMAKE) install)

$(CONFIGURE_32):       ../cyrus-sasl/build/$(MACH32)/.installed
$(CONFIGURE_64):       ../cyrus-sasl/build/$(MACH64)/.installed

# common targets
configure:	$(CONFIGURE_32_and_64)

build:	$(BUILD_32_and_64)
	(cd $(BUILD_DIR_32)/doc/guide/admin; \
	$(PERL) -I$(SDFBLIB)/lib $(SDFBLIB)/script/sdf -2html guide.sdf; \
	$(PERL) -I$(SDFBLIB)/lib $(SDFBLIB)/script/sdf -2html index.sdf)

install:	$(INSTALL_32_and_64)

# build does this always
test:	$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)



REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += text/groff/groff-core
