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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME			= tcl-sqlite
COMPONENT_VERSION		= 3.30.1
COMPONENT_REVISIOn		= 1
TARBALL_VERSION			= 3300100
COMPONENT_SUMMARY		= SQL database engine library - tcl files
COMPONENT_SRC			= sqlite-autoconf-$(TARBALL_VERSION)
COMPONENT_ARCHIVE		= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH	= \
	sha256:8c5a50db089bd2a1b08dbc5b00d2027602ca7ff238ba7658fabca454d4298e60
COMPONENT_ARCHIVE_URL		= http://www.sqlite.org/2019/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL		= http://www.sqlite.org/
COMPONENT_FMRI			= runtime/tcl-8/tcl-sqlite-3
COMPONENT_CLASSIFICATION	= Development/Databases
COMPONENT_LICENSE		= Public Domain

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

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
CONFIGURE_OPTIONS	+= --enable-threads
CONFIGURE_OPTIONS	+= --enable-64bit
CONFIGURE_OPTIONS	+= --with-tcl="$(COMPONENT_DIR)/../tcl/build/$(MACH$(BITS))"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
