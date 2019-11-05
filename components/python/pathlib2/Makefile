#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pathlib2
COMPONENT_VERSION= 	2.3.2
COMPONENT_PROJECT_URL=	https://github.com/mcmtroffaes/pathlib2
COMPONENT_FMRI=	library/python/pathlib2
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8eb170f8d0d61825e09a95b38be068299ddeda82f35e96c3301a8a5e7604cb83
COMPONENT_ARCHIVE_URL= \
  $(call pypi_url)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE.rst

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR = $(SOURCE_DIR)/tests
COMPONENT_TEST_ARGS = -m unittest discover --pattern=*.py

build: $(BUILD_NO_ARCH)

install: $(INSTALL_NO_ARCH)

test:	$(TEST_NO_ARCH)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
