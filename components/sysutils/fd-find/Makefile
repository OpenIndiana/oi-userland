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
# Copyright 2025 Neal Sidhwaney
#

BUILD_STYLE = cargo

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		fd-find
COMPONENT_VERSION =     10.5.0
COMPONENT_SUMMARY =		fd is a program to find entries in your filesystem. It is a simple, fast and user-friendly alternative to find. While it does not aim to support all of find's powerful functionality, it provides sensible (opinionated) defaults for a majority of use cases.
COMPONENT_ARCHIVE_HASH =	\
	sha256:f35becce49c551724fd26d9824ec01d6578868cecbcc4e3d060658f9f8ad1e4d
COMPONENT_FMRI =		file/fd-find
COMPONENT_CLASSIFICATION =	Applications/System Utilities
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE-MIT

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
