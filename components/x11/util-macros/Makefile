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

COMPONENT_NAME=         util-macros
COMPONENT_VERSION=      1.20.2
COMPONENT_SUMMARY=      GNU autoconf macros for X.Org software packages
COMPONENT_PROJECT_URL=  https://x.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:9ac269eba24f672d7d7b3574e4be5f333d13f04a7712303b1821b2a51ac82e8e
COMPONENT_ARCHIVE_URL=  https://ftp.x.org/pub/individual/util/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/build/autoconf/xorg-macros
COMPONENT_CLASSIFICATION=Development/X11
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= xorg-macros.license

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && autoreconf -fiv )

# Auto-generated dependencies
