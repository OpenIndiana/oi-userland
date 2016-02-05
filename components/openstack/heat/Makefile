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
COMPONENT_CODENAME=	kilo
COMPONENT_VERSION=	2015.1.2
COMPONENT_BE_VERSION=	2015.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5cf5dab1496304d81b060f1ce58f0c2d36a91c5a3305a4f91ec3057ac229d6ae
COMPONENT_ARCHIVE_URL=	http://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/heat
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)

TPNO=			25786

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.7

PKG_MACROS +=		COMPONENT_BE_VERSION=$(COMPONENT_BE_VERSION)
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

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/iniparse-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.i18n-27
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += library/python/sqlalchemy-migrate-27
REQUIRED_PACKAGES += system/core-os
