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

COMPONENT_NAME=		bash
COMPONENT_VERSION=	4.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/bash/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3f627124a83c6d34db503a923e20710d370573a29dd5d11d6f116d1aee7be1da
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/bash/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

IPS_COMPONENT_VERSION = $(COMPONENT_VERSION).9
PATCH_LEVEL = 0

PKG_PROTO_DIRS += $(COMPONENT_DIR)/Solaris

# Enable C99 mode + -Xc for it's additional warnings.
studio_C99MODE = -Xc $(studio_C99_ENABLE)

# Use the maximum number of registers on sparc since we have no libraries
studio_XREGS.sparc = -xregs=appl

# 8 byte memory alignment + interpretation of non-alignment instead of SIGBUS
studio_ALIGN.sparc.32 = -xmemalign=8i

# -xinline=%auto -- we like inlining where appropriate
CFLAGS += -xinline=%auto

# -xbuiltin=%none -- builtins have been known to be buggy
CFLAGS += -xbuiltin=%none

CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)

# configure checks for some functions, but doesn't seem to want to link in
# the required libraries for them. We avoid linking with libthread.so.1
# just because we pass -mt, by explicitly passing -lc.
LIBS =	-lc -lsocket -lgen

# -z redlocsym -- let's shrink the SHT_SYMTAB as much as we can
LDFLAGS =	$(LD_Z_REDLOCSYM)

# The bash test harness needs the GNU userland utilities
TEST_PATH = "PATH=$(BUILD_DIR_32):$(GNUBIN):$(USRBINDIR)"
TEST_OUTPUT = $(COMPONENT_DIR)/bash_test_results_$(MACH).out

CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV +=	LIBS="$(LIBS)"

CONFIGURE_OPTIONS  +=		--localstatedir=/var
CONFIGURE_OPTIONS  += 		--enable-alias
CONFIGURE_OPTIONS  += 		--enable-arith-for-command
CONFIGURE_OPTIONS  += 		--enable-array-variables
CONFIGURE_OPTIONS  += 		--enable-bang-history	
CONFIGURE_OPTIONS  += 		--enable-brace-expansion	
CONFIGURE_OPTIONS  += 		--enable-casemod-attributes	
CONFIGURE_OPTIONS  += 		--enable-casemod-expansions	
CONFIGURE_OPTIONS  += 		--enable-command-timing	
CONFIGURE_OPTIONS  += 		--enable-cond-command	
CONFIGURE_OPTIONS  += 		--enable-cond-regexp	
CONFIGURE_OPTIONS  += 		--enable-coprocesses	
CONFIGURE_OPTIONS  += 		--enable-debugger	
CONFIGURE_OPTIONS  += 		--enable-directory-stack	
CONFIGURE_OPTIONS  += 		--enable-disabled-builtins	
CONFIGURE_OPTIONS  += 		--enable-dparen-arithmetic	
CONFIGURE_OPTIONS  += 		--enable-extended-glob	
CONFIGURE_OPTIONS  += 		--enable-help-builtin	
CONFIGURE_OPTIONS  += 		--enable-history	
CONFIGURE_OPTIONS  += 		--enable-job-control	
CONFIGURE_OPTIONS  += 		--enable-multibyte	
CONFIGURE_OPTIONS  += 		--enable-net-redirections	
CONFIGURE_OPTIONS  += 		--enable-process-substitution	
CONFIGURE_OPTIONS  += 		--enable-progcomp	
CONFIGURE_OPTIONS  += 		--enable-prompt-string-decoding	
CONFIGURE_OPTIONS  += 		--enable-readline	
CONFIGURE_OPTIONS  += 		--enable-restricted	
CONFIGURE_OPTIONS  += 		--enable-select	
CONFIGURE_OPTIONS  += 		--enable-separate-helpfiles	
CONFIGURE_OPTIONS  += 		--enable-single-help-strings	
CONFIGURE_OPTIONS  += 		--disable-strict-posix-default	
CONFIGURE_OPTIONS  += 		--enable-usg-echo-default	
CONFIGURE_OPTIONS  += 		--enable-xpg-echo-default	
CONFIGURE_OPTIONS  += 		--enable-mem-scramble	
CONFIGURE_OPTIONS  += 		--disable-profiling	
CONFIGURE_OPTIONS  += 		--enable-static-link	
CONFIGURE_OPTIONS  += 		--enable-largefile
CONFIGURE_OPTIONS  += 		--enable-nls	
CONFIGURE_OPTIONS  += 		--with-bash-malloc	
CONFIGURE_OPTIONS  += 		--with-curses	
CONFIGURE_OPTIONS  += 		--with-installed-readline=no	
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)

TEST_ENV +=	-i
TEST_ENV +=	$(TEST_PATH)
TEST_ENV +=	$(TARGET_ENV)

build: $(BUILD_32)

install: $(INSTALL_32)
	( cd $(PROTOUSRSHAREDIR)/locale ; \
	    cp -Rp "en@boldquot" en ; \
	    cp -Rp "en@boldquot" en_CA ; \
	    cp -Rp "en@boldquot" en_GB )

test: $(TEST_32)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

