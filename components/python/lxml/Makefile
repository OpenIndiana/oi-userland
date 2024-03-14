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
#   $WS_TOOLS/python-integrate-project lxml
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lxml
HUMAN_VERSION =			5.1.0
COMPONENT_SUMMARY =		lxml - Powerful and Pythonic XML processing library combining libxml2/libxslt with the ElementTree API.
COMPONENT_PROJECT_URL =		https://lxml.de/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2b/b4/bbccb250adbee490553b6a52712c46c20ea1ba533a643f1424b27ffc6845/lxml-5.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3eea6ed6e6c918e468e693c41ef07f3c3acc310b70ddd9cc72d9ef84bc9564ca
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This project uses custom test style.
# See project's Makefile.
TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# This project uses custom test style.
# See project's Makefile.
COMPONENT_TEST_CMD =		$(PYTHON) test.py
COMPONENT_TEST_ARGS =		-vv
COMPONENT_TEST_TARGETS =

# The test.py uses modules from the src subdirectory, but compiled dynamic
# libraries are not available there.
#
# To workaround this we copy .so files from proto area back to build dir before
# we run tests.
COMPONENT_PRE_TEST_ACTION += \
	$(CP) $(PROTO_DIR)/$(PYTHON_LIB)/$(COMPONENT_NAME)/*.so $(@D)/src/$(COMPONENT_NAME) ;

# Sort list of tests
COMPONENT_TEST_TRANSFORMS += \
	" | ( \
		$(GSED) -u -e '/^$$/Q' | $(SORT) | $(NAWK) '{print}END{if(NR>0)printf(\"\\\\n\")}' ; \
		$(CAT) \
	)"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cython
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += system/library
