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

COMPONENT_NAME= pgbouncer
COMPONENT_VERSION= 	1.5.4
COMPONENT_SUMMARY= 	pgBouncer connection pooler
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:08040482f4c887e14d8c8c46fab838fff640c0f3cf231f86ad7f766b7a292280
COMPONENT_ARCHIVE_URL= \
  http://pgfoundry.org/frs/download.php/3393/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pgfoundry.org/projects/pgbouncer

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))
CONFIGURE_ENV +=        "XMLTO=xmlto --skip-validation"

build: $(BUILD_32)

install: $(INSTALL_32)
