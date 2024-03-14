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
#   $WS_TOOLS/python-integrate-project pycmd
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pycmd
HUMAN_VERSION =			1.2
COMPONENT_SUMMARY =		pycmd - pycmd: tools for managing/searching Python related files.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c1/ea/c73238007d9e57a513f39835a815c4aaaf3bdc9e1ee64fd3bdb6a616ecf9/pycmd-1.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:adc1976c0106919e9338db20102b91009256dcfec924a66928d7297026f72477
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing needs access to py.lookup and py.cleanup
COMPONENT_PRE_TEST_ACTION += $(LN) -s py.lookup-$(PYTHON_VERSION) $(PROTO_DIR)/usr/bin/py.lookup ;
COMPONENT_POST_TEST_ACTION += $(RM) $(PROTO_DIR)/usr/bin/py.lookup ;
COMPONENT_PRE_TEST_ACTION += $(LN) -s py.cleanup-$(PYTHON_VERSION) $(PROTO_DIR)/usr/bin/py.cleanup ;
COMPONENT_POST_TEST_ACTION += $(RM) $(PROTO_DIR)/usr/bin/py.cleanup ;
COMPONENT_TEST_ENV += PATH=$(PROTO_DIR)/usr/bin:$(PATH)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/py
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
