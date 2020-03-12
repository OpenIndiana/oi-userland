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
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	barman
COMPONENT_VERSION= 	2.9
COMPONENT_SUMMARY= 	An administration tool for disaster recovery of PostgreSQL servers 
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:16cb4ad4bfc5d3fc5197bf70b40bf4390fe5081391ee11d853154cee3b4a6e0c
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/pgbarman/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pgbarman.org/

PYTHON_VERSIONS=	3.5

TEST_TARGET=$(NO_TESTS)

include $(WS_TOP)/make-rules/common.mk

COMPONENT_POST_INSTALL_ACTION += \
	cd $(PROTO_DIR)/usr/bin ; \
	for file in barman barman-wal-archive barman-wal-restore; do \
		mv $$file $$file-$(PYTHON_VERSION) ; \
	done ;

# Install example configuration files
DOC_DIR=$(PROTO_DIR)/usr/share/barman

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(DOC_DIR); \
	$(CP) $(SOURCE_DIR)/doc/barman.conf $(DOC_DIR)/barman.conf-example; \
	for file in $(SOURCE_DIR)/doc/barman.d/*.conf-template; do \
		$(CP) $$file $(DOC_DIR)/$$(basename $$file| $(GSED) -e 's:template:example:g'); \
	done

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-35
