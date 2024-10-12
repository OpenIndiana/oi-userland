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

# This is pangomm-2.48 ABI series

COMPONENT_NAME=			pangomm
HUMAN_VERSION=			2.54.0
COMPONENT_SUMMARY=		C++ API for Pango
COMPONENT_ARCHIVE_HASH=		sha256:4a5b1fd1b7c47a1af45277ea82b5abeaca8e08fb10a27daa6394cf88d74e7acf
COMPONENT_FMRI=			library/desktop/c++/pangomm-248
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/glibmm-268
REQUIRED_PACKAGES += library/c++/sigcpp3
REQUIRED_PACKAGES += library/desktop/c++/cairomm-116
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
