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
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS = NO_ARCH
BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		kafka-python
COMPONENT_VERSION=	2.0.1
COMPONENT_SUMMARY=	Python client for Apache Kafka
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e59ad42dec8c7d54e3fbba0c1f8b54c44d92a3392d88242962d0c29803f2f6f8
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/dpkp/kafka-python
COMPONENT_FMRI=		library/python/kafka-python
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	Apache License 2.0
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	2.7 3.5

# We miss pytest-mock python module
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_ENV +=   $(PYTHON_ENV)
COMPONENT_TEST_ENV +=   PYTHONPATH=$(PROTO_DIR)/$(PYTHON_LIB)
COMPONENT_TEST_CMD =    $(PYTHON.$(BITS)) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS = 

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
