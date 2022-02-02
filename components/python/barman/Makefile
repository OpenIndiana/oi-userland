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
# Copyright 2016 Alexander Pyhalov
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	barman
COMPONENT_VERSION= 	2.18
COMPONENT_SUMMARY= 	An administration tool for disaster recovery of PostgreSQL servers 
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1955a570922bce2cb8fc1a346e0b3e7bee1c366ca16a2e92b1811240d89de29f
COMPONENT_ARCHIVE_URL=	https://github.com/EnterpriseDB/barman/releases/download/release/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://pgbarman.org/
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_FMRI=		database/postgres/barman
COMPONENT_LICENSE=	GPLv3

PYTHON_VERSIONS=	3.9
PYTHON_VERSION=		3.9

TEST_TARGET=$(NO_TESTS)
include $(WS_TOP)/make-rules/common.mk

# Install example configuration files
DOC_DIR=$(PROTO_DIR)/usr/share/barman

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(DOC_DIR); \
	$(CP) $(SOURCE_DIR)/doc/barman.conf $(DOC_DIR)/barman.conf-example; \
	for file in $(SOURCE_DIR)/doc/barman.d/*.conf-template; do \
		$(CP) $$file $(DOC_DIR)/$$(basename $$file| $(GSED) -e 's:template:example:g'); \
	done

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-39
