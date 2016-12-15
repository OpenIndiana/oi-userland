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
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= corosync
COMPONENT_VERSION= 2.4.1
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0fae5f07af8854c8921f243469be9052e3795237f5c6293d12ae235d2f75e965
COMPONENT_PROJECT_URL= https://github.com/corosync/corosync
COMPONENT_ARCHIVE_URL= https://github.com/$(COMPONENT_NAME)/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= BSD
COMPONENT_SUMMARY= The Corosync cluster engine.

PATH= /usr/gnu/bin:/usr/bin:/usr/sbin:/sbin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL = 1

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

CFLAGS += -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS
LDFLAGS += -R/usr/lib/mps

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sharedstatedir=/var/hacluster
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-monitoring
CONFIGURE_OPTIONS += --enable-snmp
CONFIGURE_OPTIONS += --enable-xmlconf
CONFIGURE_OPTIONS += --enable-testagents
CONFIGURE_OPTIONS += --enable-augeas
CONFIGURE_OPTIONS += --enable-qdevices
CONFIGURE_OPTIONS += --with-logdir=/var/log/hacluster

COMPONENT_POST_INSTALL_ACTION=( \
    mkdir -p  $(PROTO_DIR)/usr/share/corosync/examples/conf; \
    cp -r $(PROTO_DIR)/etc/corosync/*  $(PROTO_DIR)/usr/share/corosync/examples/conf ; \
    mv $(PROTO_DIR)/etc/logrotate.d    $(PROTO_DIR)/usr/share/corosync/examples; \
    rm $(PROTO_DIR)/etc/corosync/corosync.conf.example; \
    rm $(PROTO_DIR)/etc/corosync/corosync.conf.example.udpu; \
    rm $(PROTO_DIR)/etc/corosync/corosync.xml.example )

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libqb
REQUIRED_PACKAGES += library/libstatgrab
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += system/management/snmp/net-snmp
