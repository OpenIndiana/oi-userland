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
#   $WS_TOOLS/python-integrate-project ipdb
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ipdb
HUMAN_VERSION =			0.13.13
COMPONENT_SUMMARY =		ipdb - IPython-enabled pdb
COMPONENT_PROJECT_URL =		https://github.com/gotcha/ipdb
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3d/1b/7e07e7b752017f7693a0f4d41c13e5ca29ce8cbcfdcc1fd6c4ad8c0a27a0/ipdb-0.13.13.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e3ac6018ef05126d442af680aad863006ec19d02290561ac88b8b1c0b0cfc726
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	COPYING.txt

# We need to force setup.py test style because automatically detected pytest
# test style does not work properly.
TEST_STYLE = setup.py

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/decorator
PYTHON_REQUIRED_PACKAGES += library/python/ipython
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
