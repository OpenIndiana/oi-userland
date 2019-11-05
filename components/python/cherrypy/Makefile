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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		CherryPy
# This is the last version with Python 2.7 support
COMPONENT_VERSION=	17.3.0
COMPONENT_SUMMARY=	'Pythonic, object-oriented HTTP framework'
COMPONENT_PROJECT_URL=	http://www.cherrypy.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c3e4d76232ade4c47666b9008f92556465df517b8dca833ece3bed027028ae7d
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=		library/python/cherrypy
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE.md

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_INSTALL_ACTION = \
	(cd $(PROTO_DIR)/usr/bin ; $(MV) -f cherryd cherryd-$(PYTHON_VERSION))

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/cherrypy/test
COMPONENT_TEST_CMD =    nosetests-$(PYTHON_VERSION) -s $(SOURCE_DIR)/cherrypy/test
COMPONENT_TEST_ARGS =	-v

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

# Test requirements
REQUIRED_PACKAGES += library/python/nose-27
REQUIRED_PACKAGES += library/python/nose-34
REQUIRED_PACKAGES += library/python/nose-35

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/six-34
REQUIRED_PACKAGES += library/python/six-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
