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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freetds
COMPONENT_VERSION=	1.00.6
IPS_COMPONENT_VERSION=	1.0.6
COMPONENT_PROJECT_URL=	http://www.freetds.org/
COMPONENT_SUMMARY=	FreeTDS command-line utilities
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:b59cf0b48ea53095657a99583b853205df4e9dc295119cfbf4b1cdc0da9ba828
COMPONENT_ARCHIVE_URL=	ftp://ftp.freetds.org/pub/freetds/stable/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		database/freetds
COMPONENT_LICENSE=	LGPLv2
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

LDFLAGS += -lsocket -lnsl
CFLAGS += -I/usr/include/odbc

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

CONFIGURE_BINDIR.32 =   $(CONFIGURE_PREFIX)/bin/$(MACH32)

COMPONENT_POST_INSTALL_ACTION= \
	(cd $(PROTOUSRDIR) ;  \
	 $(MV) include/tds_sysdep_public.h include/tds_sysdep_public-$(BITS).h )

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += system/library
