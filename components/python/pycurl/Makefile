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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project pycurl
#

BUILD_STYLE = pyproject
# Force setup.py build style because we need to pass additional --openssl-dir
# and there seems to be no way how to do that with the default pyproject build
# style.
BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pycurl
HUMAN_VERSION =			7.45.4
COMPONENT_SUMMARY =		PycURL -- A Python Interface To The cURL library
COMPONENT_PROJECT_URL =		http://pycurl.io/
COMPONENT_ARCHIVE_HASH =	\
	sha256:32c8e237069273f4260b6ae13d1e0f99daae938977016021565dc6e11050e803
COMPONENT_LICENSE =		LGPL-2.1-only

TEST_STYLE = pytest

# Install common files to /usr
PYTHON_DATA = $(USRDIR)

include $(WS_MAKE_RULES)/common.mk

# Make sure we compile and link with proper openssl version
LDFLAGS += -L$(OPENSSL_LIBDIR)
LDFLAGS += -R$(OPENSSL_LIBDIR)
COMPONENT_BUILD_SETUP_PY_ARGS += --openssl-dir=$(OPENSSL_PREFIX)

# Rename pycurl documentation to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRSHAREDOCDIR)/pycurl $(PROTOUSRSHAREDOCDIR)/pycurl-$(PYTHON_VERSION) ;

# Compile extra libraries for tests
COMPONENT_PRE_TEST_ACTION += PATH=$(PATH.gnu) make -C $(@D)/tests/fake-curl/libcurl ;

# https://github.com/pycurl/pycurl/issues/876
PYTEST_ADDOPTS += --deselect tests/pause_test.py::PauseTest::test_pause_via_call
PYTEST_ADDOPTS += --deselect tests/pause_test.py::PauseTest::test_pause_via_return

# Replace Python version in pycurl documentation directory name
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/\(usr\/share\/doc\/pycurl-\)3\.[0-9]*/\1$$(PYVER)/' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
