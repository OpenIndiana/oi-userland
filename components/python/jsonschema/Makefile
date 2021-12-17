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
# Copyright 2017 Gary Mills
# Copyright 2021 Nona Hansel
# Copyright (c) 2015 Alexander Pyhalov
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         jsonschema
COMPONENT_VERSION=      3.2.0
COMPONENT_REVISION=		3
COMPONENT_PROJECT_URL=  https://pypi.python.org/pypi/jsonschema
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:c8a85b28d377cc7737e46e2d9f2b4f44ee3c0e1deac6bf46ddefc7187d30797a
COMPONENT_ARCHIVE_URL=  https://pypi.python.org/packages/source/j/jsonschema/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; \
                $(MV) jsonschema jsonschema-$(PYTHON_VERSION); )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += library/python/importlib-metadata-35
REQUIRED_PACKAGES += library/python/importlib-metadata-37
REQUIRED_PACKAGES += library/python/importlib-metadata-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
