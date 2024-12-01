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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         liblogging
COMPONENT_VERSION=      1.0.6
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=      An easy to use logging library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:338c6174e5c8652eaa34f956be3451f7491a4416ab489aef63151f802b00bf93
COMPONENT_ARCHIVE_URL=  https://download.rsyslog.com/liblogging/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.rsyslog.com/liblogging
COMPONENT_FMRI=         library/liblogging
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-journal=no

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
