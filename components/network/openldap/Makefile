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
# Copyright (c) 2011, 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2022, Friedrich Kink
#

BUILD_BITS=             64_and_32
USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         openldap
COMPONENT_VERSION=      2.6.3
COMPONENT_SUMMARY=      OpenLDAP is an open source implementation of the Lightweight Directory Access Protocol
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tgz
COMPONENT_PROJECT_URL=  https://www.openldap.org/
COMPONENT_ARCHIVE_HASH= sha256:d2a2a1d71df3d77396b1c16ad7502e674df446e06072b0e5a4e941c3d06c0d46
COMPONENT_ARCHIVE_URL=  https://openldap.org/software/download/OpenLDAP/openldap-release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/openldap
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      The OpenLDAP Public License
COMPONENT_LICENSE_FILE= LICENSE

SDFVER=			sdf-2.001
SDFBLIB=		$(BUILD_DIR)/${SDFVER}/blib

COMPONENT_ARCHIVE_1= $(SDFVER).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
	sha256:6f9bcdc884a9f450208c740e45effdfeb7e65c689f57b05d3c15208193a8a6ea
COMPONENT_ARCHIVE_URL_1= ftp://ftp.eenet.ee/pub/cpan/authors/id/I/IA/IANC/$(COMPONENT_ARCHIVE_1)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))
COMPONENT_POST_CONFIGURE_ACTION.32 = ( $(GSED) -i -e 's:perl5/5.34/lib/i86pc-solaris-thread-multi-64:perl5/5.22/lib/i86pc-solaris-64int:g' -e 's:-m64::' $(@D)/servers/slapd/back-perl/Makefile )

PERL.64=		/usr/perl5/5.34/bin/perl
PERL.32=		/usr/perl5/5.22/bin/perl
PERL=			$(PERL.$(BITS))
COMPONENT_PRE_BUILD_ACTION = \
	 ( $(CP) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) $(BUILD_DIR); \
	 cd $(BUILD_DIR); \
	 gzip -dc $(COMPONENT_ARCHIVE_1) | tar xopf -; \
	 rm $(COMPONENT_ARCHIVE_1); \
	 cd $(SDFVER); $(PERL) Makefile.PL; $(GMAKE))

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)/openldap
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/openldap
CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-overlays
CONFIGURE_OPTIONS += --enable-dynamic
CONFIGURE_OPTIONS += --enable-modules
CONFIGURE_OPTIONS += --enable-syslog
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-rlookups
CONFIGURE_OPTIONS += --enable-dynacl
CONFIGURE_OPTIONS += --enable-aci
CONFIGURE_OPTIONS += --enable-wrappers
CONFIGURE_OPTIONS += --enable-shared
#enable all backends but wt
CONFIGURE_OPTIONS += --enable-backends=mod
CONFIGURE_OPTIONS += --enable-wt=no
#enable all overlays
CONFIGURE_OPTIONS += --enable-overlays=mod
CONFIGURE_OPTIONS += --enable-argon2
#CONFIGURE_OPTIONS += --enable-balancer
CONFIGURE_OPTIONS += --without-systemd
CONFIGURE_OPTIONS += --with-cyrus-sasl
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-tls=openssl
CONFIGURE_OPTIONS += --with-mp=gmp
CONFIGURE_OPTIONS += --with-odbc=unixodbc
CONFIGURE_OPTIONS.64 += LDFLAGS=-L$(OPENSSL_PREFIX)/lib/$(MACH64)
CONFIGURE_OPTIONS.32 += LDFLAGS=-L$(OPENSSL_PREFIX)/lib
CONFIGURE_OPTIONS += CPPFLAGS="-I$(OPENSSL_PREFIX)/include -I/usr/include/odbc"

COMPONENT_TEST_ENV += LD_LIBRARY_PATH="$(PROTOUSRLIBDIR):$(PROTOUSRLIBDIR64):"
COMPONENT_TEST_ENV += PATH="$(PROTOUSRSBINDIR):$(PROTOUSRBINDIR):/usr/bin"

# to remove plugin.la dependency
COMPONENT_POST_INSTALL_ACTION= $(GSED) -i -e 's:.la$$:.so:' $(PROTOETCDIR)/$(COMPONENT_NAME)/slapd.*

# common targets
BUILD_TARGET:	$(BUILD_64_and_32)
	(cd $(BUILD_DIR)/doc/guide/admin; \
	$(PERL) -I$(SDFBLIB)/lib $(SDFBLIB)/script/sdf -2html guide.sdf; \
	$(PERL) -I$(SDFBLIB)/lib $(SDFBLIB)/script/sdf -2html index.sdf)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
