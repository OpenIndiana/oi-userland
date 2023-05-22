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
#   $WS_TOOLS/python-integrate-project dogpile.cache
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dogpile.cache
HUMAN_VERSION =			1.2.1
COMPONENT_SUMMARY =		dogpile.cache - A caching front-end based on the Dogpile lock.
COMPONENT_PROJECT_URL =		https://github.com/sqlalchemy/dogpile.cache
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/21/fa/2fec52e38feb6ce89930be010314aa99ff616d6f6dc068cfaa7491ce5f3e/dogpile.cache-1.2.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1d0be0cef90505c9f24e9f00aedab8dce9356d28a4153d5660ab13eeb6a0cfd4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing fails with the randomly plugin installed
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/decorator
PYTHON_REQUIRED_PACKAGES += library/python/stevedore
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/decorator
TEST_REQUIRED_PACKAGES.python += library/python/mako
TEST_REQUIRED_PACKAGES.python += library/python/pytest
