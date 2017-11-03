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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pgbouncer
COMPONENT_VERSION= 	1.7.2
COMPONENT_REVISION=	3
COMPONENT_SUMMARY= 	pgBouncer connection pooler
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:de36b318fe4a2f20a5f60d1c5ea62c1ca331f6813d2c484866ecb59265a160ba
COMPONENT_ARCHIVE_URL= \
  https://pgbouncer.github.io/downloads/files/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://pgfoundry.org/projects/pgbouncer
COMPONENT_FMRI=	database/postgres/pgbouncer
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	BSD

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))
CONFIGURE_ENV +=        "XMLTO=xmlto --skip-validation"

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += database/postgres-94/developer
REQUIRED_PACKAGES += library/libevent
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
