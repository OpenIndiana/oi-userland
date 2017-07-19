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

COMPONENT_NAME			= tcl-sqlite
COMPONENT_VERSION		= 3.19.3
TARBALL_VERSION			= 3190300
COMPONENT_SUMMARY		= SQL database engine library - tcl files
COMPONENT_SRC			= sqlite-autoconf-$(TARBALL_VERSION)
COMPONENT_ARCHIVE		= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH	= \
	sha256:06129c03dced9f87733a8cba408871bd60673b8f93b920ba8d815efab0a06301
COMPONENT_ARCHIVE_URL=	http://www.sqlite.org/2016/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.sqlite.org/
COMPONENT_FMRI=	runtime/tcl-8/tcl-sqlite-3
COMPONENT_CLASSIFICATION=	Development/Databases
COMPONENT_LICENSE=	Public Domain

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

CONFIGURE_SCRIPT=       $(SOURCE_DIR)/tea/configure

CONFIGURE_OPTIONS	+= --enable-shared
CONFIGURE_OPTIONS.32	+= --with-tcl="/usr/lib"
CONFIGURE_OPTIONS.64	+= --with-tcl="/usr/lib/$(MACH64)"
CONFIGURE_OPTIONS.64	+= LIBS="-m64"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
