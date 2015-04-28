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
# Copyright (c) 2014, 2015, Oracle and/or its affiliates. All rights reserved.
#

COMPILER = gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		w3m
COMPONENT_VERSION=	0.5.3
COMPONENT_PROJECT_URL=	http://w3m.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e994d263f2fd2c22febfbe45103526e00145a7674a0fda79c822b97c2770a9e3
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	utility/w3m

TPNO=			21998

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) ; autoconf ; automake ; aclocal ; libtoolize )

# install the bits in /usr/bin and /usr/lib
CONFIGURE_BINDIR.64 = $(CONFIGURE_BINDIR.32)
CONFIGURE_LIBDIR.64 = $(CONFIGURE_LIBDIR.32)

CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	--libexecdir=$(CONFIGURE_LIBDIR.32)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--with-browser=/usr/bin/firefox

# Use the HTML and CSS styling external test suite as referenced at
# http://www.w3.org/2005/MWI/Tests/
COMPONENT_TEST_CMD = $(@D)/w3m
COMPONENT_TEST_ARGS = -dump \
	http://www.cameronmoll.com/mobile/mkp/pg1.html \
	http://www.cameronmoll.com/mobile/mkp/pg2.html \
	http://www.cameronmoll.com/mobile/mkp/pg3.html \
	http://www.cameronmoll.com/mobile/mkp/pg4.html
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_DIR =
COMPONENT_SYSTEM_TEST_CMD =		/usr/bin/w3m
COMPONENT_SYSTEM_TEST_ARGS =		-dump \
	http://www.cameronmoll.com/mobile/mkp/pg1.html \
	http://www.cameronmoll.com/mobile/mkp/pg2.html \
	http://www.cameronmoll.com/mobile/mkp/pg3.html \
	http://www.cameronmoll.com/mobile/mkp/pg4.html
COMPONENT_SYSTEM_TEST_TARGETS =

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)
system-test:	$(SYSTEM_TEST_64)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/gc
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
