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
HUMAN_VERSION =			23.0.1
COMPONENT_SUMMARY =		pip - The PyPA recommended tool for installing Python packages.
COMPONENT_PROJECT_URL =		https://pip.pypa.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/6b/8b/0b16094553ecc680e43ded8f920c3873b01b1da79a54274c98f08cb29fca/pip-23.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cd015ea1bfb0fcef59d8a286c1f8bebcb983f6317719d415dc5351efb7cd7024
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# https://github.com/pypa/pip/issues/11824
TEST_STYLE = none

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
