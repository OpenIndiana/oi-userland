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

COMPONENT_NAME= 	ptyprocess
COMPONENT_VERSION= 	0.6.0
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	https://github.com/pexpect/ptyprocess
COMPONENT_FMRI=	library/python/ptyprocess
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:923f299cc5ad920c68f2bc0bc98b75b9f838b93b599941a6b63ddbc2476394c0
COMPONENT_ARCHIVE_URL= \
  $(call pypi_url)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	ISC
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.5 3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR = $(SOURCE_DIR)/tests
COMPONENT_TEST_CMD = $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
