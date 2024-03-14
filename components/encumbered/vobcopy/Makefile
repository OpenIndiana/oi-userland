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
# Copyright 2016 Apostolos Syropoulos
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         vobcopy
COMPONENT_VERSION=      1.2.1
COMPONENT_SUMMARY=      The VOBcopy DVD tool
COMPONENT_PROJECT_URL=  https://github.com/barak/vobcopy
COMPONENT_FMRI=         media/vobcopy
COMPONENT_CLASSIFICATION=System/Media
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/barak/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:f4737efaf5ad4f84b5c94ca82cda04dbb20c59cebc23588e3662e0c2813d6fde
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

TEST_TARGET=$(NO_TESTS)

COMPONENT_PREP_ACTION = (cd $(@D); autoreconf -fvi)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/video/libdvdread
REQUIRED_PACKAGES += system/library
