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
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pgbouncer
COMPONENT_VERSION= 	1.20.1
COMPONENT_SUMMARY= 	pgBouncer connection pooler
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:24992cf557d73426d7048698dffc7b019e6364d4d8757ae2cf5e2471286a2088
COMPONENT_ARCHIVE_URL=	https://pgbouncer.github.io/downloads/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.pgbouncer.org/
COMPONENT_FMRI=	database/postgres/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYRIGHT

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CLONEY_ARGS= CLONEY_MODE="hardlink"

CONFIGURE_OPTIONS += --with-openssl=$(OPENSSL_PREFIX)
CONFIGURE_ENV +=	"XMLTO=xmlto --skip-validation"

# Build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libcares
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
