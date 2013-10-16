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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gdb
COMPONENT_VERSION=	7.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8070389a5dcc104eb0be483d582729f98ed4d761ad19cedd3f17b5d2502faa36
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gdb/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =	http://www.gnu.org/software/gdb/
COMPONENT_BUGDB=	utility/gdb

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# GDB wants the GNU utilities
PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

# There are a large number of macros in the GCB code written
# specifically for GCC's preprocessor. Studio does not expand
# these macros the same way GCC does, and the resulting gdb is
# not usable. Building gdb with a GCC >= 4.7.2 produces very
# good results, even on SPARC.
CC = /usr/gcc/4.7/bin/gcc
CXX = /usr/gcc/4.7/bin/g++

CFLAGS_sparc =	-g -O2 -mcpu=ultrasparc -mtune=ultrasparc
CFLAGS_sparc +=	-mno-unaligned-doubles
CFLAGS_sparc += -mapp-regs -mhard-float
CFLAGS_i386 =	-g -O2 -march=opteron -mtune=opteron
CFLAGS_EXTRA = -Wall -Wno-long-long -Wcast-align -fno-omit-frame-pointer

CFLAGS = $(CC_BITS) $(CFLAGS_EXTRA) $(CFLAGS_$(MACH))
CXXFLAGS = $(CC_BITS) $(CFLAGS_EXTRA) $(CFLAGS_$(MACH))
CPPFLAGS = -D_REENTRANT -I/usr/include/ncurses

# `echo $(CFLAGS)` and `echo $(LDFLAGS)` used to
# work around problem with extra blank characters
# inserted into configrue option strings during
# nested configure invocations within the gdb build.

CONFIGURE_ENV += CFLAGS="`echo $(CFLAGS)`"
CONFIGURE_ENV += CPPFLAGS="`echo $(CPPFLAGS)`"
CONFIGURE_ENV += LDFLAGS="`echo $(LDFLAGS)`"

CONFIGURE_OPTIONS += --with-system-readline
CONFIGURE_OPTIONS += --with-x=no
CONFIGURE_OPTIONS += --with-curses
CONFIGURE_OPTIONS += --disable-werror
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-tui
CONFIGURE_OPTIONS += --without-auto-load-safe-path
CONFIGURE_OPTIONS += --with-python=yes
CONFIGURE_OPTIONS += --with-libexpat-prefix=/usr/lib
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)

# Generate the newly added Solaris instruction and
# register tables which weren't there by default.
COMPONENT_PRE_CONFIGURE_ACTION = \
  ( cd  $(SOURCE_DIR)/gdb/features ; \
    $(GMAKE) all )

COMPONENT_POST_INSTALL_ACTION = \
  ( cd  $(PROTOUSRDIR)/share/gdb/python/gdb ; \
      $(PYTHON) -m compileall . ; \
    cd  $(PROTOUSRDIR)/share/gdb/python/gdb/command ; \
      $(PYTHON) -m compileall . ; \
    cd  $(PROTOUSRDIR)/share/gdb/python/gdb/function ; \
      $(PYTHON) -m compileall . ; \
    cd  $(PROTOUSRBINDIR64)/ ; \
      /usr/bin/strip -x gdb ; \
    cd  $(COMPONENT_DIR) ; \
      $(INSTALL) -m 0755 $(COMPONENT_DIR)/Solaris/gdbtui \
	$(PROTOUSRBINDIR)/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-1  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-2  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-3  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-4  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-5  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-6  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdb.info-7  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdbint.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdbint.info-1  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/gdbint.info-2  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/annotate.info  \
	$(PROTOUSRSHAREDIR)/info/ ; \
      $(INSTALL) -m 0644 $(SOURCE_DIR)/gdb/doc/stabs.info  \
	$(PROTOUSRSHAREDIR)/info/ )

# Disable ASLR: it's a debugger and we do not want to risk
# altering the results of the debugging experiment.
ASLR_MODE=$(ASLR_DISABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
