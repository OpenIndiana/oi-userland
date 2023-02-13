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

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gsl
COMPONENT_VERSION=      2.7.1
COMPONENT_SUMMARY=      GSL - GNU Scientific Library
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/gsl/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:dcb0fbd43048832b757ff9942691a8dd70026d5da0ff85601e52687f6deeb34b
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/gsl
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

CONFIGURE_OPTIONS += --disable-static

unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
	'-e "/test-suite.log/p" ' \
	'-e "/Testsuite/p" ' \
	'-e "/====/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
