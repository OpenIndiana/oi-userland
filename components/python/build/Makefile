#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright 2020 OmniOS Community Edition (OmniOSce) Association.
#

BUILD_BITS=			64
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		build
COMPONENT_VERSION=	0.7.0
COMPONENT_SUMMARY=	A simple, correct PEP517 package builder
COMPONENT_PROJECT_URL=	https://pypi.org/project/build/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:1aaadcd69338252ade4f7ec1265e1a19184bf916d84c9b7df095f423948cb89f
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/build
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= LICENSE

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk	

COMPONENT_POST_INSTALL_ACTION= \
	cd $(PROTO_DIR)/usr/bin && $(MV) pyproject-build pyproject-build-$(PYTHON_VERSION)

# Build dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
