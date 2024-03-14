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
#   $WS_TOOLS/python-integrate-project ply
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ply
HUMAN_VERSION =			3.11
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		ply - Python Lex & Yacc
COMPONENT_PROJECT_URL =		http://www.dabeaz.com/ply/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e5/69/882ee5c9d017149285cab114ebeab373308ef0f874fcdac9beb90e0ac4da/ply-3.11.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:00c7c1aaa88358b9c765b6d3000c6eec0ba42abca5351b095321aef446081da3
COMPONENT_LICENSE =		BSD-3-Clause

# This project uses custom testing.  See $(SOURCE_DIR)/test/README.
TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# Custom testing
COMPONENT_TEST_DIR = $(@D)/test
COMPONENT_TEST_CMD = $(PYTHON) testlex.py ; $(PYTHON) testyacc.py ; $(PYTHON) testcpp.py
COMPONENT_TEST_ARGS =
COMPONENT_TEST_TARGETS =
COMPONENT_POST_TEST_ACTION = cd $(COMPONENT_TEST_DIR) ; ./cleanup.sh

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
