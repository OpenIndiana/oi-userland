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

BUILD_STYLE= setup.py
SINGLE_PYTHON_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	barman
COMPONENT_VERSION= 	3.8.0
COMPONENT_SUMMARY= 	An administration tool for disaster recovery of PostgreSQL servers 
COMPONENT_PROJECT_URL=	https://pgbarman.org/
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2c9a1571047d90d885b962b8167630c7cda6a2b892d09c2779baa6bd49f484ac
COMPONENT_ARCHIVE_URL=	https://github.com/EnterpriseDB/barman/releases/download/release/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		database/postgres/barman
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	LICENSE

PKG_MACROS += PYVER=$(PYTHON_VERSION)
PKG_MACROS += PYV=$(shell echo $(PYTHON_VERSION) | tr -d .)

TEST_TARGET= $(NO_TESTS)
include $(WS_TOP)/make-rules/common.mk

# Install example configuration files
DOC_DIR= $(PROTO_DIR)/usr/share/barman

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(DOC_DIR); \
	$(CP) $(SOURCE_DIR)/doc/barman.conf $(DOC_DIR)/barman.conf-example; \
	for file in $(SOURCE_DIR)/doc/barman.d/*.conf-template; do \
		$(CP) $$file $(DOC_DIR)/$$(basename $$file| $(GSED) -e 's:template:example:g'); \
	done

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/argcomplete
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/psycopg2
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
