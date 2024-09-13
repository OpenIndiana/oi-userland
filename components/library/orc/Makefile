#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2012 EveryCity Ltd. All rights reserved.
#

BUILD_STYLE = meson
BUILD_BITS = 64_and_32
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         orc
COMPONENT_VERSION=	0.4.40
COMPONENT_FMRI=		library/orc
COMPONENT_PROJECT_URL=	https://gstreamer.freedesktop.org/projects/orc.html
COMPONENT_SUMMARY=	The Optimized Inner Loop Runtime Compiler for SIMD array operations
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:3fc2bee78dfb7c41fd9605061fc69138db7df007eae2f669a1f56e8bacef74ab
COMPONENT_ARCHIVE_URL=  \
	http://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-2-Clause AND BSD-3-Clause
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Heals libgstvideoscale (from gstreamer 0.10) core dump
gcc_OPT = -O2

# Dynamic library version number
SOVER = 0.$(word 3,$(subst ., ,$(COMPONENT_VERSION))).0
SOVER_RE = $(subst .,\.,$(SOVER))

# Replace library version number by SOVER
GENERATE_EXTRA_CMD += | $(GSED) -e 's/$(SOVER_RE)/$$(SOVER)/'

# SOVER is needed for manifest processing
PKG_MACROS += SOVER=$(SOVER)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
