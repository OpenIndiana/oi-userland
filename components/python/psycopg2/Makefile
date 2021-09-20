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

BUILD_STYLE=	setup.py
BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	psycopg2
COMPONENT_VERSION= 	2.9.1
COMPONENT_SUMMARY= 	Python-PostgreSQL Database Adapter
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:de5303a6f1d0a7a34b9d40e4d3bef684ccc44a49bbe3eb85e3c0bffb4a131b7c
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/psycopg2
COMPONENT_FMRI=		library/python/psycopg2
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	LGPLv3

PYTHON_VERSIONS=	3.7 3.9

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Don't depend on host default pg_config
PATH				=	$(PG_BINDIR.$(BITS)):$(PATH.illumos)

LDFLAGS 			+=	-L$(PG_LIBDIR.$(BITS)) -R$(PG_LIBDIR.$(BITS))
COMPONENT_BUILD_ENV	+=	LDFLAGS="$(LDFLAGS)"

# Manually added build dependencies
REQUIRED_PACKAGES	+= $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
