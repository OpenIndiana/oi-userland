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

COMPONENT_NAME =		mergiraf
HUMAN_VERSION =			0.15.0
COMPONENT_SUMMARY =		A syntax-aware merge driver for Git
COMPONENT_ARCHIVE_HASH =	\
	sha256:10e17ab4ea1d4f2d5dd49b8f716096c0b56f8406805c660ac4a1aa1b5084aa6e
COMPONENT_FMRI =		developer/mergiraf
COMPONENT_CLASSIFICATION =	Development/Other Languages
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
