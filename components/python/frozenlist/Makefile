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
#   $WS_TOOLS/python-integrate-project frozenlist
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		frozenlist
HUMAN_VERSION =			1.4.0
COMPONENT_SUMMARY =		frozenlist - A list-like structure which implements collections.abc.MutableSequence
COMPONENT_PROJECT_URL =		https://github.com/aio-libs/frozenlist
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/8c/1f/49c96ccc87127682ba900b092863ef7c20302a2144b3185412a08480ca22/frozenlist-1.4.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:09163bdf0b2907454042edb19f887c6d33806adc71fbd54afc14908bfdc22251
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
