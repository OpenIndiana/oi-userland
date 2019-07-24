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
# Copyright 2017 <contributor name>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=
COMPONENT_VERSION=
COMPONENT_SUMMARY=
COMPONENT_PROJECT_URL=
COMPONENT_FMRI=
COMPONENT_CLASSIFICATION=
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=
COMPONENT_ARCHIVE_HASH=
COMPONENT_LICENSE=

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/gem.mk
include $(WS_MAKE_RULES)/ips.mk


build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(NO_TESTS)
