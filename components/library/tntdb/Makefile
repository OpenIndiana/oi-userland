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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	tntdb
COMPONENT_VERSION=	1.3
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	C++ library to access SQL databases, easy and robust
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:093ab2694bc66bc05ae0a5c8a505d75ae84d4c35c2ddc0ff0283c5b9574b474b
COMPONENT_ARCHIVE_URL= \
  http://www.tntnet.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.tntnet.org/tntdb.html
COMPONENT_FMRI=	library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS +=	$(CPP_LARGEFILES)
CXXFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_LARGEFILES)

# We use a fixed default mysql and postgres implementation+version as defined
# in `make-rules/*.mk` files included above
PATH.64=$(USRBINDIR.64):$(USRBINDIR.32):$(GNUBIN.64):$(GNUBIN.32)
PATH.32=$(USRBINDIR.32):$(GNUBIN.32)
PATH=$(MYSQL_BINDIR.$(BITS)):$(PG_BINDIR.$(BITS)):$(PATH.$(BITS))

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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += $(MYSQL_BASEPKG)/library
# We need mysql_config delivered by (mariadb-101|mysql|percona)/client :
REQUIRED_PACKAGES += $(MYSQL_BASEPKG)/client
REQUIRED_PACKAGES += $(PG_BASEPKG)/library
# We need pg_config :
REQUIRED_PACKAGES += $(PG_BASEPKG)/developer
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/cxxtools
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
