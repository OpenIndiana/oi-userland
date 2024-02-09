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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pycurl
HUMAN_VERSION =			7.45.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pycurl - PycURL -- A Python Interface To The cURL library
COMPONENT_PROJECT_URL =		http://pycurl.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a8/af/24d3acfa76b867dbd8f1166853c18eefc890fc5da03a48672b38ea77ddae/pycurl-7.45.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5730590be0271364a5bddd9e245c9cc0fb710c4cbacbdd95264a3122d23224ca
COMPONENT_LICENSE =		LGPL-2.1-only

TEST_STYLE = pytest

# Install common files to /usr
PYTHON_DATA = $(USRDIR)

include $(WS_MAKE_RULES)/common.mk

# Make sure we link with proper openssl version
LDFLAGS += -L$(OPENSSL_LIBDIR)
LDFLAGS += -R$(OPENSSL_LIBDIR)
COMPONENT_BUILD_SETUP_PY_ARGS += --openssl-dir=$(OPENSSL_PREFIX)

# Rename pycurl documentation to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRSHAREDOCDIR)/pycurl $(PROTOUSRSHAREDOCDIR)/pycurl-$(PYTHON_VERSION) ;

# Compile extra libraries for tests
COMPONENT_PRE_TEST_ACTION += make -C $(@D)/tests/fake-curl/libcurl ;

# Replace Python version in pycurl documentation directory name
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/\(usr\/share\/doc\/pycurl-\)3\.[0-9]*/\1$$(PYVER)/' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
