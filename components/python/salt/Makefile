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
HUMAN_VERSION =			3007.1
COMPONENT_SUMMARY =		Portable, distributed, remote execution and configuration management system
COMPONENT_PROJECT_URL =		https://saltproject.io
COMPONENT_ARCHIVE_HASH =	\
	sha256:b933ac4cb3e4b1118b46dada55c9cc6bdc6f0f94b4c92877aec44b25c6a28c9a
COMPONENT_LICENSE =		Apache-2.0 AND MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

COMPONENT_FMRI =		system/management/salt
COMPONENT_CLASSIFICATION =	System/Administration and Configuration

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

# The installer is unable to install salt wheel due to some bug (see
# https://github.com/saltstack/salt/issues/65083) so we need to switch to
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
PYTHON_REQUIRED_PACKAGES += library/python/aiohttp
PYTHON_REQUIRED_PACKAGES += library/python/cherrypy
PYTHON_REQUIRED_PACKAGES += library/python/contextvars
PYTHON_REQUIRED_PACKAGES += library/python/cryptography
PYTHON_REQUIRED_PACKAGES += library/python/distro
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/jinja2
PYTHON_REQUIRED_PACKAGES += library/python/jmespath
PYTHON_REQUIRED_PACKAGES += library/python/looseversion
PYTHON_REQUIRED_PACKAGES += library/python/markupsafe
PYTHON_REQUIRED_PACKAGES += library/python/msgpack
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/psutil
PYTHON_REQUIRED_PACKAGES += library/python/pycryptodomex
PYTHON_REQUIRED_PACKAGES += library/python/pyopenssl
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/pyzmq
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tornado
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
TEST_REQUIRED_PACKAGES.python += library/python/flaky
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/more-itertools
TEST_REQUIRED_PACKAGES.python += library/python/pyfakefs
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-custom-exit-code
TEST_REQUIRED_PACKAGES.python += library/python/pytest-helpers-namespace
TEST_REQUIRED_PACKAGES.python += library/python/pytest-httpserver
TEST_REQUIRED_PACKAGES.python += library/python/pytest-salt-factories
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subtests
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/trustme
