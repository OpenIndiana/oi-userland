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
#   $WS_TOOLS/python-integrate-project persistent
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		persistent
HUMAN_VERSION =			5.0
COMPONENT_SUMMARY =		persistent - Translucent persistent objects
COMPONENT_PROJECT_URL =		https://github.com/zopefoundation/persistent/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/8f/24/a04530e61999442cecf4a6acb234db159915abaeb8081a28be821abf861a/persistent-5.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:871e63c52131160795cdc8e9c3dd313f86e0dff34c151c98dcd9123c6d8ce673
COMPONENT_LICENSE =		ZPL-2.1
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Force no colors and more verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -vv

# This project uses both cpython and abi3 ABI depending on particular library.
# To deal with this we need to disable automatic ABI library name transforms.
PY3_CPYTHON_NAMING=\#

# Replace Python version in include file paths
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's|\(usr/include/python\)3.[0-9]\{1,\}/|\1$$(PYVER)/|' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cffi
PYTHON_REQUIRED_PACKAGES += library/python/zope-interface
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/manuel
TEST_REQUIRED_PACKAGES.python += library/python/repoze-sphinx-autointerface
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
TEST_REQUIRED_PACKAGES.python += library/python/zope-testrunner
