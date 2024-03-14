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
#   $WS_TOOLS/python-integrate-project fields
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		fields
COMPONENT_VERSION =		5.0.0
COMPONENT_SUMMARY =		fields - Container class boilerplate killer.
COMPONENT_PROJECT_URL =		https://github.com/ionelmc/python-fields
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/18/68/b922b5b0b2c1d99171c0ed9ad10296b55ee644eb1fa2fd5e45cafe56ae33/fields-5.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:31d4aa03d8d44e35df13c431de35136997f047a924a597d84f7bc209e1be5727
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# fields --> pytest-benchmark --> aspectlib ==> fields
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/characteristic
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
