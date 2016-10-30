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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= shmux
COMPONENT_VERSION= 1.0.2
COMPONENT_SUMMARY= shmux - Shell Multiplexor
COMPONENT_PROJECT_URL= http://web.taranis.org/shmux/
COMPONENT_FMRI= shell/shmux
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_URL= \
    http://web.taranis.org/shmux/dist/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
    sha256:0886aaca4936926d526988d85df403fa1679a60c355f1be8432bb4bc1e36580f
COMPONENT_LICENSE= BSD-like

PATH=/usr/gnu/bin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

COMPONENT_PRE_CONFIGURE_ACTION= \
    $(CLONEY) $(SOURCE_DIR) $(@D)

LDFLAGS+= -lnsl -lsocket

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += diagnostic/fping
