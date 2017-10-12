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

COMPONENT_NAME= 	pgpool-II
COMPONENT_VERSION= 	3.6.6
COMPONENT_SUMMARY= 	pgpool-II middle ware
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:5fbdac14a07b4f4cabef8bd224be1fbb0770d9aa4731d8fa7905878dc4c22fbc
COMPONENT_ARCHIVE_URL= \
  http://www.pgpool.net/download.php?f=$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pgpool.net/
COMPONENT_FMRI=	database/postgres/pgpool-II
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -D__EXTENSIONS__

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_BINDIR.64 =   $(CONFIGURE_PREFIX)/bin
# Earlier all binaries were delivered in /usr/bin,
# preserve this behavior
CONFIGURE_SBINDIR.64 =   $(CONFIGURE_PREFIX)/bin

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS	+=	--sysconfdir=/etc/pgpool-II

COMPONENT_POST_BUILD_ACTION += $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) -C $(BUILD_DIR_$(BITS))/doc/src/sgml man1 man8

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)/usr/share/man && \
	$(CP) -r $(BUILD_DIR_$(BITS))/doc/src/sgml/man[18] \
		$(PROTO_DIR)/usr/share/man

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += data/docbook/dtds
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
