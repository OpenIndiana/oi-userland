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
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pacemaker
COMPONENT_VERSION= 1.1.15
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC= $(COMPONENT_NAME)-Pacemaker-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:9af53ef397fbd1517f380eb4268b48433c41bb38dd3511ed9cb80e9478034775
COMPONENT_PROJECT_URL= https://www.clusterlab.org
COMPONENT_ARCHIVE_URL= https://github.com/Clusterlabs/$(COMPONENT_NAME)/archive/Pacemaker-$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= GPLv2,LGPLv2,BSD
COMPONENT_SUMMARY= Pacemaker is an advanced, scalable high-availability cluster resource manager.

PATH= /usr/gnu/bin:/usr/bin:/usr/sbin:/sbin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL = 1

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

CFLAGS += -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS -lssp_nonshared -lssp -lnsl

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sharedstatedir=/var/hacluster
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-corosync
CONFIGURE_OPTIONS += --with-heartbeat=no
CONFIGURE_OPTIONS += --with-snmp
CONFIGURE_OPTIONS += --with-esmtp
CONFIGURE_OPTIONS += --with-cs-quorum
CONFIGURE_OPTIONS += --with-acl=no
CONFIGURE_OPTIONS += --enable-upstart=no
CONFIGURE_OPTIONS += --enable-systemd=no
CONFIGURE_OPTIONS += --enable-fatal-warnings=no

COMPONENT_POST_INSTALL_ACTION=( \
    mkdir -p $(PROTO_DIR)/usr/share/pacemaker/examples; \
    mv $(PROTO_DIR)/etc/logrotate.d $(PROTO_DIR)/usr/share/pacemaker/examples )

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += utility/arpsend
REQUIRED_PACKAGES += application/cluster/corosync
REQUIRED_PACKAGES += application/cluster/cluster-glue
REQUIRED_PACKAGES += application/cluster/resource-agents
REQUIRED_PACKAGES += library/libstatgrab
REQUIRED_PACKAGES += library/libesmtp
REQUIRED_PACKAGES += library/libqb
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
# added manually, not found as dependency
REQUIRED_PACKAGES += text/asciidoc
