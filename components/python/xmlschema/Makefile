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
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS= NO_ARCH
BUILD_STYLE= setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         xmlschema
COMPONENT_VERSION=      1.9.2
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=		The xmlschema library is an implementation of XML Schema for Python
COMPONENT_PROJECT_URL=  https://pypi.org/project/xmlschema/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= 
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_FMRI=			library/python/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=		MIT

PYTHON_VERSIONS=	3.7 3.9

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Add python-version for binaries
COMPONENT_POST_INSTALL_ACTION = ( \
	cd $(PROTO_DIR)/usr/bin ; \
	for file in xmlschema-json2xml xmlschema-validate xmlschema-xml2json; do \
		$(MV) $$file $$file-$(PYTHON_VERSION); \
	done )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
