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
#   $WS_TOOLS/python-integrate-project subprocess-tee
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		subprocess-tee
HUMAN_VERSION =			0.4.1
COMPONENT_SUMMARY =		subprocess-tee - subprocess-tee
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f6/a0/acafd85c7c0aead293a16a70a49aba20ba2af9478771370b2897eae6059c/subprocess-tee-0.4.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b3c124993f8b88d1eb1c2fde0bc2069787eac720ba88771cba17e8c93324825d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# subprocess-tee --> molecule ==> ansible-compat ==> subprocess-tee
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/ansible-core
TEST_REQUIRED_PACKAGES.python += library/python/enrich
TEST_REQUIRED_PACKAGES.python += library/python/molecule
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-plus
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
