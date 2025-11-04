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

BUILD_STYLE = cargo

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		oi-pkg-checker
HUMAN_VERSION =			3.0.0
COMPONENT_SUMMARY =		Finds problems/errors in packages/components in OpenIndiana
COMPONENT_ARCHIVE_HASH =	\
	sha256:70b9f817820ed426994a48d5858f376abf07ba246c21bbadaa66261f8aeba219
COMPONENT_FMRI =		developer/oi-pkg-checker
COMPONENT_CLASSIFICATION =	Development/System
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.md

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
