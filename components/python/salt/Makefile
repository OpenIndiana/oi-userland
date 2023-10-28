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
#   $WS_TOOLS/python-integrate-project salt
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		salt
HUMAN_VERSION =			3006.4
COMPONENT_SUMMARY =		salt - Portable, distributed, remote execution and configuration management system
COMPONENT_PROJECT_URL =		https://saltproject.io
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/97/09/e25bf3e4a4a217045ab2defaec8d3a2f9bc916166b6aaccb7288e2b99712/salt-3006.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d097885c33c2cfaa0ccdc627ca570d67690c8d037dc7801be88788bcca1036ae
COMPONENT_LICENSE =		Apache-2.0 AND MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI =		system/management/salt
COMPONENT_CLASSIFICATION =	System/Administration and Configuration

# Needs pytest-salt-factories >= 1.0.0rc21 to run tests, but such version is
# still pre-release.
TEST_STYLE = none

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

# The installer is unable to install salt wheel due to some bug (see
# https://github.com/pypa/installer/issues/194) so we need to switch to
# pyproject_installer.  The pyproject_installer is used during bootstrap so we
# just pretend we are bootstapping and we will get the pyproject_installer
# based build and install.
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Install salt.xml
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application ; \
	$(CP) $(COMPONENT_DIR)/files/salt.xml $(PROTO_DIR)/lib/svc/manifest/application ; \

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += requirements/pytest.txt

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/contextvars
PYTHON_REQUIRED_PACKAGES += library/python/distro
PYTHON_REQUIRED_PACKAGES += library/python/jinja2
PYTHON_REQUIRED_PACKAGES += library/python/jmespath
PYTHON_REQUIRED_PACKAGES += library/python/looseversion
PYTHON_REQUIRED_PACKAGES += library/python/markupsafe
PYTHON_REQUIRED_PACKAGES += library/python/msgpack
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/psutil
PYTHON_REQUIRED_PACKAGES += library/python/pycryptodomex
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/pyzmq
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-custom-exit-code
TEST_REQUIRED_PACKAGES.python += library/python/pytest-helpers-namespace
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest-salt-factories
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subtests
TEST_REQUIRED_PACKAGES.python += library/python/pytest-tempdir
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
