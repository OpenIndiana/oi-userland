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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
# Copyright 2023 Klaus Ziegler
#

USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgadmin3
COMPONENT_VERSION= 	1.23
COMPONENT_SUMMARY= 	pgAdminIII administration and development GUI for PostgreSQL
COMPONENT_SRC= 		pgadmin3-lts-master-20220717
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4237b54f98316367a2474631bfe7d60f84c5d5e0339c549e64fdf4f02706f009
COMPONENT_ARCHIVE_URL= \
  https://github.com/allentc/pgadmin3-lts/archive/refs/tags/master-20220717.tar.gz
COMPONENT_PROJECT_URL = https://www.pgadmin.org

LDFLAGS+=   -L$(PG_LIBDIR)   -R$(PG_LIBDIR)
LDFLAGS+=   -lsocket -lnsl

CONFIGURE_OPTIONS += --with-pgsql=$(PG_HOME)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= (cd $(SOURCE_DIR); bash bootstrap)

COMPONENT_BUILD_ENV+= LDFLAGS="$(LDFLAGS)"

# build dependencies.
REQUIRED_PACKAGES += library/python/sphinx

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
