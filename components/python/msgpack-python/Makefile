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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		msgpack-python
COMPONENT_VERSION=	0.4.7
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/msgpack-python
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5e001229a54180a02dcdd59db23c9978351af55b1290c27bc549e381f43acd6b
COMPONENT_ARCHIVE_URL=	$(call pypi_url)

PYTHON_VERSIONS=        2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR=     $(SOURCE_DIR)
COMPONENT_TEST_ARGS=
COMPONENT_TEST_CMD=     py.test-$(PYTHON_VERSION)

$(TEST_32_and_64):	$(INSTALL_32_and_64)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
