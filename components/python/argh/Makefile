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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	argh
COMPONENT_VERSION= 	0.26.2
COMPONENT_REVISION=	2
COMPONENT_SUMMARY= 	An unobtrusive argparse wrapper with natural syntax
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:e9535b8c84dc9571a48999094fda7f33e63c3f1b74f3e5f3ac0105a58405bb65
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/a/argh/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/argh

PYTHON_VERSIONS=	2.7 3.5

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
