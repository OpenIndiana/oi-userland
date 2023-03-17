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
# Copyright (c) 2020 Michal Nowak
#

BUILD_BITS= 64_and_32
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         sqlite
COMPONENT_VERSION=      3.41.1
COMPONENT_REVISION=	1
TARBALL_VERSION=		3410100
COMPONENT_SUMMARY=		in-process SQL database engine library
COMPONENT_SRC=          sqlite-src-$(TARBALL_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= sha256:db929012f9009e7f07960e7f017e832d8789a29f4b203071b4fd79229e7d7a20
COMPONENT_PROJECT_URL=  https://www.sqlite.org
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/2023/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         database/sqlite-3
COMPONENT_CLASSIFICATION=	Development/Databases
COMPONENT_LICENSE=      Public Domain

include $(WS_MAKE_RULES)/common.mk

# 'oserror' test has too low threshold for file descriptor depletion. When it's
# bumped 32-bit is fine, however on 64-bit the whole test suite crashes.
COMPONENT_PRE_CONFIGURE_ACTION += $(RM) $(SOURCE_DIR)/test/oserror.test ;

CFLAGS			+= -D_POSIX_PTHREAD_SEMANTICS
CFLAGS			+= -DNDEBUG
CFLAGS			+= -DSQLITE_SECURE_DELETE 
CFLAGS			+= -DSQLITE_ENABLE_DBSTAT_VTAB
CFLAGS			+= -DSQLITE_ENABLE_FTS3 
CFLAGS			+= -DSQLITE_ENABLE_FTS4 
CFLAGS			+= -DSQLITE_ENABLE_FTS5 
CFLAGS			+= -DSQLITE_ENABLE_JSON1
CFLAGS			+= -DSQLITE_ENABLE_RTREE
CFLAGS			+= -DSQLITE_ENABLE_UPDATE_DELETE_LIMIT
CFLAGS			+= -DUSE_PREAD 
CFLAGS			+= -DHAVE_USLEEP
CFLAGS			+= -DHAVE_FDATASYNC
CFLAGS			+= -DHAVE_STATVFS 
CFLAGS			+= -DSQLITE_ENABLE_UNLOCK_NOTIFY
CFLAGS			+= -DSQLITE_ENABLE_STAT2
CFLAGS			+= -DSQLITE_ENABLE_STMT_SCANSTATUS
CFLAGS			+= -DSQLITE_ENABLE_COLUMN_METADATA

CONFIGURE_OPTIONS.32	+= --disable-tcl
CONFIGURE_OPTIONS.64	+= --with-tcl="$(USRLIBDIR64)"
CONFIGURE_OPTIONS	+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS	+= --disable-static
CONFIGURE_OPTIONS	+= --enable-readline
CONFIGURE_OPTIONS	+= --enable-fts3
CONFIGURE_OPTIONS	+= --enable-fts4
CONFIGURE_OPTIONS	+= --enable-fts5
CONFIGURE_OPTIONS	+= --enable-json1
CONFIGURE_OPTIONS	+= --enable-update-limit
CONFIGURE_OPTIONS	+= --enable-rtree
CONFIGURE_OPTIONS	+= --enable-threadsafe 
CONFIGURE_OPTIONS	+= --enable-shared

CONFIGURE_ENV.64 += TCLLIBDIR=$(USRLIBDIR)/tcl8.6/sqlite3/$(MACH64)

# Build and install should be able to find some basic tools like cp, cat, rm, or mkdir.
COMPONENT_BUILD_ENV += PATH=$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(PATH)

# Install sqlite3(1) man page
COMPONENT_POST_INSTALL_ACTION += $(MKDIR) $(PROTO_DIR)$(USRSHAREMAN1DIR) ; $(CP) $(SOURCE_DIR)/sqlite3.1 $(PROTO_DIR)$(USRSHAREMAN1DIR)/

COMPONENT_TEST_TARGETS = test
# remove clutter and timings from test results:
COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "s/[0-9]* ms//" ' \
	' -e "s/ in [0-9]*\.[0-9]* seconds//" ' \
	' -e "s/[0-9]* microseconds per iteration//" ' \
	' -e "/^fuzzcheck/p" ' \
	' -e "/^sessionfuzz/p" ' \
	' -e "/^Time/p" ' \
	' -e "/^Query/p" ' \
	' -e "/No /p" ' 

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
