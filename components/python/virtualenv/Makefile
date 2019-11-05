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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		virtualenv
COMPONENT_VERSION=	16.5.0
COMPONENT_FMRI=		library/python/virtualenv
COMPONENT_SUMMARY=	'A tool to create isolated Python environments'
COMPONENT_PROJECT_URL=	https://virtualenv.pypa.io/en/latest/
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:948df2d66849bdbf1207110b1bcc32f64e5e35257b76f8067392e3a2c08b3731
COMPONENT_ARCHIVE_URL=	https://github.com/pypa/virtualenv/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	virtualenv.license

PYTHON_VERSIONS=        2.7 3.4 3.5

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_TEST_DIR =	$(SOURCE_DIR)
COMPONENT_TEST_ARGS =	setup.py test

# Replace "#!/usr/bin/env ..." shebang lines with properly versioned ones.
COMPONENT_POST_INSTALL_ACTION += \
    $(FIND) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) -name *.py \
        -exec $(GSED) -i -e 's|env python|python$(PYTHON_VERSION)|' "{}" \; ;

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTOUSRBINDIR); $(MV) virtualenv virtualenv-$(PYTHON_VERSION)) ;

# this python module currently has no binary components, so all
# targets are *_NO_ARCH
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
