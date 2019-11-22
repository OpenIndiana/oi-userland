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
# Copyright 2012-2013, EveryCity Ltd. All rights reserved.
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Till Wegm√ller
# Copyright 2019 Michal Nowak
#

BUILD_BITS=32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		postgresql
COMPONENT_MJR_VERSION=	9.6
COMPONENT_MNR_VERSION=	16
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:5c6cba9cc0df70ba2b128c4a87d0babfce7c0e2b888f70a9c8485745f66b22e7
COMPONENT_ARCHIVE_URL=	http://ftp.postgresql.org/pub/source/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://www.postgresql.org

TEST_TARGET=$(TEST_32_and_64)

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS = --prefix=/usr/postgres/$(COMPONENT_MJR_VERSION)
CONFIGURE_OPTIONS += --exec-prefix=/usr/postgres/$(COMPONENT_MJR_VERSION)
CONFIGURE_OPTIONS += --datadir=/usr/postgres/$(COMPONENT_MJR_VERSION)/share
CONFIGURE_OPTIONS += --sysconfdir=/etc/postgres/$(COMPONENT_MJR_VERSION)
CONFIGURE_OPTIONS += --mandir=/usr/postgres/$(COMPONENT_MJR_VERSION)/man
CONFIGURE_OPTIONS += --includedir=/usr/postgres/$(COMPONENT_MJR_VERSION)/include
CONFIGURE_OPTIONS += --sharedstatedir=/var/postgres/$(COMPONENT_MJR_VERSION)
CONFIGURE_OPTIONS += --localstatedir=/var/postgres/$(COMPONENT_MJR_VERSION)
CONFIGURE_OPTIONS += --localedir=/usr/share/locale
CONFIGURE_OPTIONS += --docdir=/usr/postgres/$(COMPONENT_MJR_VERSION)/doc
CONFIGURE_OPTIONS += --htmldir=/usr/postgres/$(COMPONENT_MJR_VERSION)/doc
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --with-system-tzdata=/usr/share/lib/zoneinfo
CONFIGURE_OPTIONS.64 += --with-tcl
CONFIGURE_OPTIONS.64 += --with-python
CONFIGURE_OPTIONS.64 += --with-pam
CONFIGURE_OPTIONS += --with-openssl
CONFIGURE_OPTIONS += --with-libedit-preferred
CONFIGURE_OPTIONS += --with-libxml
CONFIGURE_OPTIONS += --with-libxslt
CONFIGURE_OPTIONS += --with-gssapi
CONFIGURE_OPTIONS += --enable-thread-safety
CONFIGURE_OPTIONS += --enable-dtrace
CONFIGURE_OPTIONS += --enable-integer-datetimes
CONFIGURE_OPTIONS += --with-includes=/usr/include
CONFIGURE_OPTIONS += --with-tclconfig=/usr/lib
CONFIGURE_OPTIONS.64 += --with-perl
CONFIGURE_OPTIONS += --with-uuid=e2fs

CONFIGURE_OPTIONS.32 += --bindir=/usr/postgres/$(COMPONENT_MJR_VERSION)/bin/$(MACH32)
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/postgres/$(COMPONENT_MJR_VERSION)/bin/$(MACH32)
CONFIGURE_OPTIONS.32 += --sbindir=/usr/postgres/$(COMPONENT_MJR_VERSION)/bin/$(MACH32)
CONFIGURE_OPTIONS.32 += --libdir=/usr/postgres/$(COMPONENT_MJR_VERSION)/lib

CONFIGURE_OPTIONS.64 += --bindir=/usr/postgres/$(COMPONENT_MJR_VERSION)/bin
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/postgres/$(COMPONENT_MJR_VERSION)/bin
CONFIGURE_OPTIONS.64 += --sbindir=/usr/postgres/$(COMPONENT_MJR_VERSION)/bin
CONFIGURE_OPTIONS.64 += --libdir=/usr/postgres/$(COMPONENT_MJR_VERSION)/lib/$(MACH64)

CONFIGURE_OPTIONS+=$(CONFIGURE_OPTIONS.$(BITS))

CONFIGURE_ENV	+= PYTHON=$(PYTHON)
CONFIGURE_ENV.32     += PERL=$(PERL)
CONFIGURE_ENV.64     += PERL=$(PERL.5.24)

COMPONENT_BUILD_TARGETS = world
COMPONENT_INSTALL_TARGETS = install-world

COMPONENT_POST_INSTALL_ACTION.64= cd $(BUILD_DIR_$(BITS))/src/test/regress; env $(COMPONENT_INSTALL_ENV) gmake $(COMPONENT_INSTALL_ARGS) install-lib install-tests;

COMPONENT_POST_INSTALL_ACTION+= $(COMPONENT_POST_INSTALL_ACTION.$(BITS))
COMPONENT_POST_INSTALL_ACTION+= cd $(PROTO_DIR) &&  \
             $(MV) usr/postgres/$(COMPONENT_MJR_VERSION)/include/pg_config.h usr/postgres/$(COMPONENT_MJR_VERSION)/include/pg_config-$(BITS).h  && \
             $(MV) usr/postgres/$(COMPONENT_MJR_VERSION)/include/server/pg_config.h usr/postgres/$(COMPONENT_MJR_VERSION)/include/server/pg_config-$(BITS).h	

COMPONENT_TEST_ENV += MAKELEVEL=0
COMPONENT_TEST_ENV += PATH=$(PATH)

COMPONENT_TEST_TRANSFORMS= \
	'-n ' \
	'-e "/ok/p"' \
	'-e "/FAIL/p"' \
	'-e "/failed/p"'

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/gss
