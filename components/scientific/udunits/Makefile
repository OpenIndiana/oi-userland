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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           udunits
COMPONENT_VERSION=        2.2.25
COMPONENT_REVISION=       1
COMPONENT_FMRI=           library/udunits
COMPONENT_SUMMARY=	A C-based package for the programatic handling of units of physical quantities. 
COMPONENT_PROJECT_URL=   http://www.unidata.ucar.edu/software/udunits/ 
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ad486f8f45cba915ac74a38dd15f96a661a1803287373639c17e5a9b59bfd540
COMPONENT_ARCHIVE_URL= ftp://ftp.unidata.ucar.edu/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=       UCAR 
COMPONENT_LICENSE_FILE= COPYRIGHT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS+= -std=c99 $(CPP_XPG6MODE)

CONFIGURE_OPTIONS+= --disable-static

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
