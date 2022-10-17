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
#   $WS_TOOLS/python-integrate-project nbformat
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		nbformat
COMPONENT_VERSION =		5.4.0
COMPONENT_SUMMARY =		nbformat - The Jupyter Notebook format
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2c/ed/ce3e63f5e757442cbb01ac45683fb0338d48f7e824606957d933bc831a58/nbformat-5.4.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:44ba5ca6acb80c5d5a500f1e5b83ede8cbe364d5a495c4c8cf60aaf1ba656501
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	COPYING.md

include $(WS_MAKE_RULES)/common.mk

# The line number of reported warning depends on python version
COMPONENT_TEST_TRANSFORMS +=	"-e 's/:[0-9]\{1,\}\(: UserWarning: nbformat\.current is deprecated\.\)$$/:LINE\1/'"
# Order of detailed test results could change with every run
COMPONENT_TEST_TRANSFORMS +=	"-e '/^  /,/^$$/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib_metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
