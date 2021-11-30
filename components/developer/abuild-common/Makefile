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
# Copyright 2021 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

# Beside the p5m file, there is really nothing to this component which just
# delivers a user and group actions as a common ground for automated builders
COMPONENT_NAME=				abuild-common
COMPONENT_VERSION=			1.0
COMPONENT_FMRI=				developer/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=			CDDL
COMPONENT_LICENSE_FILE=		opensolaris.license
COMPONENT_SUMMARY=			Standard accound for Automated Builds systems

include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

download::

$(BUILD_DIR)/.prep: Makefile abuild-common.p5m
	$(MKDIR) -p "$(@D)"
	$(TOUCH) $@

prep::  $(BUILD_DIR)/.prep

clean::
	$(RM) -r $(BUILD_DIR)

clobber:: clean

build:: $(BUILD_DIR)/.prep

install: $(BUILD_DIR)/.prep

test: $(NO_TESTS)

# Auto-generated dependencies
