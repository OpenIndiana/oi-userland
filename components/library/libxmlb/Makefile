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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			libxmlb
COMPONENT_VERSION=		0.3.22
COMPONENT_SUMMARY=		A library to help create and query binary XML blobs
COMPONENT_PROJECT_URL=		https://github.com/hughsie/libxmlb
COMPONENT_FMRI=			library/libxmlb
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=		https://github.com/hughsie/libxmlb/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:f3c46e85588145a1a86731c77824ec343444265a457647189a43b71941b20fa0
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing expects GNU diff
PATH = $(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
