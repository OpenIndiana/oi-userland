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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgbadger
COMPONENT_VERSION= 	7.1
COMPONENT_SUMMARY= 	pgBadger PostgreSQL log analyzer
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:de7f36cb55d2c177fdf47115f3fb5c2e842b443432631212e408726baacbad7e
COMPONENT_ARCHIVE_URL= \
  https://github.com/dalibo/pgbadger/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = http://dalibo.github.io/pgbadger/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# Using makemaker.mk here is an overkill,
# because we don't need versioned  pgbadger
COMPONENT_PRE_BUILD_ACTION = ( cd $(BUILD_DIR_32) && $(PERL) Makefile.PL )

PKG_PROTO_DIRS += $(BUILD_DIR_32)

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
