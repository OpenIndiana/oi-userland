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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sqlite
TARBALL_VERSION=	3080801
COMPONENT_VERSION=	3.8.8.1
COMPONENT_PROJECT_URL=	http://www.sqlite.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-autoconf-$(TARBALL_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:2721361eb4a71d5f727dfa466bd910dadd5dbeb4d2d57b8b34205f7ce7e5b7f9
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)2015/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	database/sqlite3

# Documentation
DOC_VERSION=		$(TARBALL_VERSION)
COMPONENT_SRC_1=        $(COMPONENT_NAME)-doc-$(DOC_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).zip
COMPONENT_ARCHIVE_HASH_1=       \
    sha256:8bd54fdb0ed5daf4d47ab97838a116b71cc669591ff0bdd7935ab300942ff93f
COMPONENT_ARCHIVE_URL_1=         $(COMPONENT_PROJECT_URL)2015/$(COMPONENT_ARCHIVE_1)
PKG_PROTO_DIRS +=       $(COMPONENT_SRC_1)

TPNO=			20813

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D)/tea ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
	./configure --enable-shared --with-tcl="/usr/lib");

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/tea ; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS));

CC +=		$(CC_BITS)

CFLAGS +=	-D_POSIX_PTHREAD_SEMANTICS
CFLAGS +=	-DNDEBUG
CFLAGS +=	-DSQLITE_SECURE_DELETE
CFLAGS +=	-DSQLITE_ENABLE_FTS3
CFLAGS +=	-DUSE_PREAD
CFLAGS +=	-DHAVE_USLEEP
CFLAGS +=	-DHAVE_FDATASYNC
CFLAGS +=	-DHAVE_STATVFS
CFLAGS +=	-DSQLITE_ENABLE_UNLOCK_NOTIFY
CFLAGS +=	-DSQLITE_ENABLE_STAT2
CFLAGS +=	-DSQLITE_MAX_SCHEMA_RETRY=25
CFLAGS +=	-DSQLITE_DEFAULT_PAGE_SIZE=32768
CFLAGS +=	-DSQLITE_MAX_DEFAULT_PAGE_SIZE=32768
CFLAGS +=	-I.

CONFIGURE_OPTIONS +=	--enable-threadsafe
CONFIGURE_OPTIONS +=	--enable-dynamic-extensions
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static

ASLR_MODE =	$(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

system-test:	$(NO_TESTS)

REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
