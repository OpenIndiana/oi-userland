#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright 2021 Gary Mills
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS=		64
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycairo
# This version supports python 3.6+
COMPONENT_VERSION=	1.20.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Python bindings for Cairo
COMPONENT_PROJECT_URL=	http://www.cairographics.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:34f0a86ee5d98f3fca1f09dd3960d43ea9937b2df44f5270d2eb94f529677150
COMPONENT_ARCHIVE_URL=	https://github.com/pygobject/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=			library/python/pycairo
COMPONENT_CLASSIFICATION=	Development/Python

PYTHON_VERSIONS=	3.7 3.9
PYTHON_DATA=		$(USRDIR)

include $(WS_MAKE_RULES)/common.mk

# Rename some files to make way for symlinks
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRINCDIR)/pycairo; $(MV) py3cairo.h py3cairo.h-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRLIBDIR)/pkgconfig; $(MKDIR) ../$(MACH64)/pkgconfig; $(MV) py3cairo.pc ../$(MACH64)/pkgconfig/py3cairo.pc-$(PYTHON_VERSION)) ;

# Tests require packages: pytest py pluggy benchmark
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_CMD=	$(PYTHON)
COMPONENT_TEST_ARGS=	setup.py test

# Typical test results:
#=========================== short test summary info ==========================
#FAILED tests/test_hypothesis.py::test_fspaths - TypeError: randoms() got an u...
#FAILED tests/test_typing.py::test_typing - AssertionError: assert {'ANTIALIAS...
#=================== 2 failed, 270 passed, 3 skipped in 3.19s =================

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
