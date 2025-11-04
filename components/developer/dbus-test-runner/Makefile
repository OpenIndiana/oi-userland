#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dbus-test-runner
HUMAN_VERSION=          19.04.0
COMPONENT_VERSION=	$(shell echo $(HUMAN_VERSION) | $(GSED) -e 's/\.0*\([0-9]\)/.\1/g')
COMPONENT_SUMMARY=      A small little utility to run a couple of executables under a new DBus session for testing
COMPONENT_PROJECT_URL=  https://launchpad.net/dbus-test-runner
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:645a32fbd909baf2c01438f0cbda29dc9cd01a7aba5504c45610d88e8a57cb76
COMPONENT_ARCHIVE_URL=  https://launchpad.net/$(COMPONENT_NAME)/19.04/$(HUMAN_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/dbus-test-runner
COMPONENT_CLASSIFICATION=       Development/Distribution Tools
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# GNU xgettext is needed
PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --enable-static=no

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
