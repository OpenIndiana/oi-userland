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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pg_repack
COMPONENT_VERSION= 	1.1.8
COMPONENT_SUMMARY= 	pg_repack - utility to reorganize PostgreSQL tables on-line
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).zip
COMPONENT_COMMIT=       7487a775d5e95f26bbdd6c555b927dc19211de53
COMPONENT_ARCHIVE_HASH= \
  sha256:64a67d41db74f3a9152e4bab09845fdbec8d0f03c3fcc0292dbe4426f1420daa
COMPONENT_ARCHIVE_URL= \
  https://github.com/reorg/pg_repack/archive/$(COMPONENT_COMMIT).zip
COMPONENT_PROJECT_URL = http://reorg.github.io/pg_repack/

PG_VERSION=	9.3
# Don't depend on host default pg_config
PATH=		$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_BUILD_ENV	+=	USE_PGXS=0

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
