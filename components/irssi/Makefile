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
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		irssi
COMPONENT_VERSION=	0.8.15
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:c12d16fb605103d7c256ddce44012dc396af57f3771e086d0387c195a052a0a6
COMPONENT_ARCHIVE_URL=	http://irssi.org/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://irssi.org/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=$(SPRO_VROOT)/bin:/usr/bin:/usr/gnu/bin

CONFIGURE_OPTIONS +=	--with-perl=yes
CONFIGURE_OPTIONS +=	--with-proxy
CONFIGURE_OPTIONS +=	--with-perl-lib=$(CONFIGURE_PREFIX)/perl5/vendor_perl/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	--includedir=$(CONFIGURE_INCLUDEDIR)

CONFIGURE_ENV     +=    perlpath=$(PERL)

COMPONENT_POST_INSTALL_ACTION += ( for x in perllocal.pod .packlist '*.la' ; do find $(PROTO_DIR) -name $$x -exec rm -f {} \; ; done);
COMPONENT_POST_INSTALL_ACTION += ( for x in COPYING AUTHORS ChangeLog ; do cp $(SOURCE_DIR)/$$x $(PROTOUSRSHAREDOCDIR)/irssi/$$x ; done );

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
