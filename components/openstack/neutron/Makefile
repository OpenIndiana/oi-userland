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

COMPONENT_NAME=		neutron
COMPONENT_OLDNAME=	quantum
COMPONENT_CODENAME=	grizzly
COMPONENT_VERSION=	2013.1.4
COMPONENT_SRC=		$(COMPONENT_OLDNAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3bd26ae7dabe6093a3cbe701ac8d7022fbdbe1d8231ab1c6866de388684e272c
COMPONENT_ARCHIVE_URL=	http://launchpad.net/$(COMPONENT_NAME)/$(COMPONENT_CODENAME)/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.openstack.org/
COMPONENT_BUGDB=	service/neutron
IPS_COMPONENT_VERSION=	0.$(COMPONENT_VERSION) 

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Since this is an app, and doesn't provide any public library interfaces, we
# only need to deliver one version.  The manifest is parameterized, though.
PYTHON_VERSIONS=	2.6

PKG_MACROS +=		PYVER=$(PYTHON_VERSIONS)

# move all the proper files into place and construct .pyc files for them
COMPONENT_POST_BUILD_ACTION += \
	 ($(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent; \
	 $(CP) files/agent/evs_l3_agent.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent; \
	 $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/linux; \
	 $(CP) files/agent/linux/device.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/linux; \
	 $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/solaris; \
	 $(CP) files/agent/solaris/__init__.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/solaris; \
	 $(CP) files/agent/solaris/device.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/solaris; \
	 $(CP) files/agent/solaris/dhcp.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/solaris; \
	 $(CP) files/agent/solaris/interface.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/solaris; \
	 $(CP) files/agent/solaris/ipfilters_manager.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/solaris; \
	 $(CP) files/agent/solaris/net_lib.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/agent/solaris; \
	 $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs; \
	 $(TOUCH) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs/__init__.py; \
	 $(CP) files/evs/plugin.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs; \
	 $(MKDIR) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs/db; \
	 $(TOUCH) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs/db/__init__.py; \
	 $(CP) files/evs/db/api.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs/db; \
	 $(CP) files/evs/db/l3nat.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs/db; \
	 $(CP) files/evs/db/quotas_db.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/vendor-packages/quantum/plugins/evs/db)


COMPONENT_POST_INSTALL_ACTION += \
        $(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
