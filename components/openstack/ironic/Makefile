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

COMPONENT_NAME=		ironic
COMPONENT_CODENAME=	kilo
COMPONENT_VERSION=	2015.1.2
COMPONENT_BE_VERSION=	2015.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fd85246f7c9b0976a27b863de328f1240d43d4633511cd832e8d6904f6f4b06c
COMPONENT_ARCHIVE_URL=	http://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/ironic
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)

TPNO=			25789

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
# ironic-api and ironic-conductor depend on ironic-db and ironic-upgrade so
# copy all of the service manifests into the proto directory for
# pkgdepend(1) to find.
#
COMPONENT_POST_INSTALL_ACTION += \
	($(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
	 $(CP) \
	     files/ironic-api.xml \
	     files/ironic-conductor.xml \
	     files/ironic-db.xml \
	     files/ironic-upgrade.xml \
	     $(PROTO_DIR)/lib/svc/manifest/application/openstack/; \
	 $(MKDIR) $(PROTO_DIR)$(PYTHON_LIB)/ironic/drivers/modules; \
	 $(CP) \
	     files/drivers/solaris.py \
	     $(PROTO_DIR)$(PYTHON_LIB)/ironic/drivers/; \
	 $(CP) \
	     files/drivers/modules/solaris_ipmitool.py \
	     $(PROTO_DIR)$(PYTHON_LIB)/ironic/drivers/modules/; \
	 $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES))

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

#
# Tests require:
# hacking, coverage>=3.6, disvover, fixtures, oslo.test, psycopg2,
# python-ironicclient, python-subunit, testrepository, testtools,
# sphinx, sphinxcontrib, oslo.sphinx
# Which haven't been integrated yet
#
test:		$(NO_TESTS)


REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += install/installadm
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/file-system/uafs
REQUIRED_PACKAGES += system/file-system/uvfs
REQUIRED_PACKAGES += system/management/ipmitool
REQUIRED_PACKAGES += web/curl
