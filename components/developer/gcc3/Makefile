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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	3.4.3
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://gcc.gnu.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
# unfortunately we have our own "special" tarball and not the community version, so use that.
COMPONENT_ARCHIVE_HASH=	\
    sha256:3ab488fe2df01bf54a57acd70e745266e19232edacf77512f77655296748e7a0
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/oi-build/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-compiler

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# we build gcc with gcc
COMPILER =	gcc

# CC_BITS may get in the way
CC_BITS=

# Set standard
CFLAGS   += -std=gnu89
CXXFLAGS += -std=c++98

# enabling this causes libstdc++ to break
LD_B_DIRECT=

COMPONENT_BUILD_ARGS=

CONFIGURE_PREFIX =	/usr/gcc/3.4

# we need to override CONFIGURE_OPTIONS because GCC uses a configure that
# can't deal with CC as an argument
CONFIGURE_OPTIONS =	 --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	 --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS +=	 --infodir=$(CONFIGURE_PREFIX)/share/info
CONFIGURE_OPTIONS +=	--without-gnu-ld --with-ld=/usr/bin/ld
CONFIGURE_OPTIONS +=	--enable-languages='c,c++,f77,objc'
CONFIGURE_OPTIONS +=	--enable-shared
# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=/usr/gnu/bin/as
CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(MACH))

CONFIGURE_ENV += 	CC="$(CC)"
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"

COMPONENT_BUILD_ENV += STAGE1_CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CFLAGS_FOR_TARGET="$(CFLAGS)"
COMPONENT_BUILD_ENV += SHELL=$(CONFIG_SHELL)
COMPONENT_BUILD_TARGETS = bootstrap

# common targets
build:		$(BUILD_32)

$(PROTO_DIR)/.sedded:	$(INSTALL_32)
	(cd $(@D) ; for file in libstdc++.la libsupc++.la ; do \
		$(MV) usr/gcc/3.4/lib/$$file usr/gcc/3.4/lib/$$file.orig ; \
		sed -e "s;\\(dependency_libs=\\).*;\\1' -L/usr/gcc/3.4/lib -lgcc_s -lm';" usr/gcc/3.4/lib/$$file.orig >usr/gcc/3.4/lib/$$file ; \
		$(MV) usr/gcc/3.4/lib/$(MACH64)/$$file usr/gcc/3.4/lib/$(MACH64)/$$file.orig ; \
		sed -e "s;\\(dependency_libs=\\).*;\\1' -L/usr/gcc/3.4/lib/$(MACH64) -lgcc_s -lm';" usr/gcc/3.4/lib/$(MACH64)/$$file.orig >usr/gcc/3.4/lib/$(MACH64)/$$file ; \
	 done)
	$(TOUCH) $@

install:	$(PROTO_DIR)/.sedded

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test: $(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += developer/linker
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/c-runtime
REQUIRED_PACKAGES += system/library/gcc-3-runtime
REQUIRED_PACKAGES += system/library/math
