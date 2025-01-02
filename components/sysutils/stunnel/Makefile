#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# copyright (c) 2021, Tim Mooney.  All rights reserved.
# Copyright (c) 2025 Goetz Fischer, R-A-C. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         stunnel
COMPONENT_VERSION=      5.74
COMPONENT_SUMMARY=	A TLS-encrypting socket wrapper
COMPONENT_PROJECT_URL=  https://www.stunnel.org/
COMPONENT_FMRI=		service/security/stunnel
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:9bef235ab5d24a2a8dff6485dfd782ed235f4407e9bc8716deb383fc80cd6230
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/downloads/archive/5.x/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

# need /usr/perl5/bin on path to access pod2man perl script, used by
# the build to create docs.
COMPONENT_BUILD_ENV +=  PATH=$(PERL5BINDIR):$(PATH)

CPPFLAGS +=	"-DPIDFILE='\"/var/run/stunnel.pid\"'"

# used to generate the 64-bit interposer location
CPPFLAGS += -DMACH64='\"$(MACH64)\"'

CONFIGURE_OPTIONS += --disable-fips
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
# work around Linux-specific LDFLAGS
CONFIGURE_OPTIONS += LDFLAGS="-L$(OPENSSL_PREFIX)/lib/$(MACH64) $(LDFLAGS)"

# used to generate LD_PRELOAD_* interposer pathnames
COMPONENT_BUILD_ARGS += pkglibdir=/usr/lib/stunnel

COMPONENT_PRE_INSTALL_ACTION = \
	$(MKDIR) $(PROTOETCDIR)/stunnel ; \
	$(MKDIR) $(PROTOETCDIR)/stunnel/conf.d ; \
	$(TOUCH) $(PROTOETCDIR)/stunnel/stunnel.pem

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files
ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_TEST_TRANSFORMS += \
'-n ' \
'-e "/^[0-9]/p" ' \
'-e "/succeeded/p" ' \
'-e "/skipped/p" ' \
'-e "/failed/p" ' \
'-e "/^ /p" ' \
'-e "/^Summary:/p" '

# ncat needed for test suite
REQUIRED_PACKAGES += diagnostic/nmap

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
