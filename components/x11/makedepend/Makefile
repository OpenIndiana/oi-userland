#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Aurelien Larcher
#
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           makedepend
COMPONENT_VERSION=        1.0.9
COMPONENT_SUMMARY=        makedepend - makefile dependency generation utility
COMPONENT_PROJECT_URL=    $(XORG_PROJECT_URL)
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=    $(XORG_UTIL_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=   sha256:92d0deb659fff6d8ddbc1d27fc4ca8ceb2b6dbe15d73f0a04edc09f1c5782dd4
COMPONENT_FMRI=           developer/build/makedepend
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_LICENSE=        MIT License
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
