#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Marcel Telka <marcel@telka.sk>
# Copyright 2020 Michal Nowak
#

BITS=			64
BUILD_STYLE=		meson
USE_OPENSSL11=		yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hexchat
COMPONENT_VERSION=	2.16.1
COMPONENT_PROJECT_URL=	https://hexchat.github.io/
COMPONENT_SUMMARY=	HexChat IRC client
COMPONENT_FMRI=		desktop/irc/hexchat
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:a7e497da71df419daf9855582d51c723a2611de25d5e97b5efc33fe78da5c4c7
COMPONENT_ARCHIVE_URL=	https://dl.hexchat.net/hexchat/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= "org.opensolaris.category.2008:Applications/Internet"
COMPONENT_LICENSE= GPLv2


# We need to use non-default User-Agent for the fetch, otherwise we are denied
# to download the source file.
COMPONENT_FETCH_USER_AGENT= fetch

TEST_TARGET=           $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk
PATH=$(PATH.gnu)

PERL5_LIBDIR=/usr/perl5/$(PERL_VERSION)/lib/$(PERL_ARCH)/CORE/
COMPONENT_POST_INSTALL_ACTION = ( \
	for file in `find $(PROTOUSRDIR) -name "*.so"`; do \
        /usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(PERL5_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/hexchat/plugins/perl.so; \
        /usr/bin/elfedit -e 'dyn:value -s  RPATH "$(PERL5_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/hexchat/plugins/perl.so; \
	/usr/bin/elfedit -e 'dyn:value -s NEEDED "libpython3.9.so.1.0"' $(PROTOUSRDIR)/lib/$(MACH64)/hexchat/plugins/python.so; \
	done; )



CONFIGURE_OPTIONS += -Dwith-python=python-3.9
CONFIGURE_OPTIONS += -Dwith-lua=false
CONFIGURE_ENV += AR="/usr/gnu/bin/ar"

REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += runtime/python-39

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libx11
