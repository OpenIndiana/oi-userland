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

COMPONENT_NAME=		mixlib-cli
COMPONENT_VERSION=	1.7.7
COMPONENT_SUMMARY=	A class-based command line option parsing object
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4c46e2bba37b6afb86475455da6f458d99ff43cb84dfcb84634f8ffb92233538
COMPONENT_ARCHIVE_URL=	https://github.com/chef/mixlib-cli/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=  https://github.com/chef/mixlib-cli
COMPONENT_FMRI=		library/ruby/mixlib-cli
COMPONENT_CLASSIFICATION=	Development/Ruby
COMPONENT_LICENSE=	Apache 2.0
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += runtime/ruby-23
