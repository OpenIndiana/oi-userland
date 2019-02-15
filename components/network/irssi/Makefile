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
# Copyright 2011 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
# Copyright 2016 Adam Stevko
# Copyright 2017 Gary Mills
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		irssi
COMPONENT_VERSION=	1.2.0
COMPONENT_SUMMARY=	irssi - a terminal based IRC client
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_FMRI=		network/chat/irssi
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:1643fca1d8b35e5a5d7b715c9c889e1e9cdb7e578e06487901ea959e6ab3ebe5
COMPONENT_ARCHIVE_URL= \
  https://github.com/irssi/irssi/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://irssi.org/
COMPONENT_LICENSE=	GPLv2+
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS +=	--with-perl=yes
CONFIGURE_OPTIONS +=	--with-socks
CONFIGURE_OPTIONS +=	--with-proxy
CONFIGURE_OPTIONS +=	--with-modules
CONFIGURE_OPTIONS +=	--with-perl-lib=$(CONFIGURE_PREFIX)/perl5/vendor_perl/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)

CONFIGURE_ENV     +=    perlpath=$(PERL)

COMPONENT_PRE_CONFIGURE_ACTION += $(CLONEY) $(SOURCE_DIR) $(@D)

COMPONENT_POST_INSTALL_ACTION += ( for x in perllocal.pod .packlist '*.la' ; do find $(PROTO_DIR) -name $$x -exec rm -f {} \; ; done);
COMPONENT_POST_INSTALL_ACTION += ( for x in COPYING AUTHORS ChangeLog ; do cp $(SOURCE_DIR)/$$x $(PROTOUSRSHAREDOCDIR)/irssi/$$x ; done );

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
