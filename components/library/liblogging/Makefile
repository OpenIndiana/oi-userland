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
COMPONENT_VERSION=      1.0.7
COMPONENT_SUMMARY=      An easy to use logging library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f0f6e82c57a47f71ccdf9673af9f317c37357c9113b865d9ef4e89c2238a3a44
COMPONENT_ARCHIVE_URL=  https://github.com/rsyslog/liblogging/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=  https://www.rsyslog.com/liblogging
COMPONENT_FMRI=         library/liblogging
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += ( cd $(@D); NOCONFIGURE=1 ./autogen.sh );

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) );

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-journal=no

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/docutils

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
