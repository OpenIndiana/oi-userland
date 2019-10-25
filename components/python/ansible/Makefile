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
# Copyright 2019 Michal Nowak
#

BUILD_BITS=		NO_ARCH
BUILD_STYLE=		setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ansible
COMPONENT_VERSION=	2.7.14
COMPONENT_SUMMARY=	'Ansible is a radically simple IT automation system'
COMPONENT_PROJECT_URL=	https://ansible.com/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:6a52f43b5e4446aa04f3907a750010fbbf41eb050cb726065c6c877ed3a98d02
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/common.mk

# https://docs.ansible.com/ansible/devel/dev_guide/testing_units.html
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_TEST_CMD=	ln -sf /usr/bin/pytest-$(PYTHON_VERSION) bin/pytest && bin/ansible-test units -v --python $(PYTHON_VERSION)
COMPONENT_TEST_ARGS=

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += runtime/python-27
