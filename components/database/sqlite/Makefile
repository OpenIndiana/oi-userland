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
# Copyright (c) 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		sqlite
COMPONENT_VERSION=	3.29.0
TARBALL_VERSION=	3290000
COMPONENT_SRC=		sqlite-src-$(TARBALL_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH	= \
	sha256:a1533d97504e969ca766da8ff393e71edd70798564813fc2620b0708944c8817
COMPONENT_PROJECT_URL=	https://www.sqlite.org
COMPONENT_ARCHIVE_URL=	https://www.sqlite.org/2019/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		database/sqlite-3
COMPONENT_LICENSE=	PublicDomain

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION	+= $(CP) $(COMPONENT_DIR)/files/mapfile $(@D) ;

# 'oserror' test has too low threshold for file descriptor depletion. When it's
# bumped 32-bit is fine, however on 64-bit the whole test suite crashes.
COMPONENT_PRE_CONFIGURE_ACTION	+= $(RM) $(SOURCE_DIR)/test/oserror.test ;

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

# Fixes firefox crash with new sqlite, don't remove until proper fix
gcc_OPT                 =  -O2

CONFIGURE_OPTIONS.32	+= --with-tcl="$(USRLIBDIR)"
CONFIGURE_OPTIONS.64	+= --with-tcl="$(USRLIBDIR64)"
CONFIGURE_OPTIONS	+= $(CONFIGURE_OPTIONS.$(BITS))
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

# Install sqlite3(1) man page
COMPONENT_POST_INSTALL_ACTION += $(MKDIR) $(PROTO_DIR)$(USRSHAREMAN1DIR) ; $(CP) $(SOURCE_DIR)/sqlite3.1 $(PROTO_DIR)$(USRSHAREMAN1DIR)/

COMPONENT_TEST_TARGETS = test

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += library/libedit
# Auto-generated dependencies
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
