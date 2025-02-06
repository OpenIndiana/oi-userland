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

# This is glibmm-2.68 ABI series

COMPONENT_NAME=			glibmm
HUMAN_VERSION=			2.82.0
COMPONENT_SUMMARY=		C++ API for parts of glib that are useful for C++
COMPONENT_ARCHIVE_HASH=		sha256:38684cff317273615c67b8fa9806f16299d51e5506d9b909bae15b589fa99cb6
COMPONENT_FMRI=			library/c++/glibmm-268
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
