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
COMPONENT_VERSION= 	2.7.3.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	Python-PostgreSQL Database Adapter
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:9b7b16e26448b43cf167f785d8b5345007731ebf153a510e12dae826800caa65
COMPONENT_ARCHIVE_URL= \
	https://pypi.python.org/packages/6b/fb/15c687eda2f925f0ff59373063fdb408471b4284714a7761daaa65c01f15/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/psycopg2

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# Don't depend on host default pg_config
PATH=           $(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

LDFLAGS+=   -L$(PG_LIBDIR.$(BITS))   -R$(PG_LIBDIR.$(BITS))
COMPONENT_BUILD_ENV     +=      LDFLAGS="$(LDFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test:	$(NO_TESTS)

REQUIRED_PACKAGES += database/postgres-94/library
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
