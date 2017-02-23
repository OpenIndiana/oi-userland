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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sqlite
TARBALL_VERSION=	3120200
COMPONENT_VERSION=	3.12.2
COMPONENT_PROJECT_URL=	http://www.sqlite.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-autoconf-$(TARBALL_VERSION)
COMPONENT_ARCHIVE_HASH= \
    sha256:fd00770c9afd39db555c78400e52f55e8bd6568c78be23561abb472a22d09abb
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)2016/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	database/sqlite3
COMPONENT_ANITYA_ID=	4877

# Documentation
DOC_VERSION=		$(TARBALL_VERSION)
COMPONENT_SRC_1=        $(COMPONENT_NAME)-doc-$(DOC_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).zip
COMPONENT_ARCHIVE_HASH_1=       \
    sha256:67c640c4b01b961016717db61e3e43c63c33248c78ce0de9f10b88ea7ce97670
COMPONENT_ARCHIVE_URL_1=         $(COMPONENT_PROJECT_URL)2016/$(COMPONENT_ARCHIVE_1)
PKG_PROTO_DIRS +=       $(COMPONENT_SRC_1)

TPNO=			27892

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

LDFLAGS+= $(CC_BITS)

TEA_CONFIGURE_OPTIONS.32 += --with-tcl="$(USRLIBDIR)"
TEA_CONFIGURE_OPTIONS.64 += --with-tcl="$(USRLIBDIR64)"
TEA_CONFIGURE_OPTIONS.64 += --enable-64bit
TEA_CONFIGURE_OPTIONS.sparc.64 += --enable-64bit-vis
TEA_CONFIGURE_OPTIONS = --enable-shared
TEA_CONFIGURE_OPTIONS += $(TEA_CONFIGURE_OPTIONS.$(BITS))
TEA_CONFIGURE_OPTIONS += $(TEA_CONFIGURE_OPTIONS.$(MACH))
TEA_CONFIGURE_OPTIONS += $(TEA_CONFIGURE_OPTIONS.$(MACH).$(BITS))

COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D)/tea ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
	./configure $(TEA_CONFIGURE_OPTIONS));

COMPONENT_POST_BUILD_ACTION = \
	(cd $(@D)/tea ; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS));

# Enable DSQLITE_ENABLE_FTS3_TOKENIZER to allow thunderbird work. Should disable it if
# thunderbird fixes that. Bugzilla id https://bugzilla.mozilla.org/show_bug.cgi?id=1252937
CFLAGS +=	-D_POSIX_PTHREAD_SEMANTICS
CFLAGS +=	-DNDEBUG
CFLAGS +=	-DSQLITE_SECURE_DELETE
CFLAGS +=	-DSQLITE_ENABLE_FTS3
CFLAGS +=	-DUSE_PREAD
CFLAGS +=	-DHAVE_USLEEP
CFLAGS +=	-DHAVE_FDATASYNC
CFLAGS +=	-DHAVE_STATVFS
CFLAGS += 	-DSQLITE_ENABLE_DBSTAT_VTAB
CFLAGS +=	-DSQLITE_ENABLE_UNLOCK_NOTIFY
CFLAGS +=	-DSQLITE_ENABLE_FTS3_TOKENIZER
CFLAGS +=	-DSQLITE_ENABLE_STAT2
CFLAGS +=	-DSQLITE_MAX_SCHEMA_RETRY=25
CFLAGS +=	-DSQLITE_DEFAULT_PAGE_SIZE=32768
CFLAGS +=	-DSQLITE_MAX_DEFAULT_PAGE_SIZE=32768
CFLAGS +=	-DSQLITE_DEFAULT_PCACHE_INITSZ=0
CFLAGS +=	-I.

CONFIGURE_OPTIONS +=	--enable-threadsafe
CONFIGURE_OPTIONS +=	--enable-dynamic-extensions
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--disable-static

REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/readline
