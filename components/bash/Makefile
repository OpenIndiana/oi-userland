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
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bash
COMPONENT_VERSION=	4.4
COMPONENT_ARCHIVE_HASH = \
    sha256:d86b3392c1202e8ff5a423b302e6284db7f8f435ea9f39b5b1b20fd3ac36dfcb

TPNO=			32706

include $(WS_MAKE_RULES)/gnu-component.mk

# Avoid running configure again during the build due to patches to
# configure-related files by running autoconf before we run configure.
COMPONENT_PREP_ACTION += (cd $(@D); autoconf)

BASH_PATCHLEVEL=$(shell grep -h "define PATCHLEVEL" $(COMPONENT_DIR)/patches/bash* | $(NAWK) '{print $$NF}' | sort -n | tail -1)
IPS_COMPONENT_VERSION = $(COMPONENT_VERSION).$(BASH_PATCHLEVEL)
PATCH_LEVEL = 0

PKG_PROTO_DIRS += $(COMPONENT_DIR)/Solaris

# Enable C99 mode + -Xc for its additional warnings.
studio_C99MODE = -Xc $(studio_C99_ENABLE)

# Use the maximum number of registers on sparc since we have no libraries
studio_XREGS.sparc = -xregs=appl

# 8 byte memory alignment + interpretation of non-alignment instead of SIGBUS
studio_ALIGN.sparc.32 = -xmemalign=8i
studio_ALIGN.sparc.64 = -xmemalign=16i

# -xinline=%auto -- we like inlining where appropriate
CFLAGS += -xinline=%auto

# -xbuiltin=%none -- builtins have been known to be buggy
CFLAGS += -xbuiltin=%none

CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += -I$(USRINCDIR)/ncurses

# configure checks for some functions, but doesn't seem to want to link in
# the required libraries for them. We avoid linking with libthread.so.1
# just because we pass -mt, by explicitly passing -lc.
LIBS =	-lc -lgen
ifeq ($(OS_VERSION),5.11)
LIBS +=	-lsocket
endif

# -z redlocsym -- let's shrink the SHT_SYMTAB as much as we can
LDFLAGS =	$(LD_Z_REDLOCSYM)

# This avoids the need to patch configure or other files for these dependencies.
ifeq ($(OS_VERSION), 5.11)
CONFIGURE_ENV += LD_OPTIONS="-lc -lm -lgen -lsocket -lnsl -lresolv $(LD_Z_IGNORE)"
else
CONFIGURE_ENV += LD_OPTIONS="-lc -lm -lgen -lresolv $(LD_Z_IGNORE)"
endif

CONFIGURE_ENV +=	LIBS="$(LIBS)"

# Ignore tgetent() checks in configure and use libncurses on Solaris.
CONFIGURE_ENV += ac_cv_func_tgetent=yes
CONFIGURE_ENV += ac_cv_lib_termcap_tgetent=no
CONFIGURE_ENV += ac_cv_lib_curses_tgetent=no
CONFIGURE_ENV += ac_cv_lib_ncurses_tgetent=yes
CONFIGURE_ENV += bash_cv_termcap_lib=libncurses

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
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --with-bash-malloc=yes
CONFIGURE_OPTIONS += --with-curses
CONFIGURE_OPTIONS += --with-installed-readline=no

COMPONENT_TEST_DIR		= $(BUILD_DIR_64)
COMPONENT_TEST_ENV		= - $(TEST_PATH)
# The bash test harness needs the GNU userland utilities
TEST_PATH	= "PATH=$(GNUBIN):$(USRBINDIR)"
# Results output is slightly different on Intel vs. SPARC.
COMPONENT_TEST_MASTER		= \
    $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master


# The goal is to remove lines like
#   71d70
#   < +[8] cat
# from the test-trap output. To have full controll over the output I use -n
# gsed parameter (don't print the output automatically)
COMPONENT_TEST_TRANSFORMS       += \
	-n \
	'-e "                           \n\
	    /^run-trap$$/,/^run-/ {     \n\
	        \# For text region from ^run-trap$$ till any line beginning with ^run- \n\
	        /^[^0-9<>]/ {           \n\
	            \# If the line does _NOT_ start with number or < or >, print it \n\
	            p                   \n\
	        }                       \n\
		\# and delete the line so that it does not get printed by the last p command \n\
	        d                       \n\
	    }                           \n\
	    \# Everything else gets printed \n\
	    p                           \n\
	"'

COMPONENT_POST_INSTALL_ACTION += \
	( cd $(PROTOUSRSHAREDIR)/locale ; \
	    cp -Rp "en@boldquot" en ; \
	    cp -Rp "en@boldquot" en_CA ; \
	    cp -Rp "en@boldquot" en_GB )

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += shell/ksh93

