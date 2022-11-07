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
#   $WS_TOOLS/python-integrate-project setuptools_scm
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools_scm
COMPONENT_VERSION =		7.0.5
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		setuptools_scm - the blessed package to manage your versions by scm tags
COMPONENT_PROJECT_URL =		https://github.com/pypa/setuptools_scm/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/d0/43/f038b5009f93bcd77b1b8da9e6d424b739ab17aec9726f3a99eba23d53ca/setuptools_scm-7.0.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:031e13af771d6f892b941adb6ea04545bbf91ebc5ce68c78aaf3fff6e1fb4844
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - importlib_metadata
PYTHON_BOOTSTRAP = yes

# Disable tests because required packages are not available during bootstrap
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
