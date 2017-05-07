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
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_HG_REV= 0a7add1d9996
COMPONENT_SRC= Reusable-Cluster-Components-glue--$(COMPONENT_HG_REV)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_HG_REV).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:c47bfffbfe11401379d5248fc7518a3de9532c02090d614f314037fc3a7c4ceb
COMPONENT_PROJECT_URL= http://linux-ha.org/wiki/Cluster_Glue
COMPONENT_ARCHIVE_URL=  http://hg.linux-ha.org/glue/archive/$(COMPONENT_HG_REV).tar.bz2
COMPONENT_LICENSE= GPLv2, LGPLv2
COMPONENT_SUMMARY= Cluster Glue is a set of libraries, tools and utilities suitable for the Heartbeat/Pacemaker cluster stack.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL= 1

CFLAGS += -lssp -lssp_nonshared

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

COMPONENT_PREP_ACTION=(cd $(@D); $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) autogen.sh)

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += text/asciidoc
