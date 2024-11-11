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

COMPONENT_NAME =		cbindgen
HUMAN_VERSION =			0.27.0
COMPONENT_SUMMARY =		A tool for generating C bindings to Rust code.
COMPONENT_ARCHIVE_HASH =	\
	sha256:3fce8dd7fcfcbf3a0a87d8f515194b49d6135acab73e18bd380d1d93bb1a15eb
COMPONENT_FMRI =		developer/rust/cbindgen
COMPONENT_CLASSIFICATION =	Development/Other Languages
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
