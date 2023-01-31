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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		greenlet
HUMAN_VERSION =			2.0.2
COMPONENT_SUMMARY =		greenlet - Lightweight in-process concurrent programming
COMPONENT_PROJECT_URL =		https://greenlet.readthedocs.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/1e/1e/632e55a04d732c8184201238d911207682b119c35cecbb9a573a6c566731/greenlet-2.0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e7c8dc13af7db097bed64a051d2dd49e9f0af495c26995c00a9ee842690d34c0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Make sure include files are included in right packages
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's|^.*usr/include/python\(3.[0-9]*\)[^0-9]|$$(PYTHON_\1_ONLY)&|'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/objgraph
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/sphinx
