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

BUILD_STYLE= setup.py
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	psycopg2
COMPONENT_VERSION= 	2.9.4
COMPONENT_SUMMARY= 	Python-PostgreSQL Database Adapter
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d529926254e093a1b669f692a3aa50069bc71faf5b0ecd91686a78f62767d52f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/psycopg2
COMPONENT_FMRI=		library/python/psycopg2
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	LGPLv3

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Don't depend on host default pg_config
PATH= $(PG_BINDIR.$(BITS)):$(PATH.illumos)

LDFLAGS += -L$(PG_LIBDIR.$(BITS)) -R$(PG_LIBDIR.$(BITS))
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

# Manually added build dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
