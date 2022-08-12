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
COMPONENT_VERSION= 5.0.1
BRANCH_VERSION = 2022.0.0.0
COMPONENT_REVISION =	1
COMPONENT_FMRI= system/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/File System
COMPONENT_PROJECT_URL= https://github.com/cgrzemba/$(COMPONENT_NAME)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(BRANCH_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_VERSION)-$(BRANCH_VERSION).tar.gz 
COMPONENT_ARCHIVE_HASH= \
	sha256:daf8ba6e0b0650115ee5f633d5ead3004ed6d0711af17ee6e3976946fae4fdd7
COMPONENT_LICENSE= CDDL
COMPONENT_LICENSE_FILE= opt/SUNWsamfs/doc/OPENSOLARIS.LICENSE
COMPONENT_SUMMARY= Storage and Archive Manager File System

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS = DEBUG=no MYSQL_VERSION=mariadb/10.3 SAMQFS_VERSION=$(COMPONENT_VERSION)-$(BRANCH_VERSION)

COMPONENT_INSTALL_ARGS = install DEBUG=no DESTDIR=$(PROTO_DIR) SAMQFS_VERSION=$(COMPONENT_VERSION)-$(BRANCH_VERSION)

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
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/mariadb-103/library
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
