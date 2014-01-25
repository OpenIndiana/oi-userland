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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	psycopg2
COMPONENT_VERSION= 	2.5.2
COMPONENT_SUMMARY= 	Python-PostgreSQL Database Adapter
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:50382d8703a16c3c615f328c2676f002787095925c99f0afb125a59962a5bd2e
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/source/p/psycopg2/$(COMPONENT_ARCHIVE)#md5=1b433f83d50d1bc61e09026e906d84c7
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/psycopg2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# Don't depend on host default pg_config
PATH=           $(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

LDFLAGS+=   -L$(PG_LIBDIR.$(BITS))   -R$(PG_LIBDIR.$(BITS))
COMPONENT_BUILD_ENV     +=      LDFLAGS="$(LDFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)
