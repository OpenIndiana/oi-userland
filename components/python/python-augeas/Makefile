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
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		python-augeas
COMPONENT_VERSION=	0.5.0
COMPONENT_SUMMARY=	'Python bindings for Augeas'
COMPONENT_PROJECT_URL=	http://augeas.net/
COMPONENT_FMRI=		library/python/augeas
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH=	sha256:67d59d66cdba8d624e0389b87b2a83a176f21f16a87553b50f5703b23f29bac2
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_CMD =	$(PYTHON) test_augeas.py

COMPONENT_TEST_TARGETS =

COMPONENT_TEST_ARGS =

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/test

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(TEST_NO_ARCH)

# Test suite requirements
REQUIRED_PACKAGES += library/augeas-lenses
REQUIRED_PACKAGES += library/augeas-libs

# Auto-generated dependencies
