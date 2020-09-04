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

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmicrohttpd
COMPONENT_VERSION=	0.9.71
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libmicrohttpd/
COMPONENT_FMRI=		library/libmicrohttpd
COMPONENT_SUMMARY=	GNU libmicrohttpd is a small HTTP server as a C library
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e8f445e85faf727b89e9f9590daea4473ae00ead38b237cf1eda55172b89b182
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE).sig
COMPONENT_LICENSE=	LGPL2.1+
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

# Tests work properly only for curl with GnuTLS SSL backend (we use OpenSSL only),
# see https://gnunet.org/bugs/view.php?id=5564.
TEST_TARGET=		$(TEST_32_and_64)

include $(WS_MAKE_RULES)/common.mk

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

REQUIRED_PACKAGES += system/library/security/libgcrypt
# Auto-generated dependencies
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += system/library
