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
COMPONENT_VERSION_MIN=	40
COMPONENT_VERSION_PAT=	0
COMPONENT_VERSION=      $(COMPONENT_VERSION_SUP).$(COMPONENT_VERSION_MAJ).$(COMPONENT_VERSION_MIN)
# The XY in "libpngXY" file and directory names
COMPONENT_VERSION_TAG=$(COMPONENT_VERSION_SUP)$(COMPONENT_VERSION_MAJ)
# Suffix of shared libs:
COMPONENT_VERSION_SONAME=$(COMPONENT_VERSION_TAG).$(COMPONENT_VERSION_MIN).$(COMPONENT_VERSION_PAT)
COMPONENT_PROJECT_URL=  http://www.libpng.org/pub/png/
COMPONENT_SUMMARY=      Portable Network Graphics library version $(COMPONENT_VERSION)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:535b479b2467ff231a3ec6d92a525906fb8ef27978be4f66dbe05d3f3a01b3a1
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/libpng/files/libpng16/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=         image/library/libpng16
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=      zlib
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

PKG_OPTIONS += -D COMPONENT_VERSION_SONAME="$(COMPONENT_VERSION_SONAME)"
PKG_OPTIONS += -D COMPONENT_VERSION_TAG="$(COMPONENT_VERSION_TAG)"

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# for tests to pass
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
