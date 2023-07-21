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
#   $WS_TOOLS/python-integrate-project pip
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pip
HUMAN_VERSION =			23.2.1
COMPONENT_SUMMARY =		pip - The PyPA recommended tool for installing Python packages.
COMPONENT_PROJECT_URL =		https://pip.pypa.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ba/19/e63fb4e0d20e48bd2167bb7e857abc0e21679e24805ba921a224df8977c0/pip-23.2.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fb0bd5435b3200c602b5bf61d2d43c2f13c02e29c1707567ae7fbc514eb9faf2
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# https://github.com/pypa/pip/issues/11824
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# usr/bin/pip3.x needs to be handled separately because we have no generic
# rules covering it
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/\(usr\/bin\/pip\)3\.[0-9]\{1,\}$$/\1$$(PYVER)/' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
