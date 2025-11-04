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
# Copyright 2025 Jiwon Na
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           ibus-table-others
COMPONENT_VERSION=        1.3.21
COMPONENT_SUMMARY=        ibus-table-others
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:ff764340273fbb61ca94bd3e919d20e066e3ae493efa5de54ab590cfb0afc1a4
COMPONENT_ARCHIVE_URL=    https://github.com/moebiuscurve/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/ibus/table/others
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        GPLv3
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/moebiuscurve/ibus-table-others

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/input-method/ibus/table

# Auto-generated dependencies
