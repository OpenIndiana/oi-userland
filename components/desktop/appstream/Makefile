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

COMPONENT_NAME=			AppStream
COMPONENT_VERSION=		1.0.3
COMPONENT_SUMMARY=		Cross-distribution effort for enhancing the way we interact with the software repositories provided by distributions by standardizing software component metadata
COMPONENT_PROJECT_URL=		https://www.freedesktop.org/wiki/Distributions/AppStream/
COMPONENT_FMRI=			desktop/appstream
COMPONENT_CLASSIFICATION=	System/Packaging
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=		https://www.freedesktop.org/software/appstream/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:5ab6f6cf644e7875a9508593962e56bb430f4e59ae0bf03be6be7029deb6baa4
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/common.mk

# GNU gettext is expected in PATH
PATH = $(PATH.gnu)

# We have no libsystemd (obviously)
CONFIGURE_OPTIONS += -Dsystemd=false
# We have no libstemmer packaged
CONFIGURE_OPTIONS += -Dstemming=false

# Testing expects there is no Inkscape installed
TEST_CONFLICTING_PACKAGES += image/editor/inkscape

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxmlb
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
