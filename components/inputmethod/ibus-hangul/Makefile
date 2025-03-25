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

COMPONENT_NAME=           ibus-hangul
COMPONENT_VERSION=        1.5.5
COMPONENT_SUMMARY=        libhangul - The hangul engine for IBus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=   sha256:a5aac88286cd18960229860e3e1a778978a7aeaa484ad9acfa48284b87fdc3bb
COMPONENT_ARCHIVE_URL=    https://github.com/libhangul/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           system/input-method/library/ibus/hangul
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        GPL v2
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/libhangul/ibus-hangul

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/input-method/library/libhangul
REQUIRED_PACKAGES += system/library
