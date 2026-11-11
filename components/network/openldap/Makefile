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


USE_PARALLEL_BUILD=yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         openldap
COMPONENT_VERSION=      2.6.16
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      OpenLDAP is an open source implementation of the Lightweight Directory Access Protocol
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tgz
COMPONENT_PROJECT_URL=  https://www.openldap.org/
COMPONENT_ARCHIVE_HASH= sha256:8d8452bc3f56aa7a392c62dd377733f83d1314eed6c52fe44028439a3bb4df18
COMPONENT_ARCHIVE_URL=  https://openldap.org/software/download/OpenLDAP/openldap-release/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/openldap
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      The OpenLDAP Public License
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

CLONEY_MODE =

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)
# check below for a newer release is still needed for a gcc14 build.
CFLAGS += -Wno-implicit-function-declaration

# Set non-default directories
CONFIGURE_LIBEXECDIR =		$(CONFIGURE_LIBDIR)
CONFIGURE_LOCALSTATEDIR :=	$(CONFIGURE_LOCALSTATEDIR)/openldap
CONFIGURE_INCLUDEDIR :=		$(CONFIGURE_INCLUDEDIR)/openldap

CONFIGURE_OPTIONS += --docdir=$(USRSHAREDOCDIR)
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-dynamic
CONFIGURE_OPTIONS += --enable-syslog
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-crypt

# SLAPD related options
CONFIGURE_OPTIONS += --enable-modules
CONFIGURE_OPTIONS += --enable-rlookups
CONFIGURE_OPTIONS += --enable-dynacl
CONFIGURE_OPTIONS += --enable-aci
CONFIGURE_OPTIONS += --enable-wrappers
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
CONFIGURE_OPTIONS += LDFLAGS=-L$(OPENSSL_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += CPPFLAGS="-I$(OPENSSL_INCDIR) -I/usr/include/odbc"

# Force known perl version
CONFIGURE_ENV += PERLBIN=$(PERL)

COMPONENT_TEST_ENV += LD_LIBRARY_PATH="$(PROTOUSRLIBDIR):$(PROTOUSRLIBDIR64):"
# Put /usr/gnu/bin before /usr/bin first as the test suite uses "date -d"
COMPONENT_TEST_ENV += PATH="$(PROTOUSRSBINDIR):$(PROTOUSRBINDIR):$(PATH.gnu)"

# Tests take about 40 minutes to run.  Note that many of the
# replication tests are flaky.  The increased sleep times help, as
# does running the tests in tmpfs (if you have the memory for it)

# Keep going after a test failure
COMPONENT_TEST_ENV += NOEXIT=1
# Wait a little longer for convergence
COMPONENT_TEST_ENV += SLEEP1=20
COMPONENT_TEST_ENV += SLEEP2=40

# to remove plugin.la dependency
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e 's:.la$$:.so:' $(PROTOETCDIR)/$(COMPONENT_NAME)/slapd.* ;

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
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += security/argon2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES.perl += runtime/perl
