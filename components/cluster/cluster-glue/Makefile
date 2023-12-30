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

DROP_STATIC_LIBRARIES = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= cluster-glue
COMPONENT_VERSION= 1.0.12
COMPONENT_REVISION= 8
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_COMMIT= bdd95fd0f89f31b19fa46ffa0ea3f5022ebcd858
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= sha256:ae8cf05384e76be1cb0cd6b75708271e70f143a34aae1426684ed5b19033748f
COMPONENT_PROJECT_URL= http://linux-ha.org/wiki/Cluster_Glue
COMPONENT_ARCHIVE_URL=  https://github.com/ClusterLabs/cluster-glue/archive/$(COMPONENT_COMMIT).zip
COMPONENT_SUMMARY= Cluster Glue is a set of libraries, tools and utilities suitable for the Heartbeat/Pacemaker cluster stack.
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sharedstatedir=$(VARDIR)/cluster
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --enable-ansi=no
CONFIGURE_OPTIONS += --enable-fatal-warnings=no
CONFIGURE_OPTIONS += --with-daemon-user=hacluster
CONFIGURE_OPTIONS += --with-daemon-group=haclient
CONFIGURE_OPTIONS += --with-ocf-root=$(CONFIGURE_PREFIX)/lib/ocf
CONFIGURE_OPTIONS += --with-rundir=$(VARDIR)/run
CONFIGURE_OPTIONS += --enable-libnet

COMPONENT_PREP_ACTION=(cd $(@D); $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) autogen.sh)

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

# We do not want to distribute tests, init scripts, and compiled Python files
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRSHAREDIR)/cluster-glue/lrmtest ;
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOETCDIR)/init.d ;
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRLIBDIR.$(BITS))/stonith/plugins/stonith2/__pycache__ ;

# Make sure the Python shebang points to right Python
PYTHON_SCRIPTS += usr/lib/$(MACH64)/stonith/plugins/external/dracmc-telnet
PYTHON_SCRIPTS += usr/lib/$(MACH64)/stonith/plugins/external/ibmrsa-telnet
PYTHON_SCRIPTS += usr/lib/$(MACH64)/stonith/plugins/external/riloe
PYTHON_SCRIPTS += usr/lib/$(MACH64)/stonith/plugins/stonith2/ribcl.py

# Build dependencies
REQUIRED_PACKAGES += text/asciidoc
REQUIRED_PACKAGES += system/library/libnet

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libtool/libltdl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/management/snmp/net-snmp
REQUIRED_PACKAGES += web/curl
