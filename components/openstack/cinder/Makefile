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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cinder
COMPONENT_CODENAME=	mitaka
COMPONENT_VERSION=	8.0.0
COMPONENT_BE_VERSION=	2016.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bd05f3c0b7b2ae098284c062d20230aecdaa47ed623cb79907c39dd1e28f8a2e
COMPONENT_ARCHIVE_URL=	https://tarballs.openstack.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/cinder
COMPONENT_ANITYA_ID=	13228

TPNO=			30298

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
# cinder-api, cinder-backup, cinder-scheduler, and cinder-volume depend
# on cinder-db and cinder-upgrade, so copy all of the service manifests
# into the proto directory for pkgdepend(1) to find.
#
COMPONENT_POST_INSTALL_ACTION += \
    ($(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
     $(CP) \
	 files/cinder-api.xml \
	 files/cinder-backup.xml \
	 files/cinder-db.xml \
	 files/cinder-scheduler.xml \
	 files/cinder-upgrade.xml \
	 files/cinder-volume.xml \
	 $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
     $(MKDIR) $(PROTO_DIR)$(PYTHON_LIB)/cinder/volume/drivers/solaris; \
     $(TOUCH) \
	 $(PROTO_DIR)$(PYTHON_LIB)/cinder/volume/drivers/solaris/__init__.py; \
     $(CP) \
	 files/solaris/nfs.py \
	 files/solaris/zfs.py \
	 $(PROTO_DIR)$(PYTHON_LIB)/cinder/volume/drivers/solaris; \
     $(CP) \
	 files/zfssa/cinder.akwf \
	 $(PROTO_DIR)$(PYTHON_LIB)/cinder/volume/drivers/zfssa); \
     $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)


REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/iniparse-27
REQUIRED_PACKAGES += library/python/ipython-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.utils-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += library/python/sqlalchemy-migrate-27
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/file-system/zfs
REQUIRED_PACKAGES += system/storage/fc-utilities
REQUIRED_PACKAGES += system/storage/iscsi/iscsi-target
REQUIRED_PACKAGES += system/storage/scsi-target-mode-framework
