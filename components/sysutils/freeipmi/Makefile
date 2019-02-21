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
COMPONENT_VERSION=	1.6.3
COMPONENT_SUMMARY=	GNU FreeIPMI - in-band and out-of-band IPMI
COMPONENT_DESCRIPTION=	GNU FreeIPMI - in-band and out-of-band IPMI software based on the \
IPMI v1.5/2.0 specification ($(COMPONENT_VERSION))
COMPONENT_FMRI=		system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Hardware
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:aad4e735a7ac4a1f8ade20caadb35dfefc2a352fa2ef41d3f6e589179917e1e9
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/freeipmi/
COMPONENT_ARCHIVE_URL=	\
	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += $(CPP_LARGEFILES) -DMAXHOSTNAMELEN=256
CPPFLAGS += $(CPP_LARGEFILES) -DMAXHOSTNAMELEN=256

USRLIBDIR.32=$(USRLIBDIR)
USRLIBDIR.64=$(USRLIBDIR64)

COMPONENT_PREP_ACTION = \
    (cd $(@D) &&\
        aclocal -I . &&\
        autoheader &&\
        automake -a -f -c --gnu &&\
        autoconf &&\
        $(RM) config.h )

# Missing files in build dir for configure without this
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

#       configure(1) options to use
# a default --prefix and --mandir are set in make-rules
CONFIGURE_OPTIONS += --with-dont-check-for-root
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --infodir=/usr/share/doc/freeipmi/info
CONFIGURE_OPTIONS += --enable-static=no
CONFIGURE_OPTIONS += --libdir=$(USRLIBDIR.$(BITS))

# This is needed to avoid using CCACHE for CPP in this recipe:
# they use CPP to build manpages! Go figure...
CONFIGURE_ENV += CPP_FOR_BUILD=$(GCC_ROOT)/bin/cpp

build:		$(BUILD_32_and_64)

# Ensure 32-bit configs are installed last
$(INSTALL_32): $(INSTALL_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
