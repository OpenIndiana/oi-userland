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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lxml
HUMAN_VERSION =			5.0.0
COMPONENT_SUMMARY =		lxml - Powerful and Pythonic XML processing library combining libxml2/libxslt with the ElementTree API.
COMPONENT_PROJECT_URL =		https://lxml.de/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/80/2c/076fafd979728858829fb9ce2e13fa6367b6be9acc4da0cff6367aa6a1ce/lxml-5.0.0.zip
COMPONENT_ARCHIVE_HASH =	\
	sha256:2219cbf790e701acf9a21a31ead75f983e73daf0eceb9da6990212e4d20ebefe
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

COMPONENT_ARCHIVE =		$(COMPONENT_SRC).zip

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
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += system/library
