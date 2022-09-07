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
# Copyright 2022 erwinlem
#

BUILD_STYLE=setup.py
USE_COMMON_TEST_MASTER=no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		frozendict
COMPONENT_VERSION=	2.3.4
COMPONENT_SUMMARY=	An immutable dictionary 
COMPONENT_PROJECT_URL=	https://pypi.org/project/$(COMPONENT_NAME)
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH=	sha256:15b4b18346259392b0d27598f240e9390fafbff882137a9c48a1e0104fb17f78
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE.txt

PYTHON_VERSIONS=    3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_CMD =    $(PYTHON) -m pytest 
COMPONENT_TEST_ARGS =   test_frozendict.py
COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/test
COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9]*[0-9].[0-9][0-9]s/ X.XXs/" '
COMPONENT_TEST_TRANSFORMS += '-e "s/^Using --randomly-seed=[0-9]*/Using --randomly-seed=XXXXXXXXXX/" '

$(MANIFEST_BASE)-%.depend:	$(MANIFEST_BASE)-%.mangled
	sed -i 's/cpython-39.so/so/g' $(BUILD_DIR)/*.mangled
	$(PKGDEPEND) generate $(PKGDEPEND_GENERATE_OPTIONS) $< >$@

# Build dependencies

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
