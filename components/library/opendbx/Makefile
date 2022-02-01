#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#
#
# Copyright 2022, Friedrich Kink. All rights reserved.
#

BUILD_BITS=             64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		opendbx
COMPONENT_VERSION=	1.4.6
COMPONENT_SUMMARY=	OpenDBX is an extremely lightweight but extensible database access library
COMPONENT_FMRI= 	library/$(COMPONENT_NAME)
COMPONENT_DESCRIPTION=	OpenDBX is an extremely lightweight but extensible database access \
			library written in C. It provides an abstraction layer to all supported \
			databases with a single, clean and simple interface that leads to an \
			elegant code design automatically. If you want your application to \
			support different databases with little effort, this is definitively \
			the right thing for you!
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:2246a03812c7d90f10194ad01c2213a7646e383000a800277c6fb8d2bf81497c
COMPONENT_PROJECT_URL=	https://www.linuxnetworks.de/doc/index.php?title=OpenDBX
COMPONENT_ARCHIVE_URL=	http://linuxnetworks.de/$(COMPONENT_NAME)/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2.1

# RPATH needed to make 'make REQUIRED_PACKAGES' happy
COMPONENT_POST_CONFIGURE_ACTION= \
        (cd $(@D) ; \
	$(GSED) -i -e 's:^LDFLAGS = .*:LDFLAGS = -m64 -Wl,-rpath=/usr/mariadb/10.3/lib/amd64:' backends/mysql/Makefile; \
	$(GSED) -i -e 's:^LDFLAGS = .*:LDFLAGS = -m64 -Wl,-rpath=/usr/postgres/12/lib/amd64:' backends/pgsql/Makefile )

CONFIGURE_OPTIONS+=	--enable-static=no
CONFIGURE_OPTIONS+=	--enable-rpath
CONFIGURE_OPTIONS+=	--with-backends="mysql odbc pgsql sqlite3"
CONFIGURE_OPTIONS+=	"CPPFLAGS=-I/usr/mariadb/10.3/include -I/usr/postgres/12/include -I/usr/include/odbc"
CONFIGURE_OPTIONS+=	"LIBS=-L/usr/mariadb/10.3/lib/amd64 -L/usr/postgres/12/lib/amd64"

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# manually added
REQUIRED_PACKAGES += database/mariadb-103/client
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/mariadb-103/library
REQUIRED_PACKAGES += database/postgres-12/library
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/unixodbc
REQUIRED_PACKAGES += system/library
