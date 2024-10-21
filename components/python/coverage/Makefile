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
#   $WS_TOOLS/python-integrate-project coverage
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		coverage
HUMAN_VERSION =			7.6.4
COMPONENT_SUMMARY =		Code coverage measurement for Python
COMPONENT_PROJECT_URL =		https://github.com/nedbat/coveragepy
COMPONENT_ARCHIVE_HASH =	\
	sha256:29fc0f17b1d3fea332f8001d4558f8214af7f1d87a345f3a133c901d60347c73
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Testing needs a writable directory with existing pth file
COMPONENT_PRE_TEST_ACTION += touch $(PROTO_DIR)/$(PYTHON_LIB)/foo.pth
COMPONENT_POST_TEST_ACTION += $(RM) $(PROTO_DIR)/$(PYTHON_LIB)/foo.pth

# Force verbose output via tox posargs
TOX_POSARGS += -v

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/cffi
TEST_REQUIRED_PACKAGES.python += library/python/colorama
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/gevent
TEST_REQUIRED_PACKAGES.python += library/python/greenlet
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
