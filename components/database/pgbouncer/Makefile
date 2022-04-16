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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS= 64
#USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pgbouncer
COMPONENT_VERSION= 	1.16.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	pgBouncer connection pooler
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:087477e9e4766d032b04b7b006c0c8d64160a54141a7bfc2c6e5ae7ae11bf7fc
COMPONENT_ARCHIVE_URL=	https://pgbouncer.github.io/downloads/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.pgbouncer.org/
COMPONENT_FMRI=	database/postgres/pgbouncer
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	BSD

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))
CONFIGURE_ENV +=        "XMLTO=xmlto --skip-validation"

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libcares
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += system/library
