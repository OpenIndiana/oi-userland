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
COMPONENT_CODENAME=	mitaka
COMPONENT_VERSION=	8.1.2
COMPONENT_BE_VERSION=	2016.1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a3fdeed1421e1586bbdabd046474f1060bff4751257eacd90489f9e1b6eeff9d
COMPONENT_ARCHIVE_URL=	https://tarballs.openstack.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/neutron
IPS_PKG_NAME=		cloud/openstack/neutron

TPNO=			30361
TPNO_VPNAAS=		30362

COMPONENT_NAME_1=	neutron-vpnaas
COMPONENT_VERSION_1=	8.1.2
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:3852d8bf27c49c1beb0813a327d10e50b185f26e4479ad168498c4a2c6c97dd2
COMPONENT_ARCHIVE_URL_1=https://tarballs.openstack.org/$(COMPONENT_NAME_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_SIG_URL_1=	$(COMPONENT_ARCHIVE_URL_1).asc
SOURCE_DIR_1=		$(COMPONENT_DIR)/$(COMPONENT_SRC_1)

DEVICE_DRIVERS=		neutron_vpnaas/services/vpn/device_drivers
DEVICE_TEMPLATE=	$(DEVICE_DRIVERS)/template/solaris

PKG_PROTO_DIRS =	$(SOURCE_DIR_1)
PKG_VARS +=		COMPONENT_BE_VERSION

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk

# Depends on openvswitch, available in S12 but not 11.3, so do not publish.
BUILD_BITS=NO_ARCH
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.7

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)
PKG_MACROS +=		PYV=$(shell echo $(PYTHON_VERSIONS) | tr -d .)

install-vpnaas: $(SOURCE_DIR_1)/.installed

$(SOURCE_DIR_1)/.installed:
	(cd $(SOURCE_DIR_1); \
	 $(ENV) \
	     HOME=$(BUILD_DIR)/config-$* \
	     PROTO_DIR=$(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%) \
	     $(COMPONENT_BUILD_ENV) \
	     $(PYTHON.$(BITS)) ./setup.py build \
		 --build-base $(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%); \
	 $(ENV) \
	     HOME=$(BUILD_DIR)/config-$* \
	     PROTO_DIR=$(PYTHON_VERSIONS:%=$(BUILD_DIR)/$(MACH)-%) \
	     $(COMPONENT_BUILD_ENV) \
	     $(PYTHON.$(BITS)) ./setup.py install $(COMPONENT_INSTALL_ARGS))
	$(TOUCH) $(SOURCE_DIR_1)/.installed

# move all the proper files into place and construct .pyc files for them
COMPONENT_POST_BUILD_ACTION += \
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
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent/l3; \
    $(CP) files/agent/l3/solaris_agent.py \
	 $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent/l3; \
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent/solaris; \
    $(CP) \
	 files/agent/solaris/__init__.py \
	 files/agent/solaris/dhcp.py \
	 files/agent/solaris/interface.py \
	 files/agent/solaris/namespace_manager.py \
	 files/agent/solaris/net_lib.py \
	 files/agent/solaris/packetfilter.py \
	 files/agent/solaris/pd.py \
         files/agent/solaris/pf_firewall.py \
	 files/agent/solaris/ra.py \
	 $(PROTO_DIR)/$(PYTHON_LIB)/neutron/agent/solaris; \
    $(MKDIR) $(PROTO_DIR)/$(PYTHON_LIB)/$(DEVICE_TEMPLATE); \
    $(CP) files/services/vpn/device_drivers/solaris_ipsec.py \
	$(PROTO_DIR)/$(PYTHON_LIB)/$(DEVICE_DRIVERS); \
    $(CP) \
	files/services/vpn/device_drivers/template/solaris/ike.secret.template \
	files/services/vpn/device_drivers/template/solaris/ike.template \
	files/services/vpn/device_drivers/template/solaris/ikev2.secret.template \
	files/services/vpn/device_drivers/template/solaris/ikev2.template \
	files/services/vpn/device_drivers/template/solaris/ipsecinit.conf.template \
	$(PROTO_DIR)/$(PYTHON_LIB)/$(DEVICE_TEMPLATE)

COMPONENT_POST_INSTALL_ACTION += \
    $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# Skip all building & installing, especially of vpnaas, in evaluation mode.
ifeq ($(BUILD_TYPE), evaluation)
build:
install:
else
build:		$(BUILD_NO_ARCH)
install:	$(INSTALL_NO_ARCH) install-vpnaas
endif

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)

REQUIRED_PACKAGES += cloud/openstack/openstack-common
REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/netaddr-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.log-27
REQUIRED_PACKAGES += library/python/oslo.messaging-27
REQUIRED_PACKAGES += library/python/oslo.utils-27
REQUIRED_PACKAGES += library/python/simplejson-27
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += network/arping
REQUIRED_PACKAGES += network/firewall
REQUIRED_PACKAGES += service/network/dnsmasq
REQUIRED_PACKAGES += service/network/openvswitch
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/network
