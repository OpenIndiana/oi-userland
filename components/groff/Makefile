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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		groff
COMPONENT_VERSION=	1.22.2
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/groff/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:380864dac4772e0c0d7b1282d25d0c5fd7f63baf45c87c4657afed22a13d2076
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/groff

TPNO=			8829

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# The grog.sh script needs GNU awk not the Solaris one.
COMPONENT_PRE_CONFIGURE_ACTION = \
	$(GSED) -i -e 's?awk?/usr/gnu/bin/awk?' \
		$(SOURCE_DIR)/src/roff/grog/grog.sh

# There are _GL_INLINE_HEADER_BEGIN and _GL_INLINE_HEADER_END definitions in
# .../src/libs/gnulib/lib/wctype.h that are not being processed. There is
# code in .../src/libs/gnulib/config.h that would do this, but this header
# files is not included by wctype.h (or the C++ files that use it and fail
# to build with the Studio compilers:
# .../src/roff/troff/[env.cpp, input.cpp, node.cpp]
# See CR #17959391 for more details.
COMPONENT_POST_CONFIGURE_ACTION = \
	$(GSED) -i -e 's/_GL_INLINE_HEADER_BEGIN//' \
		-e 's/_GL_INLINE_HEADER_END//' \
		$(SOURCE_DIR)/src/libs/gnulib/lib/wctype.in.h

# Everything is under /usr/bin and /usr/lib so set bindir and libdir correctly.
CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS += \
    --with-appresdir=$(CONFIGURE_PREFIX)/X11/lib/X11/app-defaults

CONFIGURE_OPTIONS +=	CXX="$(CXX)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"

# Don't generate tmac wrappers for the Solaris troff macro packages.
# Some man pages (such as groff.1) use long macro name definitions
# which fail in compatibility mode. See:
# http://osdir.com/ml/printing.groff.general/2003-07/msg00088.html
# for more details.
COMPONENT_INSTALL_ARGS += tmac_wrap=""

COMPONENT_INSTALL_ARGS += legacyfontdir=$(PROTOUSRLIBDIR)/font
COMPONENT_INSTALL_ARGS += sys_tmac_prefix=$(PROTOUSRSHARELIBDIR)/tmac/

COMPONENT_PRE_INSTALL_ACTION = \
	($(MKDIR) $(PROTOUSRBINDIR) )

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/perl-520
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/doctools
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/toolkit/libxaw7
REQUIRED_PACKAGES += x11/library/toolkit/libxt
