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
# Copyright 2021 Till Wegmueller
#

BUILD_BITS=64 # for binaries or 32_and_64 for libraries
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			oniguruma
COMPONENT_VERSION=		6.9.7
COMPONENT_SUMMARY=		oniguruma - regular expression library 
COMPONENT_PROJECT_URL=		https://github.com/kkos/oniguruma
COMPONENT_FMRI=			text/oniguruma
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=			onig-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).1.tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/kkos/$(COMPONENT_NAME)/releases/download/v$(COMPONENT_VERSION).1/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:6444204b9c34e6eb6c0b23021ce89a0370dad2b2f5c00cd44c342753e0b204d9
COMPONENT_LICENSE=		BSD like
COMPONENT_LICENSE_FILE=		COPYING

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

#CONFIGURE_OPTIONS+= # add configuration options here

# Build dependencies
#REQUIRED_PACKAGES+= 
