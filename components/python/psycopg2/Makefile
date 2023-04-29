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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project psycopg2
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		psycopg2
HUMAN_VERSION =			2.9.6
COMPONENT_SUMMARY =		psycopg2 - psycopg2 - Python-PostgreSQL Database Adapter
COMPONENT_PROJECT_URL =		https://psycopg.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/af/c4/5726cddb53fe52f0e839eb3da04322364f14493217ebd5818cc5e4c948a5/psycopg2-2.9.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f15158418fd826831b28585e2ab48ed8df2d0d98f502a2b4fe619e7d5ca29011
COMPONENT_LICENSE =		LGPL-3.0-only

# see doc/src/install.rst
TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# Do not depend on host default pg_config
PATH := $(PG_BINDIR):$(PATH)

# force needed rpath
LD_OPTIONS += -R$(PG_LIBDIR)

#
# Note:
#
# To test we need to fulfill following prerequisites:
#	1) the default system postgres version must match the version we built
#	   psycopg2 for,
#	2) the postgresql service must be running,
#	3) the psycopg2_test database with plpgsql extension must exist.
#
# To check 1) and 2) you can run following commands:
#	gmake print-value-PG_VERSION
#	pkg mediator postgres
#	svcs '*postgresql*'
# To create the psycopg2_test database you could run:
#	su - postgres
#	createdb psycopg2_test
#	psql -c 'CREATE EXTENSION plpgsql;' psycopg2_test
#
# Testing will use the default 'postgres' user.
#
COMPONENT_TEST_ENV += PSYCOPG2_TESTDB_USER=postgres

# Custom test style - see doc/src/install.rst
COMPONENT_TEST_CMD =		$(PYTHON) -c "import tests; tests.unittest.main(defaultTest='tests.test_suite')"
COMPONENT_TEST_ARGS =		--verbose
COMPONENT_TEST_TARGETS =

# Manually added build and testing dependencies
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)
TEST_REQUIRED_PACKAGES += $(PG_SERVICE_PKG)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
