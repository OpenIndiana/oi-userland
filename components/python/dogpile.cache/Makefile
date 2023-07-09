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
HUMAN_VERSION =			1.2.2
COMPONENT_SUMMARY =		dogpile.cache - A caching front-end based on the Dogpile lock.
COMPONENT_PROJECT_URL =		https://github.com/sqlalchemy/dogpile.cache
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d2/f8/f3e877361372737d83f6592d6ba2126b2018d2208472a5dcb82773694281/dogpile.cache-1.2.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fd9022c0d9cbadadf20942391a95adaf296be80b42daa8e202f8de1c21f198b2
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/decorator
PYTHON_REQUIRED_PACKAGES += library/python/stevedore
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/decorator
TEST_REQUIRED_PACKAGES.python += library/python/mako
TEST_REQUIRED_PACKAGES.python += library/python/pytest
