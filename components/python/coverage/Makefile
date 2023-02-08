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
#   $WS_TOOLS/python-integrate-project coverage
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		coverage
HUMAN_VERSION =			7.2.1
COMPONENT_SUMMARY =		coverage - Code coverage measurement for Python
COMPONENT_PROJECT_URL =		https://github.com/nedbat/coveragepy
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/8d/4a/3518606d4b110df4f3e77bd52c241ae8a84c6dc74fac7c2a8e809449e541/coverage-7.2.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c77f2a9093ccf329dd523a9b2b3c854c20d2a3d968b6def3b820272ca6732242
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# installer is unable to overwrite files in usr/bin
COMPONENT_PRE_INSTALL_ACTION += $(RM) $(PROTOUSRBINDIR)/coverage-$(PYTHON_VERSION) ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/tomli
