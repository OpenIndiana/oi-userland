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

COMPONENT_NAME=         numpy
COMPONENT_VERSION=      1.26.4
COMPONENT_REVISION=     1
COMPONENT_FMRI=         library/python/numpy
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=      Fundamental package for scientific computing with Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:2a02aba9ed12e4ac4eb3ea9421c420301a0c6460d9830d74a9df87efa4912010
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_PROJECT_URL=  https://numpy.org/
COMPONENT_LICENSE=      NUMPY
COMPONENT_LICENSE_FILE= LICENSE.txt

include $(WS_MAKE_RULES)/common.mk
LD_OPTIONS      += -lm

PYTHON_ENV +=   CC="$(CC) $(CC_BITS)"
PYTHON_ENV +=   CXX="$(CXX) $(CC_BITS)"

# reset COMPONENT_INSTALL_ARGS. numpy does not generate dynamicly generated
# header/data files with --skip-build
COMPONENT_INSTALL_ARGS =
COMPONENT_INSTALL_ARGS +=       --root $(PROTO_DIR)
COMPONENT_INSTALL_ARGS +=       --install-lib=$(PYTHON_LIB)
COMPONENT_INSTALL_ARGS +=       --install-data=$(PYTHON_DATA)
COMPONENT_INSTALL_ARGS +=       --force

# .pyc files have to be recompiled after changing shebang path
COMPONENT_POST_INSTALL_ACTION += \
	for file in $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/numpy/*.py ; do \
	$(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' $$file ; \
	done; \
	for file in $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/numpy/*/*.py ; do \
	$(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' $$file ; \
	done; \
	for file in $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages/numpy/*/*/*.py ; do \
	$(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' $$file ; \
	done; \
	$(PYTHON) -m compileall $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages

# Build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cython

# Test dependencies
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
