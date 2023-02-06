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
# Copyright 2022 Friedrich Kink
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hylafax
COMPONENT_VERSION=	6.0.7
COMPONENT_REVISION=	4
COMPONENT_FMRI=		network/hylafax
COMPONENT_SUMMARY=	HylaFAX Open Source is an enterprise-class system for sending and \
	receiving facsimiles as well as for sending alpha-numeric pages.
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a3dcb1a7fd8794bd33cea9a9414c32da100119dd2131bd08ab3ab3749fc30315
COMPONENT_PROJECT_URL=	https://www.hylafax.org
COMPONENT_ARCHIVE_URL=	ftp://ftp.hylafax.org/source/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	HylaFAX
COMPONENT_LICENSE_FILE=	COPYRIGHT

TEST_TARGET=$(NO_TESTS) 

include $(WS_MAKE_RULES)/common.mk

#
# this not real configure from autotools but is is working
# with a few workarounds as seen in COMPONENT_POST_CONFIGURE_ACTION
#

CFLAGS+=        $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CFLAGS+=        $(CPP_LARGEFILES)
CXXFLAGS+=      $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS+=       $(JPEG_LDFLAGS)

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

COMPONENT_POST_CONFIGURE_ACTION += ( \
	$(GSED) -i -e "s:$(PROTO_DIR)::" $(@D)/config.h; \
	$(GSED) -i -e "s:/usr/local/share/locale:$(PROTO_DIR)/usr/share/locale:" $(@D)/defs; \
	$(GSED) -i -e 's:-L/usr/local/lib -R/usr/local/lib::' $(@D)/defs; \
	$(GSED) -i -e 's:-R$${LIBDIR} -lstdc++:-lstdc++:' $(@D)/defs; \
	$(MKDIR) -p  $(PROTO_DIR)$(USRLIBDIR64); \
);

# this is to avoid a conflict to usr/share/man/man1/notify.1
# delivered by SUNWcs
COMPONENT_POST_INSTALL_ACTION += ( \
	$(MV) $(PROTO_DIR)/usr/share/man/man1/notify.1 $(PROTO_DIR)$(USRSHAREMAN1DIR)/faxnotify.1; \
	$(GSED) -i -e "s:$(PROTO_DIR)::" $(PROTO_DIR)$(USRSHAREMAN1DIR)/*; \
	$(GSED) -i -e "s:$(PROTO_DIR)::" $(PROTO_DIR)$(USRSHAREMAN4DIR)/*; \
 );

CONFIGURE_OPTIONS =
CONFIGURE_OPTIONS +=    --srcdir=.
CONFIGURE_OPTIONS +=    --with-DIR_BIN=$(PROTO_DIR)$(USRBINDIR)
CONFIGURE_OPTIONS +=    --with-DIR_MAN=$(PROTO_DIR)$(USRSHAREMANDIR)
CONFIGURE_OPTIONS +=    --with-DIR_SBIN=$(PROTO_DIR)$(USRSBINDIR)
CONFIGURE_OPTIONS +=    --with-DIR_LIB=$(PROTO_DIR)$(USRLIBDIR64)
CONFIGURE_OPTIONS +=    --with-DIR_LIBEXEC=$(PROTO_DIR)$(USRSBINDIR)
CONFIGURE_OPTIONS +=    --with-DIR_LIBDATA=$(PROTO_DIR)/etc/hylafax
CONFIGURE_OPTIONS +=    --with-DIR_SPOOL=$(PROTO_DIR)/var/spool/hylafax
CONFIGURE_OPTIONS +=    --with-DIR_LOCALEDIR=$(PROTO_DIR)$(USRSHAREDIR)/locale
CONFIGURE_OPTIONS +=    --with-DIR_LOCKS=$(PROTO_DIR)/var/lock
CONFIGURE_OPTIONS +=    --with-LIBDIR=$(USRLIBDIR64)
CONFIGURE_OPTIONS +=    --with-TIFFBIN=$(USRBINDIR)
CONFIGURE_OPTIONS +=    --with-LIBINTL=-lintl
CONFIGURE_OPTIONS +=    --with-PATH_GSRIP=/usr/bin/gs
CONFIGURE_OPTIONS +=    --with-DBLIBINC=$(USRINCDIR)
CONFIGURE_OPTIONS +=    --with-AFM=no
CONFIGURE_OPTIONS +=    --with-MKDIR="/bin/mkdir -p"
CONFIGURE_OPTIONS +=    --with-AWK=/usr/bin/gawk
CONFIGURE_OPTIONS +=    --with-PATH_VGETTY=""
CONFIGURE_OPTIONS +=    --with-PATH_GETTY=""
CONFIGURE_OPTIONS +=    --with-PAGESIZE=A4
CONFIGURE_OPTIONS +=    --with-LLDOPTS=-lstdc++
CONFIGURE_OPTIONS +=    --with-PATH_DPSRIP=/var/spool/hylafax/bin/ps2fax
CONFIGURE_OPTIONS +=    --with-PATH_IMPRIP=""
CONFIGURE_OPTIONS +=    --with-SYSVINIT=/etc/init.d/hylafax
CONFIGURE_OPTIONS +=    --with-INTERACTIVE=no

# manually added
REQUIRED_PACKAGES += print/filter/ghostscript

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/extended-system-utilities
REQUIRED_PACKAGES += system/library
