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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ansible
COMPONENT_VERSION=	2.7.5
COMPONENT_SUMMARY=	'Ansible is a radically simple IT automation system'
COMPONENT_PROJECT_URL=	https://ansible.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:aaf9e1974bd12840ca055ac156f37601c08d73d726a3a6b98a2fe759a57051bb
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR =    $(COMPONENT_SRC)/tests
COMPONENT_TEST_CMD =    $(PYTHON) /usr/bin/py.test-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS =

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(TEST_NO_ARCH)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += runtime/python-27
