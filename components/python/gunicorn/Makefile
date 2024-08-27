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
#   $WS_TOOLS/python-integrate-project gunicorn
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		gunicorn
HUMAN_VERSION =			23.0.0
COMPONENT_SUMMARY =		WSGI HTTP Server for UNIX
COMPONENT_PROJECT_URL =		https://gunicorn.org
COMPONENT_ARCHIVE_URL =		\
	https://github.com/benoitc/gunicorn/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:d92daec8a5fb3d48d61ae13841173e93f321b0fd3378d876b7efbb75a1e95247
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# We have no eventlet packaged yet.
COMPONENT_POST_UNPACK_ACTION += $(RM) $(COMPONENT_SRC)/gunicorn/workers/geventlet.py ;
COMPONENT_POST_UNPACK_ACTION += $(RM) $(COMPONENT_SRC)/tests/workers/test_geventlet.py ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/gevent
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
