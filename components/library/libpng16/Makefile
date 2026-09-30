#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Jim Klimov
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libpng
COMPONENT_VERSION_SUP=	1
COMPONENT_VERSION_MAJ=	6
COMPONENT_VERSION_MIN=	59
COMPONENT_VERSION_PAT=	0
COMPONENT_VERSION=      $(COMPONENT_VERSION_SUP).$(COMPONENT_VERSION_MAJ).$(COMPONENT_VERSION_MIN)
# The XY in "libpngXY" file and directory names
COMPONENT_VERSION_TAG=$(COMPONENT_VERSION_SUP)$(COMPONENT_VERSION_MAJ)
# Suffix of shared libs:
COMPONENT_VERSION_SONAME=$(COMPONENT_VERSION_TAG).$(COMPONENT_VERSION_MIN).$(COMPONENT_VERSION_PAT)
COMPONENT_PROJECT_URL=  http://www.libpng.org/pub/png/
COMPONENT_SUMMARY=      Portable Network Graphics library version $(COMPONENT_VERSION)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2540302a1844ad2b2b501977abecfa850f265f97b78f065a712ab4074a89f5b5
COMPONENT_ARCHIVE_URL=  https://github.com/pnggroup/libpng/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         image/library/libpng16
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=      zlib
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

PKG_OPTIONS += -D COMPONENT_VERSION_SONAME="$(COMPONENT_VERSION_SONAME)"
PKG_OPTIONS += -D COMPONENT_VERSION_TAG="$(COMPONENT_VERSION_TAG)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
