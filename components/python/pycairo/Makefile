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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycairo
COMPONENT_VERSION=	1.10.0
COMPONENT_PROJECT_URL=	http://cairographics.org/pycairo/
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:9aa4078e7eb5be583aeabbe8d87172797717f95e8c4338f0d4a17b683a7253be
COMPONENT_ARCHIVE_URL=	http://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	python-mod/pycairo

TPNO=			30739

# upstream delivers python2 support separately as "py2cairo"
PYTHON_VERSIONS=        $(PYTHON3_VERSIONS)

BUILD_STYLE= waf

# replicated from $(WS_MAKE_RULES)/setup.py.mk since this uses waf.mk instead
CONFIGURE_64 = $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.configured)
BUILD_64     = $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.built)
INSTALL_64   = $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.installed)
TEST_64      = $(PYTHON3_VERSIONS:%=$(BUILD_DIR)/$(MACH64)-%/.tested-and-compared)

# Cannot run tests until build machines update to s12_105 due to bug 23763105
TEST_TARGET = $(SKIP_TEST)

# Requires newer version of cairo than we have available in S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Trick bundled waf into unpacking itself so we can patch it
COMPONENT_POST_UNPACK_ACTION += \
	(cd $(@D) ; $(PYTHON.3.5) waf --help >> /dev/null );

# Do not install optimised compiled .pyo files
CONFIGURE_OPTIONS += --nopyo

# This needed to be added for pycairo to build cleanly s12_109 onwards
studio_C99MODE = $(studio_C99_ENABLE)

# The bundled waf compiles to the old pre-python-3.2 locations, so
# tell it not to bother, and take care of it ourselves
CONFIGURE_OPTIONS += --nopyc
COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -m compileall $(PROTO_DIR)$(PYTHON_LIB)/cairo ;

# waf picks up the PYTHONDIR & PYTHONARCHDIR settings at configure time,
# but still insists on installing to site-packages instead of vendor-packages
PYTHON_SITE_DIR = $(USRLIB)/python$(PYTHON_VERSION)/site-packages
COMPONENT_PRE_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)$(PYTHON_LIB)/cairo \
		 $(PROTO_DIR)$(PYTHON_SITE_DIR) ; \
	$(RM) -r $(PROTO_DIR)$(PYTHON_SITE_DIR) ; \
	$(LN) -s $(PROTO_DIR)$(PYTHON_LIB) $(PROTO_DIR)$(PYTHON_SITE_DIR) ; \
	$(RM) -r $(PROTO_DIR)$(PYTHON_LIB)/cairo/64 ; \
	$(LN) -s . $(PROTO_DIR)$(PYTHON_LIB)/cairo/64

# the test scripts aren't hooked into the test target in pycairo, so run directly
COMPONENT_TEST_DIR = $(@D)/test
COMPONENT_TEST_CMD = /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_TARGETS =

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35

# py.test is required for testing, not building or runtime
REQUIRED_PACKAGES += library/python/pytest

