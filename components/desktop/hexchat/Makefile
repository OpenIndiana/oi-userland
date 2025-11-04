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

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hexchat
COMPONENT_VERSION=	2.16.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	HexChat IRC client
COMPONENT_PROJECT_URL=	https://hexchat.github.io/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:2e88340a8da274b87373ec0740746da78120cc6fbfdd201a4dd6999cac790e4a
COMPONENT_ARCHIVE_URL=	https://github.com/hexchat/hexchat/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/irc/hexchat
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Disable direct binding to allow the Python plugin to load.
# Without this, you get:
# ld.so.1: hexchat: fatal: relocation error: file .../python.so:
#   symbol __iob: referenced symbol not found
LD_B_DIRECT=

PERL5_LIBDIR=/usr/perl5/$(PERL_VERSION)/lib/$(PERL_ARCH)/CORE/

COMPONENT_POST_INSTALL_ACTION= ( \
	/usr/bin/elfedit -e 'dyn:value -s  RUNPATH "$(PERL5_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/hexchat/plugins/perl.so; \
	/usr/bin/elfedit -e 'dyn:value -s  RPATH "$(PERL5_LIBDIR)"' $(PROTOUSRDIR)/lib/$(MACH64)/hexchat/plugins/perl.so; \
	/usr/bin/elfedit -e 'dyn:value -add -s NEEDED "libpython$(PYTHON_VERSION).so.1.0"' \
		$(PROTOUSRDIR)/lib/$(MACH64)/hexchat/plugins/python.so)

CONFIGURE_OPTIONS += -Dwith-python=python-$(PYTHON_VERSION)
CONFIGURE_OPTIONS += -Dwith-lua=false
CONFIGURE_ENV += AR="/usr/gnu/bin/ar"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libx11
