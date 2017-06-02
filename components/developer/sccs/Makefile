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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= sccs
COMPONENT_VERSION= 5.08
IPS_COMPONENT_VERSION=5.0.8
COMPONENT_FMRI= developer/versioning/sccs
COMPONENT_SUMMARY= The POSIX standard Source Code Control System
COMPONENT_CLASSIFICATION= Development/Source Code Management
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_PROJECT_URL= https://sccs.sourceforge.net/
COMPONENT_ARCHIVE_HASH= \
  sha256:5ea2898f25272e81f7725d9cd0c6c416bc9b1b3a765acb08855feaef8295692a
COMPONENT_ARCHIVE_URL= \
  https://sourceforge.net/projects/sccs/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE= GPL,CDDL

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.illumos)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
