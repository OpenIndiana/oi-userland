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

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pickleshare
COMPONENT_VERSION= 	0.7.4
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	https://github.com/pickleshare/pickleshare
COMPONENT_FMRI=	library/python/pickleshare
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:84a9257227dfdd6fe1b4be1319096c20eb85ff1e82c7932f36efccfe1b09737b
COMPONENT_ARCHIVE_URL= \
  $(call pypi_url)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.5

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk


# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
