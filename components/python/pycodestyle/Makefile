#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2013, 2020, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pycodestyle
COMPONENT_VERSION=	2.5.0
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_FMRI=		library/python/pycodestyle
COMPONENT_SUMMARY=	pycodestyle - Python style guide checker
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://pycodestyle.readthedocs.io/en/latest/ 
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e40a936c9a450ad81df37f549d676d127b1b66000a6c500caa2b085bc0ca976c
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	2.7 3.5 3.7 3.9

include $(WS_MAKE_RULES)/common.mk

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_PRE_BUILD_ACTION = \
	/usr/bin/find $(SOURCE_DIR) -name *.py \
		-exec $(GSED) -i -e 's/env python/python$(PYTHON_VERSION)/' "{}" \; ;

# Put the correct pycodestyle version number on the .TH line in the man page in
# the proto area.
COMPONENT_POST_INSTALL_ACTION += \
	($(MKDIR) $(PROTO_DIR)/usr/share/man/man1; \
	$(GSED) -e 's/XXX/$(COMPONENT_VERSION)/' \
	    $(COMPONENT_DIR)/files/pycodestyle.1 > \
	    $(PROTO_DIR)/usr/share/man/man1/pycodestyle.1);

# Copy and compile pep8 file for backward compatibility
COMPONENT_POST_INSTALL_ACTION += \
	($(CP) files/pep8.py $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/pep8.py ; \
	$(PYTHON) -m compileall $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/pep8.py);

COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTOUSRBINDIR)/pycodestyle $(PROTOUSRBINDIR)/pycodestyle-$(PYTHON_VERSION)

# Master test results are the same for all versions of Python, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS = "-n -e '/^testsuite/p'"

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

COMPONENT_SYSTEM_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_SYSTEM_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_SYSTEM_TEST_ENV =
COMPONENT_SYSTEM_TEST_ARGS =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
