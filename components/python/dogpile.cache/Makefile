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
#   $WS_TOOLS/python-integrate-project -d python/dogpile.cache dogpile_cache
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dogpile_cache
HUMAN_VERSION =			1.5.0
COMPONENT_SUMMARY =		A caching front-end based on the Dogpile lock.
COMPONENT_PROJECT_URL =		https://github.com/sqlalchemy/dogpile.cache
COMPONENT_ARCHIVE_HASH =	\
	sha256:849c5573c9a38f155cd4173103c702b637ede0361c12e864876877d0cd125eec
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# Python 3.9 is not supported by dogpile.cache >= 1.5.0
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/decorator
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/stevedore
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/decorator
TEST_REQUIRED_PACKAGES.python += library/python/mako
TEST_REQUIRED_PACKAGES.python += library/python/pytest
