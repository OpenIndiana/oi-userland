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
#   $WS_TOOLS/python-integrate-project pep440
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pep440
HUMAN_VERSION =			0.1.2
COMPONENT_SUMMARY =		pep440 - A simple package with utils to check whether versions number match PEP 440.
COMPONENT_PROJECT_URL =		https://github.com/Carreau/pep440
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/9c/9f/6934fbe88a573c91e4715ec2e6e346cf994460154dbc0d66db6a4096fa5d/pep440-0.1.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:58b37246cc2b13fee1ca2a3c092cb3704d21ecf621a5bdbb168e44e697f6d04d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Testing needs access to pep440 binary
COMPONENT_PRE_TEST_ACTION += $(LN) -s pep440-$(PYTHON_VERSION) $(PROTO_DIR)/usr/bin/pep440 ;
COMPONENT_POST_TEST_ACTION += $(RM) $(PROTO_DIR)/usr/bin/pep440 ;
COMPONENT_TEST_ENV += PATH=$(PROTO_DIR)/usr/bin:$(PATH)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
