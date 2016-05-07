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
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		trousers
COMPONENT_VERSION=	0.3.13
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/trousers/files/trousers/
COMPONENT_ARCHIVE_HASH=	\
	sha256:bb908e4a3c88a17b247a4fc8e0fff3419d8a13170fe7bdfbe0e2c5c082a276d3
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/tss

TPNO=			27256

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL=0

ifeq ($(OS_VERSION),5.11)
# These libraries are in libc for S12:
LIBS=-lnsl -lsocket
# Use the "new" POSIX thread API (not the "draft" prototype):
CFLAGS += "-D_POSIX_PTHREAD_SEMANTICS"
endif

# Trousers 0.3.13 requires automake/autoconf >= 1.13, but Userland default
# is older than what is needed. So hard-coding to the next available, 1.15:
# "--add-missing" needed to use default "compile" script.
AUTOMAKE=/usr/bin/automake-1.15 --add-missing
ACLOCAL=/usr/bin/aclocal-1.15

LIBS += -lgen

LDFLAGS += -lbsm -lscf -lresolv

CONFIGURE_OPTIONS += --sbindir=$(USRLIBDIR)
# 'openssl' is an undocumented option that causes trousers to use OpenSSL's UI
# interfaces for text-based PIN entry.
CONFIGURE_OPTIONS += --with-gui=openssl
CONFIGURE_OPTIONS += LD="$(CC)"
CONFIGURE_OPTIONS += LIBS="$(LIBS)"

COMPONENT_POST_CONFIGURE_ACTION = (cd $(COMPONENT_SRC); \
	for f in `ls src/include/tss/*.h` ; do \
		/usr/bin/dos2unix $$f $$f; \
	done; \
	for f in `ls src/include/trousers/*.h` ; do \
		/usr/bin/dos2unix $$f $$f; \
	done; \
	for f in `ls src/include/*.h` ; do \
		/usr/bin/dos2unix $$f $$f; \
	done; \
	/usr/bin/libtoolize -f; \
	$(ACLOCAL); \
	$(AUTOMAKE) src/tspi/Makefile; \
	$(AUTOCONF))	

#
# We had to use cc as the linker (see CONFIGURE_OPTIONS above) so the
# .init and .fini sections get set correctly.  Because we use cc, we
# must pass the -m64 flag through cc to the linker when building 64 bit
# libraries.  We can't just add it to LDFLAGS because then it gets used
# when creating executables and static libs and generates lots of noise
# in the build logs.  LDARCHFLAG is only recognized by the Makefile in
# the src/tspi directory.
#
COMPONENT_BUILD_ENV.64 += LDARCHFLAG="-Wl,$(CC_BITS)"

# For regression testing, use STC test suite "tss".
# It requires a machine with TPM hardware that's enabled and initialized.
COMPONENT_TEST_TARGETS =

COMPONENT_BUILD_TARGETS = all

# These are packages required for building, not for use:
REQUIRED_PACKAGES += developer/build/automake-115
REQUIRED_PACKAGES += developer/build/libtool
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
