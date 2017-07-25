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
# Copyright (c) 2013-2016 Louis M. Picciano. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           gsl
COMPONENT_VERSION=        2.4
COMPONENT_SUMMARY=        GSL - GNU Scientific Library
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:4d46d07b946e7b31c19bbf33dda6204d7bedc2f5462a1bae1d4013426cd1ce9b
COMPONENT_ARCHIVE_URL=    ftp://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=           developer/gsl
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=        GPL v3
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    http://www.gnu.org/software/gsl/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"

CONFIGURE_OPTIONS 	+=--disable-static

unexport SHELLOPTS

	
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
