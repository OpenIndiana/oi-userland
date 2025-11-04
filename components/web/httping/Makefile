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
# CDDL HEADER END
#
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017 Adam Stevko
# Copyright 2020 Andreas Wacknitz
#
BUILD_STYLE=		justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		httping
COMPONENT_VERSION=	2.5
COMPONENT_REVISION=	1
COMPONENT_FMRI=		diagnostic/httping
COMPONENT_SUMMARY=	Ping using HTTP requests
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_DESCRIPTION=	Give httping an url, and it'll show you how long it takes to connect, send a request and retrieve the reply (only the headers).
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.vanheusden.com/httping/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
	sha256:3e895a0a6d7bd79de25a255a1376d4da88eb09c34efdd0476ab5a907e75bfaf8
COMPONENT_ARCHIVE_URL=	https://critical.ch/distfiles/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		AGPL v3

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CC +=		$(CC_BITS)

EXTRA_LIBRARIES =	-lsocket -lnsl
EXTRA_LIBRARIES +=	-lncurses -lfftw3 -lssl -lcrypto -lresolv -lm

# Provide location for openssl-3 headers/libraries
CFLAGS += -I$(OPENSSL_INCDIR)
LDFLAGS  += -L$(OPENSSL_LIBDIR)

# The usual Solaris curses.h vs ncurses/curses.h mess.
CFLAGS += -I$(USRINCDIR)/ncurses

# Override the values in the Makefile but get optimization level etc. from 
# make-rules/shared-macros.mk.
COMPONENT_BUILD_ARGS += NC=yes
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += OFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS) $(EXTRA_LIBRARIES)"

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
