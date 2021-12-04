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
# Copyright 2021 Andreas Wacknitz
#
include ../../../make-rules/shared-macros.mk

# Beside the p5m file, there is really nothing to this component which just
# delivers a user and group actions as a common ground for database servers of mysql heritage.
COMPONENT_NAME=				mysql-common
COMPONENT_VERSION=			1.0
COMPONENT_SUMMARY=			MySQL Database Management System (Base)
COMPONENT_FMRI=				database/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Databases
COMPONENT_LICENSE=			CDDL
COMPONENT_LICENSE_FILE=		cddl.license

include $(WS_MAKE_RULES)/prep-download.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

download::

$(BUILD_DIR)/.prep: Makefile mysql-common.p5m
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
