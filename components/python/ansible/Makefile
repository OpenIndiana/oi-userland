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

BUILD_STYLE=	setup.py
BUILD_BITS=	NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ansible
COMPONENT_VERSION=	2.9.27
COMPONENT_SUMMARY=	Ansible is a radically simple IT automation system
COMPONENT_PROJECT_URL=	https://ansible.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:479159e50b3bd90920d06bc59410c3a51d3f9be9b4e1029e11d1e4a2d0705736
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSION=		3.7
PYTHON_VERSIONS=	3.7

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/test
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# Required for tests
REQUIRED_PACKAGES += library/python/hypothesis-37
REQUIRED_PACKAGES += library/python/mock-37
REQUIRED_PACKAGES += library/python/pluggy-37
REQUIRED_PACKAGES += library/python/py-37
REQUIRED_PACKAGES += library/python/pyparsing-37
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/sortedcontainers-37

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
