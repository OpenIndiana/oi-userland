#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Alexander Pyhalov
#

BUILD_BITS=32
BUILD_STYLE=gem

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mixlib-config
COMPONENT_VERSION=	2.2.18
COMPONENT_SUMMARY=	A class-based configuration object
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e457a532ce080f784d0bfbd9be752a46e5821477c62fb7740472ceec583022c3
COMPONENT_ARCHIVE_URL=	https://github.com/chef/mixlib-config/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=  https://github.com/chef/mixlib-config
COMPONENT_FMRI=		library/ruby/mixlib-config
COMPONENT_CLASSIFICATION=	Development/Ruby
COMPONENT_LICENSE=	Apache 2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += runtime/ruby-23
