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

COMPONENT_NAME=           ibus-table
COMPONENT_VERSION=        1.17.16
COMPONENT_SUMMARY=        ibus-table - The tables engines for IBus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:c1040d4928308b85b3576a418c5cbd6622f199208f80d4a153d1b829ee8508b8
COMPONENT_ARCHIVE_URL=    https://github.com/mike-fabian/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/ibus/table
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        LGPLv2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/mike-fabian/ibus-table

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
