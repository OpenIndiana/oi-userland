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
HUMAN_VERSION =			5.3.0
COMPONENT_SUMMARY =		Powerful and Pythonic XML processing library combining libxml2/libxslt with the ElementTree API.
COMPONENT_PROJECT_URL =		https://lxml.de/
COMPONENT_ARCHIVE_HASH =	\
	sha256:4e109ca30d1edec1ac60cdbe341905dc3b8f55b16855e03a54aaf59e51ec8c6f
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This project uses custom test style.
# See project's Makefile.
TEST_STYLE = custom

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# lxml --> lxml_html_clean ==> lxml
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

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

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += html-clean

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cython
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/lxml-html-clean
