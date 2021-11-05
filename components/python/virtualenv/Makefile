#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2019 Tim Mooney
# Copyright (c) 2021 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		virtualenv
COMPONENT_VERSION=	20.10.0
COMPONENT_FMRI=		library/python/virtualenv
COMPONENT_SUMMARY=	A tool to create isolated Python environments
COMPONENT_PROJECT_URL=	https://virtualenv.pypa.io/en/latest/
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:576d05b46eace16a9c348085f7d0dc8ef28713a2cabaa1cf0aea41e8f12c9218
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE=	MIT

PYTHON_VERSIONS=	$(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

# Tests don't work successfully yet.
COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_CMD=		tox-3.9

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_POST_INSTALL_ACTION += \
    $(FIND) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) -name *.py \
        -exec $(GSED) -i -e 's|env python|python$(PYTHON_VERSION)|' "{}" \; ;

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTOUSRBINDIR); $(MV) virtualenv virtualenv-$(PYTHON_VERSION)) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
