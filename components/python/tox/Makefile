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
#   $WS_TOOLS/python-integrate-project tox
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tox
COMPONENT_VERSION =		3.27.1
COMPONENT_SUMMARY =		tox - tox is a generic virtualenv management and test command line tool
COMPONENT_PROJECT_URL =		https://tox.readthedocs.io
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/43/44/7e646042c3c3fde7be4ef8debd6bc42f32f36766ab526af302abd341a9a1/tox-3.27.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b2a920e35a668cc06942ffd1cf3a4fb221a4d909ca72191fb6d84b0b18a7be04
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox-current-env (test bootstrap)
# - Userland testing framework (see setup.py.mk)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/filelock
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/py
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/virtualenv
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
