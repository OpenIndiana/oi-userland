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
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= sudosh2
COMPONENT_VERSION= 1.0.5
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= sudosh - an auditing layer between sudo and a user shell, that can also be used as a login shell
COMPONENT_PROJECT_URL= https://github.com/squash/sudosh2
COMPONENT_FMRI= shell/sudosh2
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:c6ab7d4b736e19b409e66216d7760f3f64ecac849e034f03db567097cb8eb8ef
COMPONENT_LICENSE= Open Source License 2.0

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION= ( cd $(@D); autoreconf -i -f )

build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += security/sudo
