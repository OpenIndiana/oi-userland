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
# Copyright 2024 Geoff Weiss
#

BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         scour
COMPONENT_VERSION=      0.38.2
COMPONENT_FMRI=         library/python/scour
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=      An SVG optimizer/cleaner written in Python that reduces the size of scalable vector graphics by optimizing structure and removing unnecessary data.
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:6881ec26660c130c5ecd996ac6f6b03939dd574198f50773f2508b81a68e0daf
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=  https://pypi.org/project/scour/
COMPONENT_LICENSE=      APACHE
COMPONENT_LICENSE_FILE= scour.license

# gmake test fails.  Source archive from pypi does not have the test_scour.py file
TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# tox.ini not included with archive from pypi.  Manaully add a copy found on scour github.
COMPONENT_PRE_INSTALL_ACTION += cp $(COMPONENT_DIR)/files/tox.ini $(COMPONENT_DIR)/build/amd64-$(PYTHON_VERSION)/tox.ini ; 

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_POST_INSTALL_ACTION += \
	for file in $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/scour/*.py ; do \
	$(GSED) -i 's/env\ python/python$(PYTHON_VERSION)/' $$file ; \
	done  ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/six
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/six
