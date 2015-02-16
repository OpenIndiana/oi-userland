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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nova
COMPONENT_CODENAME=	havana
COMPONENT_VERSION=	2013.2.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:02902cb65b5adb0419c69cdb03ea2a0cfdfe8f7df342be44f3760d66cdecb61e
COMPONENT_ARCHIVE_URL=	http://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/nova
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION) 

TPNO=			17715

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.6

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)

# Replace the standard nova/virt/libvirt/__init__.py with an empty file.
COMPONENT_POST_INSTALL_ACTION += \
	($(CP) /dev/null $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/nova/virt/libvirt/__init__.py; \
	 $(MKDIR) $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/nova/virt/solariszones; \
	 $(CP) files/solariszones/__init__.py $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/nova/virt/solariszones; \
	 $(CP) files/solariszones/driver.py $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/nova/virt/solariszones; \
	 $(CP) files/solariszones/sysconfig.py $(PROTO_DIR)/usr/lib/python2.6/vendor-packages/nova/virt/solariszones); \
        $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)


REQUIRED_PACKAGES += install/archive
REQUIRED_PACKAGES += library/python/eventlet-26
REQUIRED_PACKAGES += library/python/oslo.config-26
REQUIRED_PACKAGES += library/python/sqlalchemy-migrate-26
REQUIRED_PACKAGES += library/python/webob-26
REQUIRED_PACKAGES += runtime/python-26
REQUIRED_PACKAGES += service/network/evs
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/file-system/zfs
REQUIRED_PACKAGES += system/library/storage/suri
REQUIRED_PACKAGES += system/storage/fc-utilities
REQUIRED_PACKAGES += system/storage/iscsi/iscsi-initiator
REQUIRED_PACKAGES += terminal/xterm
REQUIRED_PACKAGES += x11/server/xvnc
