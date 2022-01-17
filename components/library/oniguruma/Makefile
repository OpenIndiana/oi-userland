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
# Copyright 2022, Friedrich Kink. All rights reserved.
#

BUILD_BITS=             64
BUILD_STYLE=            configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		onig
COMPONENT_VERSION=	6.9.7
COMPONENT_MNR_VERSION=	1
COMPONENT_SUMMARY=	Oniguruma is a modern and flexible regular expressions library.
COMPONENT_FMRI= 	library/$(COMPONENT_NAME)
COMPONENT_DESCRIPTION=	Oniguruma is a modern and flexible regular expressions library. \
			It encompasses features from different regular expression \
			implementations that traditionally exist in different languages.
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).$(COMPONENT_MNR_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6444204b9c34e6eb6c0b23021ce89a0370dad2b2f5c00cd44c342753e0b204d9
COMPONENT_PROJECT_URL=	https://github.com/kkos/oniguruma
COMPONENT_ARCHIVE_URL=	https://github.com/kkos/oniguruma/releases/download/v$(COMPONENT_VERSION).$(COMPONENT_MNR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sha256
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	Oniguruma LICENSE

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+=	--enable-static=no

COMPONENT_TEST_TRANSFORMS += '-e "/^PASS: /!d" '

unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
