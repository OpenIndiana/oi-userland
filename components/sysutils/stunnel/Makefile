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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# copyright (c) 2021, Tim Mooney.  All rights reserved.
#

BUILD_BITS=             64
USE_OPENSSL11=          yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         stunnel
COMPONENT_VERSION=      5.60
COMPONENT_SUMMARY=	A TLS-encrypting socket wrapper
COMPONENT_PROJECT_URL=  https://www.stunnel.org/
COMPONENT_FMRI=		service/security/stunnel
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:c45d765b1521861fea9b03b425b9dd7d48b3055128c0aec673bba5ef9b8f787d
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/downloads/archive/5.x/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

# need /usr/perl5/bin on path to access pod2man perl script, used by 
# the build to create docs. 
# Perl 5.10 pod2man does not recognize "-u" argument.
COMPONENT_BUILD_ENV +=  PATH=$(PERL5BINDIR):$(PATH)

CPPFLAGS +=	"-DPIDFILE='\"/var/run/stunnel.pid\"'"

# used to generate the 64-bit interposer location
CPPFLAGS += -DMACH64='\"$(MACH64)\"'

CONFIGURE_OPTIONS +=	--disable-fips
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS +=	CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
# work around Linux-specific LDFLAGS
CONFIGURE_OPTIONS +=	LDFLAGS="-L$(OPENSSL_PREFIX)/lib/$(MACH64) $(LDFLAGS)"

# used to generate LD_PRELOAD_* interposer pathnames
COMPONENT_BUILD_ARGS += pkglibdir=/usr/lib/stunnel

COMPONENT_PRE_INSTALL_ACTION = \
	$(MKDIR) $(PROTOETCDIR)/stunnel ; \
	$(MKDIR) $(PROTOETCDIR)/stunnel/conf.d ; \
	$(TOUCH) $(PROTOETCDIR)/stunnel/stunnel.pem

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

ASLR_MODE = $(ASLR_ENABLE)

unexport SHELLOPTS
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^test /p" ' \
	'-e "/^summary: /p" '

# ncat needed for test suite
REQUIRED_PACKAGES += diagnostic/nmap-cli

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
