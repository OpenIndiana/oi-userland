#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS=64
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		borgbackup
COMPONENT_VERSION=	1.1.14
COMPONENT_PROJECT_URL=	https://borgbackup.readthedocs.org/en/stable/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:7dbb0747cc948673f695cd6de284af215f810fed2eb2a615ef26ddc7c691edba
COMPONENT_ARCHIVE_URL=	https://github.com/borgbackup/borg/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		backup/borg
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	3.5

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_FETCH_USER_AGENT=wget

COMPONENT_POST_INSTALL_ACTION = \
	$(CP) $(PROTO_DIR)/usr/bin/borg  $(PROTO_DIR)/usr/bin/borg-$(PYTHON_VERSION); \
	$(GSED) -i "1s|python.*|python${PYTHON_VERSION}|" $(PROTO_DIR)/usr/bin/borg-$(PYTHON_VERSION); \
	$(RM) $(PROTO_DIR)/usr/bin/borg;

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
