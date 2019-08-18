#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Adam Stevko. All rights reserved. 
# Copyright 2019 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= resource-agents
COMPONENT_VERSION= 4.1.0
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e9391b3c1d2d8828a36547440597c50a983ac2779c411d0b5ab26e06412b499f
COMPONENT_PROJECT_URL= https://github.com/ClusterLabs/resource-agents
COMPONENT_ARCHIVE_URL= https://github.com/ClusterLabs/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= LGPLv2,GPLv2,GPLv3
COMPONENT_SUMMARY= Combined repository of OCF agents from the RHCS and Linux-HA projects

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)
CFLAGS += "-lnsl"

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sharedstatedir=/var/hacluster
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-fatal-warnings=no
CONFIGURE_OPTIONS += --enable-ansi
CONFIGURE_OPTIONS += --with-ocf-root=$(CONFIGURE_PREFIX)/lib/ocf

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); ./autogen.sh) 

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SBINDIR.64= $(CONFIGURE_SBINDIR.32)

# leaving this folder prevents repeated install actions
COMPONENT_PRE_INSTALL_ACTION = ( $(RM) -r $(PROTO_DIR)/usr/lib/ocf/; ) 

# this component creates binaries (findif, send_arp) and links against 64-bit libraries
 
build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(TESTS_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += application/cluster/cluster-glue
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libnet
REQUIRED_PACKAGES += text/gawk
