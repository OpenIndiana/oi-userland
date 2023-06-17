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
# Copyright 2017 Dariusz Sendkowski
# Copyright 2023 Niklas Poslovski
#

USE_DEFAULT_TEST_TRANSFORMS = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           udunits
COMPONENT_VERSION=        2.2.28
#COMPONENT_REVISION=       1
COMPONENT_FMRI=           library/udunits
COMPONENT_SUMMARY=	A C-based package for the programatic handling of units of physical quantities.
COMPONENT_PROJECT_URL=   https://www.unidata.ucar.edu/software/udunits/
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:590baec83161a3fd62c00efa66f6113cec8a7c461e3f61a5182167e0cc5d579e
COMPONENT_ARCHIVE_URL= https://downloads.unidata.ucar.edu/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=       UCAR
COMPONENT_LICENSE_FILE= COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

CFLAGS+= -std=c99 $(CPP_XPG6MODE)

CONFIGURE_OPTIONS+= --disable-static

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
