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
# Copyright 2013-2017, Aurelien Larcher. All rights reserved.
# 

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         bash-completion
COMPONENT_VERSION=      2.5
COMPONENT_FMRI=         utility/$(COMPONENT_NAME)
COMPONENT_SUMMARY=      Programmable completion functions for bash
COMPONENT_CLASSIFICATION=System/Shells
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://github.com/scop/bash-completion
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:b0b9540c65532825eca030f1241731383f89b2b65e80f3492c5dd2f0438c95cf
COMPONENT_ARCHIVE_URL= \
  https://github.com/scop/bash-completion/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
# NONE
