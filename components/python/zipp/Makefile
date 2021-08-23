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
# Copyright 2021 Aurelien Larcher
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zipp
COMPONENT_VERSION=	1.2.0
COMPONENT_SUMMARY=	Backport of pathlib-compatible object wrapper for zip files
COMPONENT_PROJECT_URL=	https://github.com/jaraco/zipp
COMPONENT_FMRI=		library/python/zipp
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= \
	sha256:c70410551488251b0fee67b460fb9a536af8d6f9f008ad10ac51f615b6a521b1
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS= $(PYTHON_VERSIONS_ALL)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
