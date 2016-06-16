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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
# Build gcc with gcc
COMPILER= gcc
include ../../make-rules/shared-macros.mk

# build with itself until it's gone
GCC_ROOT =	/usr/gcc/3.4

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	3.4.3
COMPONENT_PROJECT_URL=	http://gcc.gnu.org/
# unfortunately we have our own "special" tarball and not the community version, so use that.
COMPONENT_ARCHIVE_HASH=	\
    sha256:3ab488fe2df01bf54a57acd70e745266e19232edacf77512f77655296748e7a0
COMPONENT_ARCHIVE_URL=	$(EXTERNAL_ARCHIVE_MIRROR)/$(SOURCE_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-compiler

TPNO=			17028

# Bootstrapping problems.  To be obsoleted soon, so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32=
INSTALL_32=
PUBLISH_STAMP=
endif

INSTALL_TARGET=
include $(WS_MAKE_RULES)/gnu-component.mk

PARCH =		$(MACH:i386=i386-pc)
GNU_ARCH =	$(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)

PKG_MACROS +=	GNU_ARCH="$(GNU_ARCH)"

# Make sure to pass -m32/64 any time the installed GCC is used 
CC += -m$(BITS)
CXX += -m$(BITS)

# CC_BITS may get in the way
CC_BITS=

# enabling this causes libstdc++ to break
LD_B_DIRECT=

CFLAGS += -std=gnu89

# gcc3 doesn't support -mincoming-stack-boundary, but doesn't need it either.
gcc_STACK_ALIGN.i386.32 =

CONFIGURE_PREFIX =	/usr/gcc/3.4
CONFIGURE_INFODIR =	$(CONFIGURE_PREFIX)/share/info

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--without-gnu-ld --with-ld=$(LD)
CONFIGURE_OPTIONS +=	--enable-languages='c,c++,f77,objc'
CONFIGURE_OPTIONS +=	--enable-shared
# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=$(USRBINDIR)/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=$(GNUBIN)/as

COMPONENT_BUILD_ENV += STAGE1_CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CFLAGS_FOR_TARGET="$(CFLAGS)"
COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)
COMPONENT_BUILD_TARGETS = bootstrap

# common targets
ifneq ($(BUILD_TYPE), evaluation)
$(PROTO_DIR)/.sedded:	$(INSTALL_32)
	(cd $(@D) ; for file in libstdc++.la libsupc++.la ; do \
		$(MV) usr/gcc/3.4/lib/$$file usr/gcc/3.4/lib/$$file.orig ; \
		sed -e "s;\\(dependency_libs=\\).*;\\1' -L/usr/gcc/3.4/lib -lgcc_s -lm';" usr/gcc/3.4/lib/$$file.orig >usr/gcc/3.4/lib/$$file ; \
		$(MV) usr/gcc/3.4/lib/$(MACH64)/$$file usr/gcc/3.4/lib/$(MACH64)/$$file.orig ; \
		sed -e "s;\\(dependency_libs=\\).*;\\1' -L/usr/gcc/3.4/lib/$(MACH64) -lgcc_s -lm';" usr/gcc/3.4/lib/$(MACH64)/$$file.orig >usr/gcc/3.4/lib/$(MACH64)/$$file ; \
	 done)
	$(TOUCH) $@

install:	$(PROTO_DIR)/.sedded
endif


REQUIRED_PACKAGES += developer/assembler
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/gcc-3-runtime
REQUIRED_PACKAGES += system/library/math
