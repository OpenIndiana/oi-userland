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

COMPONENT_NAME=		util-macros
COMPONENT_VERSION=	1.19.0
COMPONENT_FMRI=		developer/build/autoconf/xorg-macros
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=	GNU autoconf macros for X.Org software packages
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:0d4df51b29023daf2f63aebf3ebc638ea88efedfd560ab5866741ab3f92acaa1
COMPONENT_ARCHIVE_URL= \
  http://ftp.x.org/pub/individual/util/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://x.org
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xorg-macros.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && autoreconf -f )

build: $(BUILD_32)

install: $(INSTALL_32)
