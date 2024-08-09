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
#   $WS_TOOLS/python-integrate-project -d python/Babel babel
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		babel
HUMAN_VERSION =			2.16.0
COMPONENT_SUMMARY =		Internationalization utilities
COMPONENT_PROJECT_URL =		https://babel.pocoo.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:d1f3554ca26605fe173f3de0c65f750f5a42f924499bf134de6423582298e316
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# We need the directory where the cldr-common zip file is downloaded
COMPONENT_PRE_TEST_ACTION += $(MKDIR) $(@D)/cldr ;
# Remove the directory after testing is completed
COMPONENT_POST_TEST_ACTION += $(RM) -r $(@D)/cldr ;
# https://github.com/python-babel/babel/issues/935
COMPONENT_TEST_ENV += TZ=UTC
# The order of import_cldr INFO and WARNING lines could vary
COMPONENT_TEST_TRANSFORMS += "-e '/^INFO:import_cldr:/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/^WARNING:import_cldr:/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
