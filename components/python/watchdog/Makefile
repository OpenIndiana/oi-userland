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
#   $WS_TOOLS/python-integrate-project watchdog
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		watchdog
COMPONENT_VERSION =		2.1.9
COMPONENT_SUMMARY =		watchdog - Filesystem events monitoring
COMPONENT_PROJECT_URL =		https://github.com/gorakhargosh/watchdog
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/42/f7/da8e889f8626786eac9454e8d2718fc79359ed517be20cdd50c647167d39/watchdog-2.1.9.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:43ce20ebb36a51f21fa376f76d1d4692452b2527ccd601950d69ed36b9e21609
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# The following tests are Linux, macOS, or Windows specific and cause testsuite failure
COMPONENT_PRE_TEST_ACTION = $(RM) \
	$(SOURCE_DIR)/tests/test_fsevents.py \
	$(SOURCE_DIR)/tests/test_inotify_buffer.py \
	$(SOURCE_DIR)/tests/test_inotify_c.py \
	$(SOURCE_DIR)/tests/test_observers_winapi.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib_metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
