#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		wireshark
COMPONENT_VERSION=	2.0.5
COMPONENT_PROJECT_URL=	http://www.wireshark.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:0ce0241330828973f5b4efee422a3760cab8ce0b41e7721c4b9fd185be1bb10b
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)download/src/all-versions/$(COMPONENT_ARCHIVE)

TPNO=			30387

TEST_TARGET= $(NO_TESTS)

# Depends on newer cairo, which cannot be updated in S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Micro version for easy libraries packaging
MICRO_VERSION:= $(shell echo $(COMPONENT_VERSION) | awk -F. '{ print $$3 }')
PKG_MACROS+= MICRO_VERSION=$(MICRO_VERSION)

PATCH_LEVEL=0

# We don't have automake 1.14 yet. Thus need to reconfigure with older one.
COMPONENT_PREP_ACTION += ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh );

# Look for gnutls-3 pkg-config & libraries before the defaults
PKG_CONFIG_PATH.64 := $(PKG_CONFIG_PATH.64)/gnutls-3:$(PKG_CONFIG_PATH.64)
LDFLAGS += -L$(USRLIBDIR64)/gnutls-3

CONFIGURE_BINDIR.64= $(CONFIGURE_SBINDIR.64)

CONFIGURE_OPTIONS +=	--disable-usr-local
CONFIGURE_OPTIONS +=	--disable-androiddump
CONFIGURE_OPTIONS +=	--disable-randpkt
CONFIGURE_OPTIONS +=	--disable-dftest
CONFIGURE_OPTIONS +=	--with-krb5
CONFIGURE_OPTIONS +=	--with-qt=no
CONFIGURE_OPTIONS +=	--with-gtk2=yes
CONFIGURE_OPTIONS +=	\
  PATH="$(USRDIR)/perl5/bin:$(GNUBIN)/$(MACH64):$(GNUBIN):$(USRBIN.64):$(PATH)"

# We need to avoid RPATH=/usr/lib in Wireshark libraries so that we can
# create successfully IPS package of different Wireshark branch than is
# installed on build system without dependency errors.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	sed -e 's,-R/usr/lib/$(MACH64),,' \
	    -e 's,-R/usr/lib,,' \
	    -e 's,-R\$$libdir,,' \
		config.status > config.status.new; \
	mv config.status.new config.status; \
	chmod 755 config.status; \
	./config.status)

# During install libtool will relink libwireshark library so that it
# requires libwiretap version from system and not from proto area.
# This workaround is only needed when CBE contains older libwiretap.
LIBWIRESHARK=$(PROTOUSRLIBDIR64)/libwireshark.so.6.1.$(MICRO_VERSION)
COMPONENT_POST_INSTALL_ACTION = \
	(WTAP=`$(ELFEDIT) -e dyn:dump $(LIBWIRESHARK) | grep 'libwiretap' | awk '{print $$4}'` \
	; $(ELFEDIT) -e "dyn:value -s -with-valstr $$WTAP libwiretap.so.5" $(LIBWIRESHARK) )

REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += diagnostic/wireshark/wireshark-common
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += security/kerberos-5
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
