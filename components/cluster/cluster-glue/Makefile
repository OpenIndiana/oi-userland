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
# Copyright (c) 2013 Adam Stevko <adam.stevko@gmail.com>
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= cluster-glue
COMPONENT_VERSION= 1.0.12
COMPONENT_REVISION= 3
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_COMMIT= bdd95fd0f89f31b19fa46ffa0ea3f5022ebcd858
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= sha256:ae8cf05384e76be1cb0cd6b75708271e70f143a34aae1426684ed5b19033748f
COMPONENT_PROJECT_URL= http://linux-ha.org/wiki/Cluster_Glue
COMPONENT_ARCHIVE_URL=  https://github.com/ClusterLabs/cluster-glue/archive/$(COMPONENT_COMMIT).zip
COMPONENT_LICENSE= GPLv2, LGPLv2
COMPONENT_SUMMARY= Cluster Glue is a set of libraries, tools and utilities suitable for the Heartbeat/Pacemaker cluster stack.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL= 1

CFLAGS += -lssp -lssp_nonshared

CONFIGURE_BINDIR.64= $(CONFIGURE_PREFIX)/bin
CONFIGURE_SBINDIR.64= $(CONFIGURE_PREFIX)/sbin

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sharedstatedir=/var/cluster
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --enable-ansi=no
CONFIGURE_OPTIONS += --enable-fatal-warnings=no
CONFIGURE_OPTIONS += --with-daemon-user=hacluster
CONFIGURE_OPTIONS += --with-daemon-group=haclient
CONFIGURE_OPTIONS += --with-ocf-root=$(CONFIGURE_PREFIX)/lib/ocf
CONFIGURE_OPTIONS += --with-rundir=/var/run
CONFIGURE_OPTIONS += --enable-libnet
CONFIGURE_OPTIONS += --disable-rpath

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

COMPONENT_PREP_ACTION=(cd $(@D); $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) autogen.sh)

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_POST_INSTALL_ACTION+= cd $(PROTO_DIR) &&  \
	$(MV) usr/include/heartbeat/glue_config.h usr/include/heartbeat/glue_config-$(BITS).h

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += text/asciidoc

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
