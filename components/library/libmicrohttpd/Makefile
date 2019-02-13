#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmicrohttpd
COMPONENT_VERSION=	0.9.63
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/libmicrohttpd/
COMPONENT_FMRI=		library/libmicrohttpd
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:37c36f1be177f0e37ef181a645cd3baac1000bd322a01c2eff70f3cc8c91749c
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE).sig
COMPONENT_LICENSE=	LGPL2.1+
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY=	GNU libmicrohttpd is a small HTTP server as a C library
COMPONENT_CLASSIFICATION=System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_32 = /usr/lib/pkgconfig/gnutls-3
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.32 += -L/usr/lib/gnutls-3 -R/usr/lib/gnutls-3
LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

CONFIGURE_ENV += LIBS="-lnsl -lsocket"

CONFIGURE_OPTIONS += --enable-epoll=no
CONFIGURE_OPTIONS += --enable-itc=socketpair
CONFIGURE_OPTIONS += --disable-static

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset set unexpectedly,
# and errors such as "libtool_install_magic: unbound variable"
unexport SHELLOPTS

COMPONENT_TEST_ENV += LD_OPTIONS="$(LD_OPTIONS)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Tests work properly only for curl with GnuTLS SSL backend (we use OpenSSL only),
# see https://gnunet.org/bugs/view.php?id=5564.
test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += system/library/security/libgcrypt
# Auto-generated dependencies
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += system/library
