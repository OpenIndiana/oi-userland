#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Till Wegmueller
# Copyright 2021 Nona Hansel
#

BUILD_BITS=						NO_ARCH
BUILD_STYLE=					setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=				salt
COMPONENT_VERSION=		2019.2.8
COMPONENT_SUMMARY=		Portable, distributed, remote execution and configuration management system
COMPONENT_PROJECT_URL=		http://saltstack.com
COMPONENT_FMRI=				system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_SRC=          	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://github.com/saltstack/salt/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:26fcc34fe613532ec8fed668879159d91cdb01c5e84f65331067eeac9031c74f
COMPONENT_LICENSE=				Apache License 2.0
COMPONENT_LICENSE_FILE=		LICENSE

PYTHON_VERSIONS=		3.7

TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += SUNWcs
