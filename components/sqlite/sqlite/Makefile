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
# Copyright (c) 2013 Louis M. Picciano. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME			= sqlite
COMPONENT_VERSION		= 3.7.17
TARBALL_VERSION			= 3071700
COMPONENT_SRC			= sqlite-autoconf-$(TARBALL_VERSION)
COMPONENT_ARCHIVE		= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH	= \
	sha256:8ff46d0baa9e64c0815544e829e985f1161c096aa6344c8f430791dbeadc2baf
COMPONENT_ARCHIVE_URL=	http://www.sqlite.org/2013/$(COMPONENT_ARCHIVE)

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION   += $(CLONEY) $(SOURCE_DIR) $(@D);
COMPONENT_PRE_CONFIGURE_ACTION   += $(CP) $(COMPONENT_DIR)/mapfile $(@D)

CFLAGS			+= -D_POSIX_PTHREAD_SEMANTICS
CFLAGS			+= -DNDEBUG
CFLAGS			+= -DSQLITE_SECURE_DELETE 
CFLAGS			+= -DSQLITE_ENABLE_FTS3 
CFLAGS			+= -DUSE_PREAD 
CFLAGS			+= -DHAVE_USLEEP
CFLAGS			+= -DHAVE_FDATASYNC
CFLAGS			+= -DHAVE_STATVFS 
CFLAGS			+= -DSQLITE_ENABLE_UNLOCK_NOTIFY
CFLAGS			+= -DSQLITE_ENABLE_STAT2

#Fixes firefox crash with new sqlite, don't remove until proper fix
gcc_OPT                 =  -O2

CONFIGURE_OPTIONS	+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS	+= --enable-threadsafe 
CONFIGURE_OPTIONS	+= --enable-shared
CONFIGURE_OPTIONS	+= --disable-static

include ../../../make-rules/shared-targets.mk

build:		$(BUILD_32) $(BUILD_64)

install:	$(INSTALL_32) $(INSTALL_64)

test:		$(TEST_32) $(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
