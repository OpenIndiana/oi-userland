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
#   $WS_TOOLS/python-integrate-project -d python/PyYAML pyyaml
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyyaml
HUMAN_VERSION =			6.0.3
COMPONENT_SUMMARY =		YAML parser and emitter for Python
COMPONENT_PROJECT_URL =		https://pyyaml.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:d76623373421df22fb4cf8817020cbb7ef15c725b9d5e45f17e189bfc384190f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/cython
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
