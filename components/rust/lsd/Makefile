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
# Copyright 2025 Till Wegmueller
#

BUILD_STYLE = cargo

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lsd
HUMAN_VERSION =			1.1.5
COMPONENT_SUMMARY =		An ls command with a lot of pretty colors and some other stuff.
COMPONENT_ARCHIVE_HASH =	\
	sha256:32ff36fa4ac085aafdb515e70e6a12bf271ea4c8a4a2e51b3978106fa1f5801a
COMPONENT_FMRI =		utilities/lsd
COMPONENT_CLASSIFICATION =	Applications/System Utilities
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
