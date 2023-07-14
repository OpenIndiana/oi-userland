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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         openldap
COMPONENT_VERSION=      2.6.5
COMPONENT_SUMMARY=      OpenLDAP is an open source implementation of the Lightweight Directory Access Protocol
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tgz
COMPONENT_PROJECT_URL=  https://www.openldap.org/
COMPONENT_ARCHIVE_HASH= sha256:2e27a8d4f4c2af8fe840b573271c20aa163e24987f9765214644290f5beb38d9
COMPONENT_ARCHIVE_URL=  https://openldap.org/software/download/OpenLDAP/openldap-release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/openldap
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      The OpenLDAP Public License
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET = $(TEST_64)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)/openldap
CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/openldap
CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-dynamic
CONFIGURE_OPTIONS += --enable-syslog
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-shared

# SLAPD related options
# Note: we build 64-bit slapd only
CONFIGURE_OPTIONS.32 += --disable-slapd
CONFIGURE_OPTIONS.32 += --disable-cleartext
CONFIGURE_OPTIONS.32 += --disable-mdb
CONFIGURE_OPTIONS.32 += --disable-relay
CONFIGURE_OPTIONS.32 += --disable-syncprov
CONFIGURE_OPTIONS.64 += --enable-modules
CONFIGURE_OPTIONS.64 += --enable-rlookups
CONFIGURE_OPTIONS.64 += --enable-dynacl
CONFIGURE_OPTIONS.64 += --enable-aci
CONFIGURE_OPTIONS.64 += --enable-wrappers
#enable all backends but wt
CONFIGURE_OPTIONS.64 += --enable-backends=mod
CONFIGURE_OPTIONS.64 += --enable-wt=no
#enable all overlays
CONFIGURE_OPTIONS.64 += --enable-overlays=mod
CONFIGURE_OPTIONS.64 += --enable-argon2

#CONFIGURE_OPTIONS += --enable-balancer
CONFIGURE_OPTIONS += --without-systemd
CONFIGURE_OPTIONS += --with-cyrus-sasl
CONFIGURE_OPTIONS += --with-threads
CONFIGURE_OPTIONS += --with-tls=openssl
CONFIGURE_OPTIONS += --with-mp=gmp
CONFIGURE_OPTIONS += --with-odbc=unixodbc
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_LIBDIR)
CONFIGURE_OPTIONS += CPPFLAGS="-I$(OPENSSL_INCDIR) -I/usr/include/odbc"

# Force known perl version
CONFIGURE_ENV += PERLBIN=$(PERL)

COMPONENT_TEST_ENV += LD_LIBRARY_PATH="$(PROTOUSRLIBDIR):$(PROTOUSRLIBDIR64):"
COMPONENT_TEST_ENV += PATH="$(PROTOUSRSBINDIR):$(PROTOUSRBINDIR):/usr/bin:$(PATH.gnu)"

# to remove plugin.la dependency
COMPONENT_POST_INSTALL_ACTION.64 = $(GSED) -i -e 's:.la$$:.so:' $(PROTOETCDIR)/$(COMPONENT_NAME)/slapd.*

COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "/Comparing/p" ' \
	' -e "/Filtering/p" ' \
	' -e "/Running/p" ' \
	' -e "/Testing/p" ' \
	' -e "/Result/p" ' \
	' -e "/failed/p" ' \
	' -e "/succeeded/p" '

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += security/argon2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
