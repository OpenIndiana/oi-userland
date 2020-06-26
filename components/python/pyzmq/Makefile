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
# Copyright (c) 2020 Alexander Pyhalov
#

BUILD_STYLE= setup.py
BUILD_BITS= 32_and_64

include ../../../make-rules/shared-macros.mk

PATH=$(PATH.gnu)

COMPONENT_NAME=		pyzmq
COMPONENT_VERSION=	19.0.0
COMPONENT_SUMMARY=	Python bindings for zeromq
COMPONENT_PROJECT_URL=	https://github.com/zeromq/pyzmq
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5e1f65e576ab07aed83f444e201d86deb01cd27dcf3f37c727bc8729246a60a8
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/pyzmq
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE= BSD

PYTHON_VERSIONS=	2.7 3.5

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/zmq/tests
COMPONENT_TEST_CMD =    $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =


# Auto-generated dependencies
REQUIRED_PACKAGES += library/c++/zeromq
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
