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
# Copyright 2025 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../../make-rules/shared-macros.mk

# This is libpeas-2 ABI series

COMPONENT_NAME=			libpeas
HUMAN_VERSION=			2.0.5
COMPONENT_SUMMARY=		A GObject-based plugins engine
COMPONENT_ARCHIVE_HASH=		sha256:376f2f73d731b54e13ddbab1d91b6382cf6a980524def44df62add15489de6dd
COMPONENT_FMRI=			library/desktop/libpeas-2
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# We have no gjs-1.0 packaged yet
CONFIGURE_OPTIONS += -Dgjs=false
# We have no Lua 5.1
CONFIGURE_OPTIONS += -Dlua51=false

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
