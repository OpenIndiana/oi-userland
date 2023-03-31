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

USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		irssi
COMPONENT_VERSION=	1.4.4
COMPONENT_SUMMARY=	irssi - a terminal based IRC client
COMPONENT_PROJECT_URL=	https://irssi.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://github.com/irssi/irssi/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:fefe9ec8c7b1475449945c934a2360ab12693454892be47a6d288c63eb107ead
COMPONENT_FMRI=		network/chat/irssi
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=	GPLv2+

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=	--with-perl=yes
CONFIGURE_OPTIONS +=	--with-socks
CONFIGURE_OPTIONS +=	--with-proxy
CONFIGURE_OPTIONS +=	--with-modules
CONFIGURE_OPTIONS +=	--with-perl-lib=$(CONFIGURE_PREFIX)/perl5/vendor_perl/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)

CONFIGURE_ENV += perlpath=$(PERL)

COMPONENT_PRE_CONFIGURE_ACTION += $(CLONEY) $(SOURCE_DIR) $(@D)

COMPONENT_POST_INSTALL_ACTION += ( for x in perllocal.pod .packlist '*.la' ; do find $(PROTO_DIR) -name $$x -exec rm -f {} \; ; done);
COMPONENT_POST_INSTALL_ACTION += ( for x in COPYING AUTHORS ChangeLog ; do cp $(SOURCE_DIR)/$$x $(PROTOUSRSHAREDOCDIR)/irssi/$$x ; done );

# PKGVERS is needed for manifest processing
PKG_MACROS += PERLVER=$(PERL_VERSION)

# Bogus dependency due to libssp
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
