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
# Copyright (c) 2014, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		heat
COMPONENT_CODENAME=	mitaka
COMPONENT_VERSION=	6.0.0
COMPONENT_BE_VERSION=	2016.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b89f14dc2421b94f8c322557b93959e2b6aa3dcc9cf739ef392f5f30c326b6e5
COMPONENT_ARCHIVE_URL=	https://tarballs.openstack.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/heat

TPNO=			30355

PKG_VARS +=		COMPONENT_BE_VERSION

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
# OpenStack Mitaka requires OVS and RAD changes not present in 11.3
BUILD_BITS=NO_ARCH
include $(WS_MAKE_RULES)/no-evaluation.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.7

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

#
# heat-api-cfn, heat-api-cloudwatch, heat-api, and heat-engine depend
# on heat-db and heat-upgrade so copy all of the service manifests
# into the proto directory for pkgdepend(1) to find.
#
COMPONENT_POST_INSTALL_ACTION += \
    ($(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
     $(CP) \
	 files/heat-api-cfn.xml \
	 files/heat-api-cloudwatch.xml \
	 files/heat-api.xml \
	 files/heat-db.xml \
	 files/heat-engine.xml \
	 files/heat-upgrade.xml \
	 $(PROTO_DIR)/lib/svc/manifest/application/openstack)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

# tests require mox, discover, testtools, testrepository,
# testscenarios, sphinx and oslo.sphinx some of which have not yet
# integrated
test:		$(NO_TESTS)

system-test:	$(NO_TESTS)

REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/iniparse-27
REQUIRED_PACKAGES += library/python/oslo.concurrency-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.i18n-27
REQUIRED_PACKAGES += library/python/oslo.log-27
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += library/python/sqlalchemy-migrate-27
REQUIRED_PACKAGES += system/core-os
