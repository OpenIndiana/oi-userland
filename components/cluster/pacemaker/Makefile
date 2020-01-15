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
# Copyright 2020 Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

PATH= $(USRBINDIR64):$(PATH.gnu)

COMPONENT_NAME=		pacemaker
COMPONENT_VERSION=	2.0.3
COMPONENT_FMRI=		application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC=		$(COMPONENT_NAME)-Pacemaker-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ca228f7f9745c7bc1e31bebe30e51475e95a82d9010d281f1701f2e3310bd3fe
COMPONENT_PROJECT_URL=	https://www.clusterlab.org
COMPONENT_ARCHIVE_URL=	https://github.com/Clusterlabs/$(COMPONENT_NAME)/archive/Pacemaker-$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	GPLv2,LGPLv2,BSD
COMPONENT_SUMMARY=	Pacemaker is an advanced, scalable high-availability cluster resource manager.

include $(WS_MAKE_RULES)/common.mk

PYTHON_VERSION = 3.5

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

CFLAGS += -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS -lssp_nonshared -lssp -lnsl -lssl -lcrypto

CONFIGURE_OPTIONS.64 += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --sharedstatedir=/var/hacluster
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-corosync
CONFIGURE_OPTIONS += --with-acl=no
CONFIGURE_OPTIONS += --enable-upstart=no
CONFIGURE_OPTIONS += --enable-systemd=no
CONFIGURE_OPTIONS += --enable-fatal-warnings=no
CONFIGURE_OPTIONS += --disable-rpath
CONFIGURE_OPTIONS += --with-logdir=/var/log/hacluster
CONFIGURE_OPTIONS += --with-bundledir=/var/log/hacluster/bundles
CONFIGURE_OPTIONS += --with-openssl=yes
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"
CONFIGURE_ENV.64 += PYTHON=$(PYTHON)

COMPONENT_POST_INSTALL_ACTION=( \
	$(RM) -r $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME)/examples; \
	$(MKDIR) $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME)/examples; \
	$(MV)    $(PROTO_DIR)/etc/logrotate.d  $(PROTO_DIR)$(USRSHAREDIR)/$(COMPONENT_NAME)/examples;)

# added manually, not found as dependency
REQUIRED_PACKAGES += text/asciidoc
REQUIRED_PACKAGES += shell/gnu-getopt
REQUIRED_PACKAGES += utility/arpsend
REQUIRED_PACKAGES += library/libstatgrab
REQUIRED_PACKAGES += library/libesmtp
# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += application/cluster/cluster-glue
REQUIRED_PACKAGES += application/cluster/corosync
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libqb
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/pcre2
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
