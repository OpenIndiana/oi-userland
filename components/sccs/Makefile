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
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= sccs
COMPONENT_VERSION= 5.07
IPS_COMPONENT_VERSION=5.0.7
COMPONENT_SUMMARY= The POSIX standard Source Code Control System
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH = sha256:e0d04d99ff9158870437b018e4205da2778d716034b70468b0fecc67c597de19
COMPONENT_PROJECT_URL = http://sccs.sourceforge.net/
COMPONENT_ARCHIVE_URL= http://sourceforge.net/projects/sccs/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION= Development/Source Code Management
COMPONENT_LICENSE_FILE= sccs.license
COMPONENT_LICENSE= GPL,CDDL
COMPONENT_FMRI= developer/versioning/sccs

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

PATH=$(GCC_ROOT)/bin:/usr/bin:/usr/gnu/bin

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
