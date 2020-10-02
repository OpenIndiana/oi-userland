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
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	python-xlib
COMPONENT_VERSION= 	0.26
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	'Python interface to the X11 protocol'
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:b819c7e5f55830305919d78ea42b0cbd5e13687f5d12aa53556c33674b9876df
COMPONENT_ARCHIVE_URL= \
  $(call pypi_url)
COMPONENT_PROJECT_URL = https://github.com/python-xlib/python-xlib
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_FMRI=	library/python/python-xlib
COMPONENT_CLASSIFICATION=	Development/Python

PYTHON_VERSIONS=	2.7 3.5

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk
