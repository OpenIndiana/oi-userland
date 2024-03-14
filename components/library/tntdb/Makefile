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
# Copyright 2016 Jim Klimov
# Copyright 2022 Friedrich Kink
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         tntdb
COMPONENT_VERSION=      1.4
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      C++ library to access SQL databases, easy and robust
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:48cefd354acf2579c80b77d789d67f8b8162f1a02a3c2fb8157a9a32dc332859
COMPONENT_PROJECT_URL=  https://web.archive.org/web/20230309070315/http://www.tntnet.org/tntdb.html
COMPONENT_ARCHIVE_URL=  https://web.archive.org/web/20230309070345/http://www.tntnet.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

TEST_TARGET= $(NO_TESTS)

CFLAGS +=	$(CPP_LARGEFILES)
CXXFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_LARGEFILES)

# We use a fixed default mysql and postgres implementation+version as defined
# in `make-rules/*.mk` files included above
PATH=$(MYSQL_BINDIR.64):$(PG_BINDIR.64):$(PATH.gnu)

COMPONENT_POST_CONFIGURE_ACTION+= ( $(GSED) -i -e 's:$(MYSQL_LIBDIR):$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR):' $(@D)/src/mysql/Makefile; );
COMPONENT_POST_CONFIGURE_ACTION+= ( $(GSED) -i -e 's:$(PG_LIBDIR):$(PG_LIBDIR) -R$(PG_LIBDIR):' $(@D)/src/postgresql/Makefile; );

COMPONENT_COMMON_ENV += PATH="$(PATH)"
COMPONENT_COMMON_ENV += CC="$(CC)"
COMPONENT_COMMON_ENV += CXX="$(CXX)"
COMPONENT_COMMON_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

CONFIGURE_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ENV += $(COMPONENT_COMMON_ENV)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-mysql=yes
CONFIGURE_OPTIONS += --with-postgresql=yes
CONFIGURE_OPTIONS += --with-replicate=yes
CONFIGURE_OPTIONS += --with-oracle=no

# We need mysql_config delivered by (mariadb-101|mysql|percona)/client :
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
# We need pg_config :
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/cxxtools
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
