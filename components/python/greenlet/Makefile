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
#   $WS_TOOLS/python-integrate-project greenlet
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		greenlet
HUMAN_VERSION =			3.0.3
COMPONENT_SUMMARY =		greenlet - Lightweight in-process concurrent programming
COMPONENT_PROJECT_URL =		https://greenlet.readthedocs.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/17/14/3bddb1298b9a6786539ac609ba4b7c9c0842e12aa73aaa4d8d73ec8f8185/greenlet-3.0.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:43374442353259554ce33599da8b692d5aa96f8976d567d4badf263371fbe491
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Replace Python version in include file paths
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's|\(usr/include/python\)3.[0-9]\{1,\}/|\1$$(PYVER)/|' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/objgraph
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
