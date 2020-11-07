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
# Copyright 2016 Predrag Zečević
# Copyright 2018 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= shmux
COMPONENT_VERSION= 1.0.3
COMPONENT_SUMMARY= shmux - Shell Multiplexor
COMPONENT_PROJECT_URL= https://github.com/shmux/shmux
COMPONENT_FMRI= shell/shmux
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_URL= \
	https://github.com/shmux/shmux/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:c9f8863e2550e23e633cf5fc7a9c4c52d287059f424ef78aba6ecd98390fb9ab
COMPONENT_LICENSE= BSD-like

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PATCH_LEVEL=0

COMPONENT_PRE_CONFIGURE_ACTION= \
    $(CLONEY) $(SOURCE_DIR) $(@D)

LDFLAGS+= -lnsl -lsocket 

COMPONENT_TEST_TARGETS= test

COMPONENT_TEST_TRANSFORMS= \
	'-n ' \
	'-e "/^running test/p"'

# Manually added dependencies
REQUIRED_PACKAGES += diagnostic/fping

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
