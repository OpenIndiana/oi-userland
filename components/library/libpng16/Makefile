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

BUILD_STYLE= configure
BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libpng
COMPONENT_VERSION_SUP=	1
COMPONENT_VERSION_MAJ=	6
COMPONENT_VERSION_MIN=	38
COMPONENT_VERSION_PAT=	0
COMPONENT_VERSION=      $(COMPONENT_VERSION_SUP).$(COMPONENT_VERSION_MAJ).$(COMPONENT_VERSION_MIN)
# The XY in "libpngXY" file and directory names
COMPONENT_VERSION_TAG=$(COMPONENT_VERSION_SUP)$(COMPONENT_VERSION_MAJ)
# Suffix of shared libs:
COMPONENT_VERSION_SONAME=$(COMPONENT_VERSION_TAG).$(COMPONENT_VERSION_MIN).$(COMPONENT_VERSION_PAT)
COMPONENT_PROJECT_URL=  http://www.libpng.org/
COMPONENT_SUMMARY=      Portable Network Graphics library version $(COMPONENT_VERSION)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b3683e8b8111ebf6f1ac004ebb6b0c975cd310ec469d98364388e9cedbfa68be
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/libpng/files/libpng16/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=      zlib
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_FMRI=         image/library/libpng16

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PKG_OPTIONS +=  -D COMPONENT_VERSION_SONAME="$(COMPONENT_VERSION_SONAME)"
PKG_OPTIONS +=  -D COMPONENT_VERSION_TAG="$(COMPONENT_VERSION_TAG)"

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# for tests to pass
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS= \
	'-n ' \
  '-e "/TOTAL/p" ' \
  '-e "/PASS/p" '  \
  '-e "/SKIP/p" '  \
  '-e "/XFAIL/p" ' \
  '-e "/FAIL/p" '  \
  '-e "/XPASS/p" ' \
  '-e "/ERROR/p" ' 

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
