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
#   $WS_TOOLS/python-integrate-project -d python/CherryPy cherrypy
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cherrypy
HUMAN_VERSION =			18.10.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Object-Oriented HTTP framework
COMPONENT_PROJECT_URL =		https://www.cherrypy.dev
COMPONENT_ARCHIVE_HASH =	\
	sha256:6c70e78ee11300e8b21c0767c542ae6b102a49cac5cfd4e3e313d7bb907c5891
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE.md

include $(WS_MAKE_RULES)/common.mk

# The name varies between runs
COMPONENT_TEST_TRANSFORMS += "-e 's/name=[0-9]\{1,\}/name=X/'"
# Normalize timestamps
COMPONENT_TEST_TRANSFORMS += "-e 's|\[../.../....:..:..:..\]|[TIMESTAMP]|'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\(cherrypy\.access\.\)[0-9]\{1,\}/\1TIMESTAMP/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cheroot
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-collections
PYTHON_REQUIRED_PACKAGES += library/python/more-itertools
PYTHON_REQUIRED_PACKAGES += library/python/portend
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/zc-lockfile
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/objgraph
TEST_REQUIRED_PACKAGES.python += library/python/path
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-forked
TEST_REQUIRED_PACKAGES.python += library/python/requests-toolbelt
TEST_REQUIRED_PACKAGES.python += library/python/routes
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
