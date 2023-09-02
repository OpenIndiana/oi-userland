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
# Copyright 2021 Nona Hansel
#

BUILD_STYLE= setup.py
OPENSSL_VERSION= 3.1
SINGLE_PYTHON_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			borgbackup
COMPONENT_VERSION=		1.2.6
COMPONENT_SUMMARY=		Deduplicating backup program with compression and authenticated encryption
COMPONENT_PROJECT_URL=	https://borgbackup.readthedocs.org/en/stable/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b7a6f8f086039eeec79070b914f3c651ed7f3612c965374af910d277c7a2139d
COMPONENT_ARCHIVE_URL=	https://github.com/borgbackup/borg/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			backup/borg
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)

COMPONENT_POST_INSTALL_ACTION = \
	$(GSED) -i "1s|python.*|python${PYTHON_VERSION}|" $(PROTO_DIR)/usr/bin/borg;

# Manually add build dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pkgconfig

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/lz4
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += system/library
