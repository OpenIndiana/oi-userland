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
# Copyright (c) 2014 Alexander Pyhalov.  All rights reserved.
#

BUILD_STYLE= setup.py
BUILD_BITS= NO_ARCH
TEST_STYLE= pytest
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyxdg
COMPONENT_VERSION=	0.28
COMPONENT_SUMMARY=	A python library to access freedesktop.org standards
COMPONENT_PROJECT_URL=	https://freedesktop.org/wiki/Software/pyxdg/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:3267bb3074e934df202af2ee0868575484108581e6f3cb006af1da35395e88b4
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/pyxdg
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSIONS= 3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
