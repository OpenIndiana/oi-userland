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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk
include ../../../make-rules/shared-targets.mk

COMPONENT_NAME=		neutron
COMPONENT_CODENAME=	kilo
COMPONENT_VERSION=	2015.1.2
COMPONENT_BE_VERSION=	2015.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3ff282d75e86ea25f64e97e24b2960e7ffaeef7cf4a69c16d20ffe18065d0ef0
COMPONENT_ARCHIVE_URL=	http://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/neutron
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)
IPS_PKG_NAME=		cloud/openstack/neutron

TPNO=			25791
TPNO_VPNAAS=		27275

NUM_EXTRA_ARCHIVES=	1

COMPONENT_NAME_1=	neutron-vpnaas
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:969d0d098db2d5df33d3008d3139821330bafcc7d7e684472db8b4c23b2126e6
COMPONENT_ARCHIVE_URL_1=	http://launchpad.net/neutron/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE_1)
COMPONENT_SIG_URL_1=	$(COMPONENT_ARCHIVE_URL_1).asc
SOURCE_DIR_1=		$(COMPONENT_DIR)/$(COMPONENT_SRC_1)
DEVICE_DRIVERS=		neutron_vpnaas/services/vpn/device_drivers
DEVICE_TEMPLATE=	$(DEVICE_DRIVERS)/template/solaris

PKG_VARS +=		COMPONENT_BE_VERSION

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk

# Depends on openvswitch, available in S12 but not 11.3, so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_NO_ARCH=
INSTALL_NO_ARCH=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.7

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

# move all the proper files into place and construct .pyc files for them
COMPONENT_POST_BUILD_ACTION += \
    $(GPATCH) -d $(SOURCE_DIR_1) $(GPATCH_FLAGS) \
	< vpnaas_patches/01-vpn_db_add_solaris.patch; \
    (cd $(SOURCE_DIR_1) ; \
	$(ENV) PROTO_DIR=$(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%) \
	    HOME=$(BUILD_DIR)/config-$* $(COMPONENT_BUILD_ENV) \
	    $(PYTHON.$(BITS)) ./setup.py build \
		--build-base $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%); \
	$(ENV) PROTO_DIR=$(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%) \
	    HOME=$(BUILD_DIR)/config-$* $(COMPONENT_BUILD_ENV) \
	    $(PYTHON.$(BITS)) ./setup.py install_data \
		--install-dir $(PROTO_DIR)); \
    $(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
    $(CP) \
	 files/neutron-dhcp-agent.xml \
	 files/neutron-l3-agent.xml \
	 files/neutron-metadata-agent.xml \
	 files/neutron-openvswitch-agent.xml \
	 files/neutron-server.xml \
	 files/neutron-upgrade.xml \
	 $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
    $(MKDIR) $(PROTO_DIR)/usr/lib/neutron; \
    $(CP) files/evs/migrate/evs-neutron-migration.py \
	 $(PROTO_DIR)/usr/lib/neutron/evs-neutron-migration; \
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent; \
    $(CP) files/agent/evs_l3_agent.py \
	 $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent; \
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent/solaris; \
    $(CP) \
	 files/agent/solaris/__init__.py \
	 files/agent/solaris/dhcp.py \
	 files/agent/solaris/interface.py \
	 files/agent/solaris/net_lib.py \
	 files/agent/solaris/packetfilter.py \
	 files/agent/solaris/ra.py \
	 $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent/solaris; \
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/neutron/plugins/evs; \
    $(TOUCH) $(PROTO_DIR)/$(PYTHON_LIB)/neutron/plugins/evs/__init__.py; \
    $(CP) files/evs/plugin.py $(PROTO_DIR)/$(PYTHON_LIB)/neutron/plugins/evs; \
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/neutron/plugins/evs/migrate; \
    $(CP) \
	 files/evs/migrate/__init__.py \
	 files/evs/migrate/havana_api.py \
	 $(PROTO_DIR)/$(PYTHON_LIB)/neutron/plugins/evs/migrate; \
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/$(DEVICE_TEMPLATE); \
    $(CP) files/services/vpn/device_drivers/solaris_ipsec.py \
	$(PROTO_DIR)/$(PYTHON_LIB)/$(DEVICE_DRIVERS); \
    $(CP) \
	files/services/vpn/device_drivers/template/solaris/ikev2.secret.template \
	files/services/vpn/device_drivers/template/solaris/ike.template \
	files/services/vpn/device_drivers/template/solaris/ikev2.template \
	files/services/vpn/device_drivers/template/solaris/ipsecinit.conf.template \
	files/services/vpn/device_drivers/template/solaris/ike.secret.template \
	$(PROTO_DIR)/$(PYTHON_LIB)/$(DEVICE_TEMPLATE)

COMPONENT_POST_INSTALL_ACTION += \
    $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += library/python/alembic-27
REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/iniparse-27
REQUIRED_PACKAGES += library/python/netaddr-27
REQUIRED_PACKAGES += library/python/netifaces-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.db-27
REQUIRED_PACKAGES += library/python/simplejson-27
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += network/arping
REQUIRED_PACKAGES += network/firewall
REQUIRED_PACKAGES += service/network/dnsmasq
REQUIRED_PACKAGES += service/network/evs
REQUIRED_PACKAGES += service/network/openvswitch
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/management/rad/client/rad-python
REQUIRED_PACKAGES += system/network
