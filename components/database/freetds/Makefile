#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freetds
COMPONENT_VERSION=	1.00.94
IPS_COMPONENT_VERSION=	1.0.94
COMPONENT_PROJECT_URL=	http://www.freetds.org/
COMPONENT_SUMMARY=	FreeTDS command-line utilities
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:5fcf59a554eb3e72a09cc49c8dba5db8ad6dced07315ed775c4b8b2b81b603e4
COMPONENT_ARCHIVE_URL=	ftp://ftp.freetds.org/pub/freetds/stable/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		database/freetds
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

LDFLAGS += -lsocket -lnsl
CFLAGS += -I/usr/include/odbc

CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-threadsafe
CONFIGURE_OPTIONS +=	--with-gnutls=$(CONFIGURE_PREFIX)/include/gnutls-3
CONFIGURE_OPTIONS +=	--with-unixodbc=$(CONFIGURE_PREFIX)

COMPONENT_POST_INSTALL_ACTION= \
	(cd $(PROTOUSRDIR) ;  \
	 $(MV) include/tds_sysdep_public.h include/tds_sysdep_public-$(BITS).h )

# Some tests require SQL server to talk to (which we don't have), so they
# fail in our case: http://www.freetds.org/userguide/confirminstall.htm#TESTS
COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/TOTAL|PASS|FAIL|XFAIL|SKIP|XPASS|ERROR/'"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
