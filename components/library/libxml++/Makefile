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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libxml++
HUMAN_VERSION=			5.4.0
COMPONENT_SUMMARY= C++ interface to libxml2 and XML files
COMPONENT_PROJECT_URL= https://github.com/libxmlplusplus/libxmlplusplus
COMPONENT_ARCHIVE_HASH=		sha256:e9a23c436686a94698d2138e6bcbaf849121d63bfa0f50dc34fefbfd79566848
COMPONENT_FMRI= library/c++/libxml++
COMPONENT_CLASSIFICATION= Development/C++
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Manually added build dependency
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += library/desktop/c++/mm-common
REQUIRED_PACKAGES += library/libxslt

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
