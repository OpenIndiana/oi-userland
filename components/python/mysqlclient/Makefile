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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mysqlclient
HUMAN_VERSION =			2.1.1
COMPONENT_SUMMARY =		mysqlclient - Python interface to MySQL
COMPONENT_PROJECT_URL =		https://github.com/PyMySQL/mysqlclient
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/50/5f/eac919b88b9df39bbe4a855f136d58f80d191cfea34a3dcf96bf5d8ace0a/mysqlclient-2.1.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:828757e419fb11dd6c5ed2576ec92c3efaa93a0f7c39e263586d1ee779c3d782
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Do not depend on host default MySQL
COMPONENT_BUILD_ENV += PATH=$(MYSQL_BINDIR):$(PATH)
COMPONENT_INSTALL_ENV += PATH=$(MYSQL_BINDIR):$(PATH)

# Force needed rpath
LD_OPTIONS += -R$(MYSQL_LIBDIR)

# We need to make sure Python will not found modules distributed with source
# package because there is missing compiled library.
COMPONENT_TEST_DIR = $(@D)/tests

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
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
