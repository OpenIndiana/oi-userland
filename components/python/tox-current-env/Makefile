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
#   $WS_TOOLS/python-integrate-project tox-current-env
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tox-current-env
COMPONENT_VERSION =		0.0.8
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		tox-current-env - Use current environment instead of virtualenv for tox testenvs
COMPONENT_PROJECT_URL =		https://github.com/fedora-python/tox-current-env
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/79/47/15350fe5510ab977af93a18ac008b99ff8cebb714e14ae021e7d63b75c27/tox-current-env-0.0.8.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b587e9679d296e5d19add3929a3a4aa2cd0086314fb1501d76e50c5b769d5282
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - Userland testing framework (see setup.py.mk)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tox
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
