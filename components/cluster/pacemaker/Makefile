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
# Copyright 2019 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

PATH= $(USRBINDIR64):$(PATH.gnu)

COMPONENT_NAME= pacemaker
COMPONENT_VERSION= 1.1.21
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC= $(COMPONENT_NAME)-Pacemaker-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:4914f2caf5676ecf54b2fd19c59b40268a54b04703b56cf840cb63fbdbbb7d06
COMPONENT_PROJECT_URL= https://www.clusterlab.org
COMPONENT_ARCHIVE_URL= https://github.com/Clusterlabs/$(COMPONENT_NAME)/archive/Pacemaker-$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= GPLv2,LGPLv2,BSD
COMPONENT_SUMMARY= Pacemaker is an advanced, scalable high-availability cluster resource manager.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

CFLAGS += -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS -lssp_nonshared -lssp -lnsl

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
GNUTLS_PKG_CONFIG_PATH_64 = /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATH = $(GNUTLS_PKG_CONFIG_PATH_$(BITS)):$(PKG_CONFIG_PATH.$(BITS))

LD_OPTIONS.64 += -L/usr/lib/$(MACH64)/gnutls-3 -R/usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CONFIGURE_OPTIONS.64 += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sysconfdir=/etc
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
CONFIGURE_OPTIONS += --disable-rpath
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

COMPONENT_POST_INSTALL_ACTION=( \
    $(RM) -r $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME)/examples; \
    $(MKDIR) $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME)/examples; \
    $(MV)    $(PROTO_DIR)/etc/logrotate.d  $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME)/examples;)

CONFIGURE_SBINDIR.64= $(CONFIGURE_SBINDIR.32)

build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(TESTS_64)

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
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
# added manually, not found as dependency
REQUIRED_PACKAGES += text/asciidoc
