#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
#   via checkout freeipmi_sfw-gate_oi151a~0.7.7~9c2a4ac793f0
# Copyright 2016 Jim Klimov
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freeipmi
COMPONENT_VERSION=	1.6.15
COMPONENT_SUMMARY=	GNU FreeIPMI - in-band and out-of-band IPMI software based on the IPMI v1.5/2.0 specification
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:d6929c354639f5ce75b5b1897e8b366eb63625c23e5c4590a7aea034fe2b8caf
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/freeipmi/
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Hardware
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# gcc 14 complains about this
CFLAGS += -Wno-error=implicit-function-declaration

CFLAGS += $(CPP_LARGEFILES) -DMAXHOSTNAMELEN=256
CPPFLAGS += $(CPP_LARGEFILES) -DMAXHOSTNAMELEN=256

CONFIGURE_OPTIONS += --infodir=/usr/share/doc/freeipmi/info
CONFIGURE_OPTIONS += --libdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-dont-check-for-root

# This is needed to avoid using CCACHE for CPP in this recipe:
# they use CPP to build manpages! Go figure...
CONFIGURE_ENV += CPP_FOR_BUILD=$(GCC_ROOT)/bin/cpp

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += driver/ipmi
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
