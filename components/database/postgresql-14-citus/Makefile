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
# Copyright 2019 Alexander Pyhalov
# Copyright 2022 Marco van Wieringen
#

PG_VERSION= 14
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= citus
COMPONENT_VERSION= 12.1.7
COMPONENT_SUMMARY= Citus Open Source PostgreSQL extension
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:a1c0d093d65fcbc6786c79202391fe3a773db89f3929fd6aa52c35d57cce1a08
COMPONENT_ARCHIVE_URL= https://github.com/citusdata/citus/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL= https://www.citusdata.com/
COMPONENT_FMRI= database/postgres-$(PG_VERNUM)/citus
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_LICENSE= AGPLv3.0
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing needs to install some files
COMPONENT_TEST_ENV += DESTDIR=$(PROTO_DIR)

# Manually added dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += web/curl
