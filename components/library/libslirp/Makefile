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
# Copyright (c) 2016-2020 Aurelien Larcher
#
BUILD_STYLE=meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libslirp
COMPONENT_VERSION=      4.9.1
COMPONENT_SUMMARY=      A general purpose TCP-IP emulator used by virtual machine hypervisors to provide virtual networking services.
COMPONENT_PROJECT_URL=  https://gitlab.freedesktop.org/slirp
COMPONENT_FMRI=         library/network/libslirp
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:3caff6e2de445f4995629d4929c55419f661b2b1d14f12481e155a71c1e8f811
COMPONENT_ARCHIVE_URL=  https://gitlab.freedesktop.org/slirp/libslirp/-/archive//v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD MIT
COMPONENT_LICENSE_FILE=    COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket

# get rid of the timestamps from the test results
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*[0-9].[0-9][0-9]s//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
