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
#   $WS_TOOLS/python-integrate-project mysqlclient
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mysqlclient
HUMAN_VERSION =			2.2.0
COMPONENT_SUMMARY =		mysqlclient - Python interface to MySQL
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/de/9c/b176826e8994551ce826404dab97e305a4bb76c8b0a4e016fabda2901c71/mysqlclient-2.2.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:04368445f9c487d8abb7a878e3d23e923e6072c04a6c320f9e0dc8a82efba14e
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Force needed rpath
LD_OPTIONS += -R$(MYSQL_LIBDIR)

# We need to make sure Python will not found modules distributed with source
# package because there is missing compiled library.
COMPONENT_TEST_DIR = $(@D)/tests

# https://github.com/PyMySQL/mysqlclient/issues/628
PYTEST_ADDOPTS += -p no:mypy

#
# Note:
#
# To test we need to fulfill following prerequisites:
#	1) the default system mysql/mariadb version must match the version we
#	   built mysqlclient for,
#	2) the mariadb service must be running,
#	3) the (default) test database must exist.
#
# To check 1) and 2) you can run following commands:
#	gmake print-value-MYSQL_VERSION
#	pkg mediator mysql
#	svcs '*mariadb*'
#

# Manually added build and testing dependencies
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)
TEST_REQUIRED_PACKAGES += $(MYSQL_BASEPKG)

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
