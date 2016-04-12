#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2016 Jim Klimov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= zeromq

# See configure.ac for ABI version mapping to software version
COMPONENT_VERSION_ABI= 5
COMPONENT_VERSION_MAJ= 4
COMPONENT_VERSION_MIN= 2
COMPONENT_VERSION_PAT= 0
COMPONENT_VERSION_MAJ_MIN= $(COMPONENT_VERSION_MAJ).$(COMPONENT_VERSION_MIN)
COMPONENT_VERSION= $(COMPONENT_VERSION_MAJ_MIN).$(COMPONENT_VERSION_PAT)
# Git snapshot from 2016-04-05:
COMPONENT_GIT_REV= 8251306
# Since we will be taking occasional git snapshots for the same nominal
# project version, we should use COMPONENT_REVISION to update the packages.

COMPONENT_SUMMARY= Open source message queue optimised for performance (bleeding edge)
COMPONENT_SRC= zeromq-libzmq-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:6a35f43c0a6cb2bd9d26e637d5d7c5b2f54d3c132e73bcb4e9da31c46d30cb8a
COMPONENT_ARCHIVE_URL= \
  https://codeload.github.com/zeromq/libzmq/legacy.tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_PROJECT_URL= http://zeromq.org/
# Two licenses in tarball, LGPLv3+ is referenced in their spec-file
COMPONENT_LICENSE_FILE= COPYING.LESSER
COMPONENT_LICENSE= LGPLv3+
COMPONENT_CLASSIFICATION= System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Note: This USR path is used in build prefix and in p5m manifest,
# except where we mediate the links and the relative SUB path is used
COMPONENT_SUB_DIR=zeromq-$(COMPONENT_VERSION_MAJ_MIN)
COMPONENT_USR_DIR=$(USRDIR)/$(COMPONENT_SUB_DIR)

PKG_OPTIONS +=	-D COMPONENT_VERSION_ABI="$(COMPONENT_VERSION_ABI)"
PKG_OPTIONS +=	-D COMPONENT_VERSION_MAJ_MIN="$(COMPONENT_VERSION_MAJ_MIN)"
PKG_OPTIONS +=	-D COMPONENT_SUB_DIR="$(COMPONENT_SUB_DIR)"
PKG_OPTIONS +=	-D COMPONENT_USR_DIR="$(COMPONENT_USR_DIR)"

COMPONENT_PREP_ACTION =	\
	( cd $(@D) && \
	  libtoolize --copy --force && \
	  aclocal -I m4 && \
	  autoheader && \
	  automake -c -f -a && \
	  autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

# Build docs just once (for one ARCH), parameter varies from version to version
CONFIGURE_OPTIONS.32 +=	--with-documentation --with-docs
CONFIGURE_OPTIONS.64 +=	--without-documentation --without-docs

CONFIGURE_OPTIONS +=	--enable-static=no
CONFIGURE_OPTIONS +=	--with-libsodium

CONFIGURE_PREFIX   =	$(COMPONENT_USR_DIR)

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
