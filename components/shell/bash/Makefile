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
# Copyright (c) 2019, Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bash
COMPONENT_VERSION=	5.0
COMPONENT_REVISION=	2
COMPONENT_FMRI=		shell/bash
COMPONENT_SUMMARY=	GNU Bourne-Again shell (bash)
COMPONENT_CLASSIFICATION=	System/Shells
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/bash/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = \
    sha256:b4a80f2ac66170b2913efbfb9f2594f1f76c7b1afd11f799e22035d63077fb4d
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/bash/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3, FDLv1.2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

BASH_PATCHLEVEL=$(shell grep -h "define PATCHLEVEL" $(COMPONENT_DIR)/patches/bash* | nawk '{print $$NF}' | sort -n | tail -1)
IPS_COMPONENT_VERSION = $(COMPONENT_VERSION).$(BASH_PATCHLEVEL)
PATCH_LEVEL = 0

PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

CFLAGS += -I/usr/include/ncurses

# configure checks for some functions, but doesn't seem to want to link in
# the required libraries for them. We avoid linking with libthread.so.1
# just because we pass -mt, by explicitly passing -lc.
LIBS =	-lc -lsocket -lgen

# -z redlocsym -- let's shrink the SHT_SYMTAB as much as we can
LDFLAGS =	$(LD_Z_REDLOCSYM)

# The bash test harness needs the GNU userland utilities
TEST_PATH = "PATH=$(BUILD_DIR_64):$(GNUBIN):$(USRBINDIR)"

COMPONENT_PREP_ACTION = ( cd $(@D); autoconf -f -i )

CONFIGURE_ENV += LIBS="$(LIBS)"
CONFIGURE_ENV += LD_OPTIONS="-lc -lm -lgen -lsocket -lnsl -lresolv $(LD_Z_IGNORE)"

CONFIGURE_OPTIONS += --disable-profiling
CONFIGURE_OPTIONS += --disable-strict-posix-default
CONFIGURE_OPTIONS += --enable-alias
CONFIGURE_OPTIONS += --enable-arith-for-command
CONFIGURE_OPTIONS += --enable-array-variables
CONFIGURE_OPTIONS += --enable-bang-history
CONFIGURE_OPTIONS += --enable-brace-expansion
CONFIGURE_OPTIONS += --enable-casemod-attributes
CONFIGURE_OPTIONS += --enable-casemod-expansions
CONFIGURE_OPTIONS += --enable-command-timing
CONFIGURE_OPTIONS += --enable-cond-command
CONFIGURE_OPTIONS += --enable-cond-regexp
CONFIGURE_OPTIONS += --enable-coprocesses
CONFIGURE_OPTIONS += --enable-debugger
CONFIGURE_OPTIONS += --enable-directory-stack
CONFIGURE_OPTIONS += --enable-disabled-builtins
CONFIGURE_OPTIONS += --enable-dparen-arithmetic
CONFIGURE_OPTIONS += --enable-extended-glob
CONFIGURE_OPTIONS += --enable-help-builtin
CONFIGURE_OPTIONS += --enable-history
CONFIGURE_OPTIONS += --enable-job-control
CONFIGURE_OPTIONS += --enable-largefile
CONFIGURE_OPTIONS += --enable-mem-scramble
CONFIGURE_OPTIONS += --enable-multibyte
CONFIGURE_OPTIONS += --enable-net-redirections
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --enable-process-substitution
CONFIGURE_OPTIONS += --enable-progcomp
CONFIGURE_OPTIONS += --enable-prompt-string-decoding
CONFIGURE_OPTIONS += --enable-readline
CONFIGURE_OPTIONS += --enable-restricted
CONFIGURE_OPTIONS += --enable-select
CONFIGURE_OPTIONS += --enable-separate-helpfiles
CONFIGURE_OPTIONS += --enable-single-help-strings
CONFIGURE_OPTIONS += --enable-static-link
CONFIGURE_OPTIONS += --enable-usg-echo-default=yes
CONFIGURE_OPTIONS += --enable-xpg-echo-default=yes
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-bash-malloc=yes
CONFIGURE_OPTIONS += --with-curses
CONFIGURE_OPTIONS += --with-installed-readline=no

COMPONENT_TEST_DIR =		$(BUILD_DIR_64)
COMPONENT_TEST_ENV =		- $(TEST_PATH)

COMPONENT_TEST_MASTER		= \
    $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

# The tests use /tmp/xx, and there can only be one user running
# the them at a time. Need to remove /tmp/xx after testing to
# avoid permission issues for other users running these tests
COMPONENT_POST_TEST_ACTION =	rm -f /tmp/xx

build: $(BUILD_64)

install: $(INSTALL_64)
	( cd $(PROTOUSRSHAREDIR)/locale ; \
	    cp -Rp "en@boldquot" en ; \
	    cp -Rp "en@boldquot" en_CA ; \
	    cp -Rp "en@boldquot" en_GB )

test:	$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
