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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glance
COMPONENT_CODENAME=	mitaka
COMPONENT_VERSION=	12.0.0
COMPONENT_BE_VERSION=	2016.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:42213a4cd59bbcaa5f34d09ff48494a4d9831de9f27fc8541726a685a4c4f509
COMPONENT_ARCHIVE_URL=	https://tarballs.openstack.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/glance

TPNO=			30299

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
# glance-api, glance-registry, and glance-scrubber depend on glance-db
# and glance-upgrade so copy all of the service manifests into the
# proto directory for pkgdepend(1) to find.
#
COMPONENT_POST_INSTALL_ACTION += \
	($(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
	 $(CP) \
	     files/glance-db.xml \
	     files/glance-api.xml \
	     files/glance-registry.xml \
	     files/glance-scrubber.xml \
	     files/glance-upgrade.xml \
	     $(PROTO_DIR)/lib/svc/manifest/application/openstack)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)


REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/glance_store-27
REQUIRED_PACKAGES += library/python/iniparse-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.messaging-27
REQUIRED_PACKAGES += library/python/oslo.utils-27
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += library/python/sqlalchemy-migrate-27
REQUIRED_PACKAGES += system/core-os
