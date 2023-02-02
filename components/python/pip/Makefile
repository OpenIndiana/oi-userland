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
HUMAN_VERSION =			23.0
COMPONENT_SUMMARY =		pip - The PyPA recommended tool for installing Python packages.
COMPONENT_PROJECT_URL =		https://pip.pypa.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b5/16/5e24bf63cff51dcc169f43bd43b86b005c49941e09cc3482a5b370db239e/pip-23.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:aee438284e82c8def684b0bcc50b1f6ed5e941af97fa940e83e2e8ef1a59da9b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = setup.py

include $(WS_MAKE_RULES)/common.mk

# installer is unable to overwrite files in usr/bin
COMPONENT_PRE_INSTALL_ACTION += $(RM) $(PROTOUSRBINDIR)/pip$(PYTHON_VERSION) ;

# usr/bin/pip3.x needs to be handled separately because we have no generic
# rules covering it
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/\(usr\/bin\/pip\)3\.[0-9]\{1,\}$$/\1$$(PYVER)/' | uniq

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
