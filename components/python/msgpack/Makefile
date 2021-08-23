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
# Copyright 2021 Nona Hansel
#

BUILD_BITS=				64
BUILD_STYLE=			setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		msgpack
COMPONENT_VERSION=	1.0.2
COMPONENT_FMRI=         library/python/msgpack
COMPONENT_PROJECT_URL=	https://pypi.org/project/msgpack/
COMPONENT_CLASSIFICATION= Development/Python		
COMPONENT_SUMMARY=	'Python MessagePack (de)serializer'
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fae04496f5bc150eefad4e9571d1a76c55d021325dcd484ce45065ebbdd00984
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_LICENSE_FILE= COPYING

PYTHON_VERSIONS= 	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR=     $(SOURCE_DIR)
COMPONENT_TEST_ARGS=
COMPONENT_TEST_CMD=     py.test-$(PYTHON_VERSION)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
