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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		MarkupSafe
COMPONENT_VERSION=	0.23
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/MarkupSafe
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:a4ec1aff59b95a14b45eb2e23761a0179e98319da5a7eb76b56ea8cdc7b871c3
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/M/MarkupSafe/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_ARGS=	./setup.py test

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
