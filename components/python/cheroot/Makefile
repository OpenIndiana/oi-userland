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
# Copyright 2018 Alexander Pyhalov
#

BUILD_STYLE=setup.py
BUILD_BITS=NO_ARCH
PYTHON3_ONLY=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cheroot
COMPONENT_VERSION=      8.5.2
COMPONENT_REVSION=	1
COMPONENT_SUMMARY=      Cheroot - high-performance, pure-Python HTTP server
COMPONENT_PROJECT_URL=  https://github.com/cherrypy/cheroot
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f137d03fd5155b1364bea557a7c98168665c239f6c8cedd8f80e81cdfac01567
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_FMRI=         library/python/cheroot
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= LICENSE.md

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR)/usr/bin ; $(MV) -f cheroot cheroot-$(PYTHON_VERSION))

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
