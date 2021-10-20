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
# Copyright 2015, PALO Richard.
# Copyright 2017 Gary Mills
# Copyright 2021 Nona Hansel
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS=		64
BUILD_STYLE=	setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		MarkupSafe
COMPONENT_VERSION=	2.0.1
COMPONENT_SUMMARY=	A XML/HTML/XHTML Markup safe string for Python
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/MarkupSafe
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:594c67807fb16238b30c44bdf74f36c02cdf22d1c8cda91ef8a0ed8dabf5620a
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/markupsafe
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	BSD

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =    $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
