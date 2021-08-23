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
# Copyright 2013 Aurelien Larcher.  All rights reserved.
# Copyright 2021 Nona Hansel.  All rights reserved.
#

BUILD_BITS=			NO_ARCH
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	Pyro4
COMPONENT_VERSION= 	4.80
COMPONENT_REVISION=	1
COMPONENT_IPS_NAME=	pyro4
COMPONENT_FMRI= 	library/python/$(COMPONENT_IPS_NAME)
COMPONENT_SUMMARY= 	Distributed object middleware for Python (RPC)
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:46847ca703de3f483fbd0b2d22622f36eff03e6ef7ec7704d4ecaa3964cb2220
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/P/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://github.com/irmen/Pyro4
COMPONENT_LICENSE_FILE=	$(COMPONENT_IPS_NAME).license

PYTHON_VERSIONS=	$(PYTHON_VERSIONS_ALL)

# Running tests need tox what we don't have yet:
TEST_TARGET=	$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Manually add dependencies
#REQUIRED_PACKAGES += library/python/serpent-27	# serpent-27 is not available anymore
REQUIRED_PACKAGES += library/python/serpent-35
REQUIRED_PACKAGES += library/python/serpent-37
REQUIRED_PACKAGES += library/python/serpent-39

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
