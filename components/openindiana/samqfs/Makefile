# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Carsten Grzemba
#

BUILD_STYLE = justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= samqfs
COMPONENT_VERSION= 5.64.5
BRANCH_VERSION = 
COMPONENT_REVISION =	0
COMPONENT_FMRI= system/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/File System
COMPONENT_PROJECT_URL= https://github.com/cgrzemba/$(COMPONENT_NAME)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)$(BRANCH_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_VERSION)$(BRANCH_VERSION).tar.gz 
COMPONENT_ARCHIVE_HASH= \
	sha256:cd9f26f11e9581a0e9e889e7b25335d5e9b0d4326ecaa3df625d1cd33b3e8e3d
COMPONENT_LICENSE= CDDL
COMPONENT_LICENSE_FILE= opt/SUNWsamfs/doc/OPENSOLARIS.LICENSE
COMPONENT_SUMMARY= Storage and Archive Manager File System

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS = AMD64=yes DEBUG=no MYSQL_VERSION=$(MYSQL_IMPLEM)/$(MYSQL_VERSION) SAMQFS_VERSION=$(COMPONENT_VERSION)$(BRANCH_VERSION) NO_BUILD_ACSLS=-D_NoACSLS_

COMPONENT_INSTALL_ARGS = install AMD64=yes DEBUG=no DESTDIR=$(PROTO_DIR) SAMQFS_VERSION=$(COMPONENT_VERSION)$(BRANCH_VERSION)

PKG_HARDLINKS += opt/SUNWsamfs/bin/archive
PKG_HARDLINKS += opt/SUNWsamfs/bin/request
PKG_HARDLINKS += opt/SUNWsamfs/bin/sdu
PKG_HARDLINKS += opt/SUNWsamfs/bin/sfind
PKG_HARDLINKS += opt/SUNWsamfs/bin/sls
PKG_HARDLINKS += opt/SUNWsamfs/lib/libsam.so
PKG_HARDLINKS += opt/SUNWsamfs/lib/libsamcat.so
PKG_HARDLINKS += opt/SUNWsamfs/lib/libsamrft.so
PKG_HARDLINKS += opt/SUNWsamfs/lib/libsamut.so
PKG_HARDLINKS += opt/SUNWsamfs/sbin/samquota
PKG_HARDLINKS += opt/SUNWsamfs/sbin/samu
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/archive.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/release.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/request.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/sdu.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/segment.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/setfa.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/sfind.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/sls.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/squota.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/ssum.1
PKG_HARDLINKS += opt/SUNWsamfs/man/man1/stage.1

# Build dependencies
REQUIRED_PACKAGES += library/python/jinja2

# Auto-generated dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
