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

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libdvdread
COMPONENT_VERSION=      5.0.4
COMPONENT_REVISION=     2
COMPONENT_FMRI=         library/video/libdvdread
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SUMMARY=      Library for reading DVD video disks
COMPONENT_GIT_HASH=494311d309441846eae697f915b61d2980bfa69d
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= \
	sha256:c2aa771320ba98cd279ed0ddc204c9751a981eccdb84c121e25beadb21da9300
# 5.0.4 is a bug fix release which was never released as tarball
COMPONENT_ARCHIVE_URL=  \
	https://github.com/mirror/libdvdread/archive/$(COMPONENT_GIT_HASH).zip
COMPONENT_PROJECT_URL=  http://dvdnav.mplayerhq.hu
COMPONENT_LICENSE=      GPLv2.0
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D); autoreconf -f -i )

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
