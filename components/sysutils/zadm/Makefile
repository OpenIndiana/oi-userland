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
# Copyright 2025 Marcel Telka
#

BUILD_BITS = NO_ARCH

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			zadm
COMPONENT_VERSION=		0.15.0
COMPONENT_SUMMARY=		zadm - zone management tool
COMPONENT_PROJECT_URL=		https://github.com/omniosorg/zadm
COMPONENT_FMRI=			system/zones/zadm
COMPONENT_CLASSIFICATION=	System/Virtualization
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/omniosorg/zadm/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:9619fd4a7d6cbc1d921e5955fb98e89403d86450bd8663c803493bb2027f55e2
COMPONENT_LICENSE=		GPL-3.0-only
COMPONENT_LICENSE_FILE=		LICENSE

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

# This component does not support VPATH build.
# It does not build even with symlinks.
CLONEY_MODE = copy

# Force SUBDIRS="etc lib" to skip the thirdparty subdir.  We do not need
# thirdparty perl modules because we use system provided library/perl-5/*
# packages to satisfy our dependencies.
COMPONENT_BUILD_ARGS += SUBDIRS="etc lib"
COMPONENT_INSTALL_ARGS += SUBDIRS="etc lib"
COMPONENT_TEST_ARGS += SUBDIRS="etc lib"

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
