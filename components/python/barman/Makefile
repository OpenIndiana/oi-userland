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
#   $WS_TOOLS/python-integrate-project barman
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		barman
HUMAN_VERSION =			3.11.1
COMPONENT_SUMMARY =		Backup and Recovery Manager for PostgreSQL
COMPONENT_PROJECT_URL =		https://www.pgbarman.org/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/EnterpriseDB/barman/archive/refs/tags/release/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:61a5d687a56b42c2a9adeb6dd3760d2654990f0760230c721cc8a73a910a9f0a
COMPONENT_LICENSE =		GPL-3.0-only
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI =		database/postgres/barman
COMPONENT_CLASSIFICATION =	System/Databases

# Github tarball use different source directory than sdist
COMPONENT_SRC =			barman-release-$(HUMAN_VERSION)

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Make sure man pages are installed at proper location
PYTHON_DATA=$(USRDIR)

# Install example configuration files
COMPONENT_POST_INSTALL_ACTION += \
	DOC_DIR=$(PROTO_DIR)/usr/share/barman ; \
	$(MKDIR) $$DOC_DIR ; \
	$(CP) $(SOURCE_DIR)/doc/barman.conf $$DOC_DIR/barman.conf-example ; \
	for file in $(SOURCE_DIR)/doc/barman.d/*.conf-template ; do \
		$(CP) $$file $$DOC_DIR/$$(basename $$file | $(GSED) -e 's:template:example:g') ; \
	done ;

# Install additional /etc files
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOETCSECDIR)/exec_attr.d ; \
	$(INSTALL) $(COMPONENT_DIR)/files/exec_attr $(PROTOETCSECDIR)/exec_attr.d/barman ; \
	$(INSTALL) -d $(PROTOETCSECDIR)/prof_attr.d ; \
	$(INSTALL) $(COMPONENT_DIR)/files/prof_attr $(PROTOETCSECDIR)/prof_attr.d/barman ; \
	$(INSTALL) -d $(PROTOETCDIR)/user_attr.d/prof_attr.d ; \
	$(INSTALL) $(COMPONENT_DIR)/files/user_attr $(PROTOETCDIR)/user_attr.d/barman ; \
	$(INSTALL) $(COMPONENT_DIR)/files/barman.conf $(PROTOETCDIR)/barman.conf ;

# Install additional man page
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOUSRSHAREMAN4DIR) ; \
	$(INSTALL) $(COMPONENT_DIR)/files/barman.conf.4 $(PROTOUSRSHAREMAN4DIR) ;

# We have no packages needed for cloud testing so we need to skip following tests
PYTEST_ADDOPTS += --ignore tests/test_barman_cloud_backup_show.py
PYTEST_ADDOPTS += --ignore tests/test_barman_cloud_wal_archive.py
PYTEST_ADDOPTS += --ignore tests/test_cloud.py
PYTEST_ADDOPTS += --ignore tests/test_cloud_snapshot_interface.py
PYTEST_ADDOPTS += --ignore tests/test_infofile.py
PYTEST_ADDOPTS += --ignore tests/test_output.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/psycopg2
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/py
TEST_REQUIRED_PACKAGES.python += library/python/pytest
