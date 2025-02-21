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
# Copyright (c) 2024, Friedrich Kink
#

BUILD_STYLE= waf
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=    talloc
COMPONENT_VERSION= 2.4.3
COMPONENT_SUMMARY= talloc is a hierarchical, reference counted memory pool system with destructors.
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:dc46c40b9f46bb34dd97fe41f548b0e8b247b77a918576733c528e83abd854dd
COMPONENT_ARCHIVE_URL= https://download.samba.org/pub/talloc/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://$(COMPONENT_NAME).samba.org/$(COMPONENT_NAME)/doc/html/index.html
COMPONENT_FMRI = library/talloc
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_LICENSE = LGPL

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	cd $(@D); \
	);

WAF = PYTHONHASHSEED=1 $(PYTHON) ./buildtools/bin/waf

CONFIGURE_OPTIONS += --disable-python

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^\#/p" ' \
	'-e "/^test /p" '\
	'-e "/^success/p" ' \
	'-e "/^failed/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
