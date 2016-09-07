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

COMPONENT_NAME=		nova
COMPONENT_CODENAME=	mitaka
COMPONENT_VERSION=	13.1.0
COMPONENT_BE_VERSION=	2016.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:2c44b0f015f48348d768abff0e0fc90c6f8faf46743cae94736d77704f249368
COMPONENT_ARCHIVE_URL=	\
    https://tarballs.openstack.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/nova

TPNO=			30363

PKG_VARS +=		COMPONENT_BE_VERSION

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.7

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

#
# Replace the standard nova/virt/libvirt/__init__.py with an empty file.
#
# All of the nova SMF manifests depend on nova-upgrade so copy it into
# the proto directory for pkgdepend(1) to find.
#
COMPONENT_POST_INSTALL_ACTION += \
    ($(CP) /dev/null $(PROTO_DIR)$(PYTHON_LIB)/nova/virt/libvirt/__init__.py; \
     $(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
     $(CP) \
	 files/nova-api-ec2.xml \
	 files/nova-api-metadata.xml \
	 files/nova-api-osapi-compute.xml \
	 files/nova-cert.xml \
	 files/nova-compute.xml \
	 files/nova-conductor.xml \
	 files/nova-consoleauth.xml \
	 files/nova-novncproxy.xml \
	 files/nova-objectstore.xml \
	 files/nova-scheduler.xml \
	 files/nova-upgrade.xml \
	 files/zone-vnc-console.xml \
	 $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
     $(CP) \
	 files/network/solaris_net.py \
	 $(PROTO_DIR)$(PYTHON_LIB)/nova/network; \
     $(MKDIR) $(PROTO_DIR)$(PYTHON_LIB)/nova/virt/solariszones; \
     $(CP) \
	 files/solariszones/__init__.py \
	 files/solariszones/driver.py \
	 files/solariszones/sysconfig.py \
	 $(PROTO_DIR)$(PYTHON_LIB)/nova/virt/solariszones); \
    $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)


REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += install/archive
REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/iniparse-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.log-27
REQUIRED_PACKAGES += library/python/oslo.messaging-27
REQUIRED_PACKAGES += library/python/oslo.serialization-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += library/python/sqlalchemy-migrate-27
REQUIRED_PACKAGES += library/python/webob-27
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/file-system/zfs
REQUIRED_PACKAGES += system/library/storage/suri
REQUIRED_PACKAGES += system/storage/fc-utilities
REQUIRED_PACKAGES += system/storage/iscsi/iscsi-initiator
REQUIRED_PACKAGES += terminal/xterm
REQUIRED_PACKAGES += web/novnc
REQUIRED_PACKAGES += x11/diagnostic/x11-info-clients
REQUIRED_PACKAGES += x11/modeline-utilities
REQUIRED_PACKAGES += x11/server/xvnc
REQUIRED_PACKAGES += x11/x11-server-utilities
