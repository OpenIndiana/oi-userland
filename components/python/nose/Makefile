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
#   $WS_TOOLS/python-integrate-project nose
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nose
HUMAN_VERSION =			1.3.7
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		nose - nose extends unittest to make testing easier
COMPONENT_PROJECT_URL =		http://readthedocs.org/docs/nose/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/58/a5/0dc93c3ec33f4e281849523a5a913fa1eea9a3068acfa754d44d88107a44/nose-1.3.7.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f1bffef9cbc82628f6e7d7b40d7e255aefaa1adb6a1b1d26c69a8b79e6208a98
COMPONENT_LICENSE =		LGPL-2.1-only

# nose uses custom testing via the selftest.py script
TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# Support for 2to3 was removed in setuptools 58.0.0 so we cannot rely on
# use_2to3 and we need to convert the code explicitly here.
COMPONENT_PRE_BUILD_ACTION += 2to3-$(PYTHON_VERSION) --write --nobackups --no-diffs $(@D) ;

# We need to convert tests from Python 2 syntax to Python 3 syntax before we
# run them.  See selftest.py for details.
COMPONENT_PRE_TEST_ACTION = \
	cd $(@D) ; $(PYTHON) setup.py --no-user-cfg build_tests ;

# Custom test style
COMPONENT_TEST_CMD =		$(PYTHON) selftest.py
COMPONENT_TEST_ARGS =
COMPONENT_TEST_TARGETS =

# Get verbose test results
COMPONENT_TEST_ENV +=		NOSE_VERBOSE=2

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"

# teamcity-messages pollutes test report and causes test_issue135 to fail
TEST_CONFLICTING_PACKAGES.python += library/python/teamcity-messages

# Manually added test dependencies
TEST_REQUIRED_PACKAGES.python += library/python/twisted

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
