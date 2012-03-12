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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pcre
COMPONENT_VERSION=	8.21
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:dffb43eff9729c0999843a86ef97961b8c4f6ac8
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/pcre/files/pcre/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://pcre.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/lint-libraries.mk

# pick up -xc99=all in CFLAGS
studio_C99MODE=        $(studio_C99_ENABLE)

# pick up -xlang=c99 in XPG5MODE
studio_cplusplus_C99MODE=	$(studio_cplusplus_C99_ENABLE)

# turn on largefile support
CFLAGS+=	$(CPP_LARGEFILES)

CFLAGS+=	$(XPG6MODE)

# Although -norunpath is set for CXXFLAGS, we need to put -norunpath 
# here, otherwise -norunpath doesn't get set when creating the shared 
# libraries (CC -G).
CXX+=	$(studio_NORUNPATH)

CXXFLAGS+=	$(CC_PIC)

# turn on support for large files
CXXFLAGS+=	$(CPP_LARGEFILES)

CXXFLAGS+=	$(XPG5MODE)

# We need to do this because libtool adds wrong paths to RPATH.
LDFLAGS += -L$(CONFIGURE_LIBDIR.$(BITS)) -R$(CONFIGURE_LIBDIR.$(BITS))

LINTFLAGS+=	-I. $(studio_XBITS) $(CPP_LARGEFILES)

CONFIGURE_ENV+= "CC=$(CC)"
CONFIGURE_ENV+=	"CFLAGS=$(CFLAGS)"
CONFIGURE_ENV+=	"CPP=$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV+= "CXX=$(CXX)"
CONFIGURE_ENV+=	"CXXFLAGS=$(CXXFLAGS)"
CONFIGURE_ENV+=	"CXXCPP=$(CXX) $(CPPFLAGS) $(CXXFLAGS) -E"
CONFIGURE_ENV+=	"LDFLAGS=$(LDFLAGS)"
CONFIGURE_ENV+=	"CXXLDFLAGS=$(LDFLAGS)"
CONFIGURE_ENV+= "CXXLD=$(CXX) $(CXXFLAGS) $(LDFLAGS)"
CONFIGURE_ENV+= "INSTALL=$(INSTALL)"
CONFIGURE_ENV+= "MAKE=$(GMAKE)"

CONFIGURE_ENV.64+= "CXXLINKLIB=$(CXX) $(CCFLAGS) $(LDFLAGS)"
CONFIGURE_ENV.64+= "MACH64=$(MACH64)"

CONFIGURE_OPTIONS+=	--includedir=$(CONFIGURE_INCLUDEDIR)/pcre
CONFIGURE_OPTIONS+=	--localstatedir=/var
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--enable-cpp
CONFIGURE_OPTIONS+=	--enable-rebuild-chartables
CONFIGURE_OPTIONS+=	--enable-utf8
CONFIGURE_OPTIONS+=	--enable-unicode-properties
CONFIGURE_OPTIONS+=	--enable-newline-is-any
CONFIGURE_OPTIONS+=	--disable-stack-for-recursion
CONFIGURE_OPTIONS+=	--enable-pcregrep-libz
CONFIGURE_OPTIONS+=	--enable-pcregrep-libbz2
CONFIGURE_OPTIONS+=	--with-posix-malloc-threshold=20
CONFIGURE_OPTIONS+=	--with-link-size=4
CONFIGURE_OPTIONS+=	--with-match-limit=10000000
CONFIGURE_OPTIONS+=	--with-pic

CONFIGURE_OPTIONS.64+=	--libexecdir=$(CONFIGURE_PREFIX)/libexec/$(MACH64)

COMPONENT_BUILD_ENV+=	"LDFLAGS=$(LDFLAGS)"
COMPONENT_BUILD_ENV+=	"INSTALL=$(INSTALL)"
COMPONENT_BUILD_ENV+=	"MAKE=$(GMAKE)"

COMPONENT_BUILD_ARGS+=	-e

COMPONENT_INSTALL_ARGS+=	"INSTALL=$(INSTALL)"
COMPONENT_INSTALL_ARGS+=	"MAKE=$(GMAKE)"

# common targets

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
