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
# Copyright 2017 Predrag Zečević
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bzr
COMPONENT_VERSION=	2.7.0
COMPONENT_VERSION_BASE=	2.7
COMPONENT_PROJECT_URL=	http://bazaar.canonical.com/
COMPONENT_SUMMARY=	Bazaar is a version control system that helps you track project history over time and to collaborate easily with others.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:0d451227b705a0dd21d8408353fe7e44d3a5069e6c4c26e5f146f1314b8fdab3
# https://launchpad.net/bzr/2.7/2.7.0/+download/bzr-2.7.0.tar.gz
COMPONENT_ARCHIVE_URL=	https://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_VERSION_BASE)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/versioning/bzr
COMPONENT_CLASSIFICATION=	Development/Source Code Management
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_LICENSE=	GPLv2

# Does not compile with 3.4 yet
PYTHON_VERSIONS=        2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_FETCH_USER_AGENT=wget

build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(NO_TEST)

REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/import-profiler-27
REQUIRED_PACKAGES += runtime/python-27
