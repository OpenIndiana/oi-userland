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
# Copyright (c) 2013, 2014, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cinder
COMPONENT_CODENAME=	grizzly
COMPONENT_VERSION=	2013.1.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b3466dbc2ea88eef67f73db2b12ec2e8b66047b2bfa0eea31392e155657bee00
COMPONENT_ARCHIVE_URL=	http://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/cinder
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION) 

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.6

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)

# cinder-api, cinder-backup, cinder-scheduler, and cinder-volume
# depend on the cinder-db svc so copy the manifest into the proto
# directory for pkgdepend to find
COMPONENT_POST_INSTALL_ACTION += \
        ($(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
         $(CP) files/cinder-api.xml $(PROTO_DIR)/lib/svc/manifest/application/openstack/; \
         $(CP) files/cinder-backup.xml $(PROTO_DIR)/lib/svc/manifest/application/openstack/; \
         $(CP) files/cinder-db.xml $(PROTO_DIR)/lib/svc/manifest/application/openstack/; \
         $(CP) files/cinder-scheduler.xml $(PROTO_DIR)/lib/svc/manifest/application/openstack/; \
         $(CP) files/cinder-volume.xml $(PROTO_DIR)/lib/svc/manifest/application/openstack/; \
         $(MKDIR) $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/cinder/volume/drivers/solaris; \
	 $(TOUCH) $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/cinder/volume/drivers/solaris/__init__.py; \
	 $(CP) files/solaris/zfs.py $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/cinder/volume/drivers/solaris); \
	 $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
