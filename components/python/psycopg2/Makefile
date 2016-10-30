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
# Copyright 2016 Alexander Pyhalov
# Copyright 2015, PALO Richard.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	psycopg2
COMPONENT_VERSION= 	2.6.2
COMPONENT_SUMMARY= 	Python-PostgreSQL Database Adapter
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:70490e12ed9c5c818ecd85d185d363335cc8a8cbf7212e3c185431c79ff8c05c
COMPONENT_ARCHIVE_URL= \
	https://pypi.python.org/packages/7b/a8/dc2d50a6f37c157459cd18bab381c8e6134b9381b50fbe969997b2ae7dbc/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/psycopg2

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# Don't depend on host default pg_config
PATH=           $(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

LDFLAGS+=   -L$(PG_LIBDIR.$(BITS))   -R$(PG_LIBDIR.$(BITS))
COMPONENT_BUILD_ENV     +=      LDFLAGS="$(LDFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test:	$(NO_TESTS)

REQUIRED_PACKAGES += database/postgres-93/library
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
