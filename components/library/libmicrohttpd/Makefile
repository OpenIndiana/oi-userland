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

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmicrohttpd
COMPONENT_VERSION=	0.9.77
COMPONENT_SUMMARY=	GNU libmicrohttpd is a small HTTP server as a C library
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libmicrohttpd/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9e7023a151120060d2806a6ea4c13ca9933ece4eacfc5c9464d20edddb76b0a0
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sig
COMPONENT_FMRI=		library/libmicrohttpd
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	LGPL2.1+

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += (cd $(@D) && autoreconf -fi)

CONFIGURE_ENV += LIBS="-lnsl -lsocket"

CONFIGURE_OPTIONS += --enable-epoll=no
CONFIGURE_OPTIONS += --enable-itc=socketpair
CONFIGURE_OPTIONS += --disable-static

# Tests work properly only for curl with GnuTLS SSL backend (we use OpenSSL only),
# see https://gnunet.org/bugs/view.php?id=5564.

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset set unexpectedly,
# and errors such as "libtool_install_magic: unbound variable"
unexport SHELLOPTS

COMPONENT_TEST_ENV += LD_OPTIONS="$(LD_OPTIONS)"

# Manually added build dependencies
REQUIRED_PACKAGES += system/library/security/libgcrypt

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += system/library
