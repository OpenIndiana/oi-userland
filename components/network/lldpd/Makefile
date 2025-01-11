#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Marcel Telka
#

USE_DEFAULT_TEST_TRANSFORMS= yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			lldpd
COMPONENT_VERSION=		1.0.19
COMPONENT_SUMMARY=		lldpd is a 802.1AB implementation (LLDP) to help you locate neighbors of all your equipments
COMPONENT_PROJECT_URL=		https://lldpd.github.io/
COMPONENT_FMRI=			service/network/lldp
COMPONENT_CLASSIFICATION=	System/Services
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=		https://media.luffy.cx/files/lldpd/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=		sha256:f87df3163d5e5138da901d055b384009785d1eb50fdb17a2343910fcf30a997f
COMPONENT_LICENSE=		ISC
COMPONENT_LICENSE_FILE=		LICENSE

include $(WS_MAKE_RULES)/common.mk

# Build expects socket functions in libc
CONFIGURE_ENV += LIBS=-lsocket

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-privsep-user=lldp
CONFIGURE_OPTIONS += --with-privsep-group=lldp
CONFIGURE_OPTIONS += --with-privsep-chroot=$(VARDIR)/empty

# Install the service related files
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -Dm0444 $(COMPONENT_DIR)/files/lldp.xml $(PROTO_DIR)/lib/svc/manifest/network/lldp.xml ;

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libevent2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
