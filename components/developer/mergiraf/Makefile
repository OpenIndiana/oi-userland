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
HUMAN_VERSION =			0.16.1
COMPONENT_SUMMARY =		A syntax-aware merge driver for Git
COMPONENT_ARCHIVE_HASH =	\
	sha256:0f7e6c0025fb5a164b7f747deae7b9304d504f47d1513eb41322f35f2e612610
COMPONENT_FMRI =		developer/mergiraf
COMPONENT_CLASSIFICATION =	Development/Other Languages
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e '/^error: Could not stat \/tmp\/\.tmp.\{6\}\/does_not_exist_2\.json: No such file or directory\$$/d'"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
