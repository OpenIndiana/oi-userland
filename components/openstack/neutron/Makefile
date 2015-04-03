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
# Copyright (c) 2013, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		neutron
COMPONENT_CODENAME=	juno
COMPONENT_VERSION=	2014.2.2
COMPONENT_BE_VERSION=	2014.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6b0509f7bc12a52ef4e90e1464720cd240eb93f0db2eef7d109d51fdb836a412
COMPONENT_ARCHIVE_URL=	http://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/neutron
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION)

TPNO=			21824

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

# move all the proper files into place and construct .pyc files for them
COMPONENT_POST_BUILD_ACTION += \
	($(MKDIR) $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
	 $(CP) \
             files/neutron-dhcp-agent.xml \
             files/neutron-l3-agent.xml \
             files/neutron-metadata-agent.xml \
             files/neutron-server.xml \
             files/neutron-upgrade.xml \
             $(PROTO_DIR)/lib/svc/manifest/application/openstack; \
         $(MKDIR) $(PROTO_DIR)/usr/lib/neutron; \
         $(CP) files/evs/migrate/evs-neutron-migration.py \
	     $(PROTO_DIR)/usr/lib/neutron/evs-neutron-migration; \
         $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/agent; \
	 $(CP) files/agent/evs_l3_agent.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/agent; \
	 $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/agent/solaris; \
	 $(CP) \
	     files/agent/solaris/__init__.py \
	     files/agent/solaris/dhcp.py \
	     files/agent/solaris/interface.py \
	     files/agent/solaris/ipfilters_manager.py \
	     files/agent/solaris/net_lib.py \
	     files/agent/solaris/ra.py \
	     $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/agent/solaris; \
	 $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/plugins/evs; \
	 $(TOUCH) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/plugins/evs/__init__.py; \
	 $(CP) files/evs/plugin.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/plugins/evs; \
         $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/plugins/evs/migrate; \
         $(CP) files/evs/migrate/__init__.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/plugins/evs/migrate; \
         $(CP) files/evs/migrate/havana_api.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/neutron/plugins/evs/migrate)

COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)


REQUIRED_PACKAGES += library/python/eventlet-27
REQUIRED_PACKAGES += library/python/iniparse-27
REQUIRED_PACKAGES += library/python/netaddr-27
REQUIRED_PACKAGES += library/python/oslo.config-27
REQUIRED_PACKAGES += library/python/oslo.db-27
REQUIRED_PACKAGES += library/python/python-mysql-27
REQUIRED_PACKAGES += library/python/simplejson-27
REQUIRED_PACKAGES += library/python/six-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += network/ipfilter
REQUIRED_PACKAGES += service/network/dnsmasq
REQUIRED_PACKAGES += service/network/evs
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/management/rad/client/rad-python
REQUIRED_PACKAGES += system/network
