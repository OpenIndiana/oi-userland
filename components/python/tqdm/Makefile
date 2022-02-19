#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019-2020 Nona Hansel
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS=	NO_ARCH
BUILD_STYLE=	setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tqdm
COMPONENT_VERSION=	4.62.3
COMPONENT_SUMMARY=	Fast, extensible progress bar for Python and CLI
COMPONENT_PROJECT_URL=	https://github.com/tqdm/tqdm
COMPONENT_FMRI=		library/python/tqdm		
COMPONENT_CLASSIFICATION= Development/Python 
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_ARCHIVE_HASH= sha256:d359de7217506c9851b7869f3708d8ee53ed70a1b8edbba4dbcb47442592920d
COMPONENT_LICENSE=	MPLv2.0,MIT
COMPONENT_LICENSE_FILE=	LICENCE

PYTHON_VERSIONS=	3.7 3.9

# Tests are failing because numpy package cannot be build.
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTOUSRBINDIR); $(MV) tqdm tqdm-$(PYTHON_VERSION)) ;

#COMPONENT_TEST_DIR= $(SOURCE_DIR)
#COMPONENT_TEST_CMD= tox -e py$(PYV)

# Manually added test dependencies
REQUIRED_PACKAGES += library/python/tox

# Manually added dependencies
REQUIRED_PACKAGES += library/python/importlib-metadata-37
REQUIRED_PACKAGES += library/python/importlib-metadata-39

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
