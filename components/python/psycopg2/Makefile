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

BUILD_STYLE=setup.py
BUILD_BITS=32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	psycopg2
COMPONENT_VERSION= 	2.8.4
COMPONENT_REVISION=	2
COMPONENT_SUMMARY= 	Python-PostgreSQL Database Adapter
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:f898e5cc0a662a9e12bde6f931263a1bbd350cfb18e1d5336a12927851825bb6
COMPONENT_ARCHIVE_URL= \
	$(call pypi_url)
COMPONENT_PROJECT_URL = https://pypi.python.org/pypi/psycopg2

PYTHON_VERSIONS=	2.7 3.5

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Don't depend on host default pg_config
PATH=           $(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

LDFLAGS+=   -L$(PG_LIBDIR.$(BITS))   -R$(PG_LIBDIR.$(BITS))
COMPONENT_BUILD_ENV     +=      LDFLAGS="$(LDFLAGS)"

REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
