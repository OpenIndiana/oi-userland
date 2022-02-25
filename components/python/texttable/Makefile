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
# Copyright 2019 Nona Hansel
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS=			NO_ARCH
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		texttable
COMPONENT_VERSION=	1.6.4
COMPONENT_SUMMARY=	Python module for creating simple ASCII tables
COMPONENT_PROJECT_URL=	https://github.com/foutaise/texttable
COMPONENT_FMRI=		library/python/texttable
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= sha256:42ee7b9e15f7b225747c3fa08f43c5d6c83bc899f80ff9bae9319334824076e9
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR=	$(SOURCE_DIR)
PYV= $(subst .,,$(PYTHON_VERSION))
COMPONENT_TEST_CMD=	tox -e py$(PYV)

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/pluggy-35
REQUIRED_PACKAGES += library/python/pluggy-37
REQUIRED_PACKAGES += library/python/pluggy-39
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
#REQUIRED_PACKAGES += library/python/pytest-cov-35
REQUIRED_PACKAGES += library/python/pytest-cov-37
REQUIRED_PACKAGES += library/python/pytest-cov-39
REQUIRED_PACKAGES += library/python/tox

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
