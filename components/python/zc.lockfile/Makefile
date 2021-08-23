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
# Copyright 2018 Alexander Pyhalov
#

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zc.lockfile
COMPONENT_VERSION=	2.0
COMPONENT_SUMMARY=	Basic inter-process locks
COMPONENT_PROJECT_URL=	https://pypi.org/project/zc.lockfile/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:307ad78227e48be260e64896ec8886edc7eae22d8ec53e4d528ab5537a83203b
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/zc.lockfile
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_LICENSE=	ZPL2.1
COMPONENT_LICENSE_FILE=	LICENSE.txt

PYTHON_VERSIONS=	$(PYTHON_VERSIONS_ALL)

TEST_TARGET=$(NO_TEST)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
