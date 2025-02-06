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

include ../../../make-rules/shared-macros.mk

# This is atkmm-2.36 ABI series

COMPONENT_NAME=			atkmm
HUMAN_VERSION=			2.36.3
COMPONENT_SUMMARY=		C++ binding for the ATK library
COMPONENT_ARCHIVE_HASH=		sha256:6ec264eaa0c4de0adb7202c600170bde9a7fbe4d466bfbe940eaf7faaa6c5974
COMPONENT_FMRI=			library/desktop/c++/atkmm-236
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
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
