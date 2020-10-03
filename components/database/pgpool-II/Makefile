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

BUILD_BITS=64

COMPONENT_NAME= 	pgpool-II
COMPONENT_VERSION= 	4.1.4
COMPONENT_SUMMARY= 	pgpool-II middle ware
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:b793d516e21653e08b821af4816f69db262d876d9876372e9aa4f4539e1b6bb5
COMPONENT_ARCHIVE_URL= \
	https://www.pgpool.net/download.php?f=$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pgpool.net/
COMPONENT_FMRI=	database/postgres/pgpool-II
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/common.mk

CFLAGS += -D__EXTENSIONS__

COMPONENT_PREP_ACTION =        (cd $(SOURCE_DIR) && autoreconf -fi )
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

# Build dependencies
REQUIRED_PACKAGES += data/docbook/dtds
REQUIRED_PACKAGES += developer/documentation-tool/openjade

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
