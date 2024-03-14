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
# Copyright 2023 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		iaxmodem
COMPONENT_VERSION=	1.3.4
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		network/iaxmodem
COMPONENT_SUMMARY=	IAXmodem is a software modem written in C that uses an IAX channel
COMPONENT_DESCRIPTION=	IAXmodem is a software modem written in C that uses an IAX channel \
	(commonly provided by an Asterisk PBX system) instead of a traditional \
	phone line and uses a DSP library instead of DSP hardware chipsets. \
	To accomplish this, then, IAXmodem interfaces an IAX library known as \
	libiax2 with a DSP library known as spandsp, and then IAXmodem interfaces \
	the DSP library with a tty device node for interfacing with modem \
	applications.
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:900de2f77072bce02786fe7f4d4ddfd4b9f5fe3255b1319772383099adee5633
COMPONENT_PROJECT_URL=	https://iaxmodem.sourceforge.net/
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/iaxmodem/files/latest/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

TEST_TARGET=$(NO_TESTS) 

include $(WS_MAKE_RULES)/common.mk

#
# despite not a real autotools setup it works with some adaptions
# as seen in COMPONENT_POST_CONFIGURE_ACTION and COMPONENT_POST_INSTALL_ACTION
#

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

COMPONENT_POST_CONFIGURE_ACTION += ( \
	 $(GSED) -i -e 's/-DSTATICLIBS -DUSE_UNIX98_PTY/-DSTATICLIBS -D__EXTENSIONS__ -DSOLARIS -DUSE_UNIX98_PTY/' $(@D)/Makefile; \
	 $(GSED) -i -e 's/-DMODEMVER/-m64 -DMODEMVER/' $(@D)/Makefile; \
	 $(GSED) -i -e 's:Ilib/libiax2/src:I/usr/include/iax:' $(@D)/Makefile; \
	 $(GSED) -i -e 's: lib/libiax2/src/.libs/libiax.a: -liax:' $(@D)/Makefile; \
	 $(GSED) -i -e 's/-lm -lutil -ltiff/-m64 -lm -lnsl -lsocket -ltiff/' $(@D)/Makefile; \
	 );

CFLAGS+=	-DSOLARIS $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CFLAGS+=	$(CPP_LARGEFILES)
CXXFLAGS+=	$(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS+=	$(JPEG_LDFLAGS)

COMPONENT_INSTALL_TARGETS=	all

COMPONENT_POST_INSTALL_ACTION= ( \
	$(MKDIR) -p $(PROTO_DIR)/usr/sbin; \
	$(MKDIR) -p $(PROTO_DIR)/usr/share/man/man1; \
	$(MKDIR) -p $(PROTO_DIR)/etc/iaxmodem; \
	$(CP) $(@D)/$(COMPONENT_NAME) $(PROTO_DIR)/usr/sbin; \
	$(CP) $(@D)/$(COMPONENT_NAME).1 $(PROTO_DIR)/usr/share/man/man1; \
	$(CP) files/ttyIAX0.example $(PROTO_DIR)/etc/iaxmodem; \
	$(CP) files/config.ttyIAX $(PROTO_DIR)/etc/iaxmodem; \
	);
# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libiax2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
