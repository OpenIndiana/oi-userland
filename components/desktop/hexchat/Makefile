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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hexchat
COMPONENT_VERSION=	2.12.4
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://hexchat.github.io/
COMPONENT_SUMMARY=	HexChat IRC client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:fa35913158bbc7d0d99de79371b6df3e8d21802f1d2c7c92f0e5db694acf2c3a
COMPONENT_ARCHIVE_URL=	https://dl.hexchat.net/hexchat/$(COMPONENT_ARCHIVE)
# We need to use non-default User-Agent for the fetch, otherwise we are denied
# to download the source file.
COMPONENT_FETCH_USER_AGENT= fetch

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# This is a workaround for hexchat-2.12.4 packaging bugs
COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					$(TOUCH) aclocal.m4 Makefile.in && \
					$(RM) build-aux/ltmain.sh && \
					$(LN) -s /usr/share/libtool/build-aux/ltmain.sh build-aux/ltmain.sh)

CONFIGURE_ENV += OBJC=$(CC)
CONFIGURE_ENV += PERL=$(PERL)
CONFIGURE_ENV += INTLTOOL_PERL=$(PERL)

CONFIGURE_OPTIONS += --enable-python=python2.7
# Avoid using luajit since static linking is broken
CONFIGURE_OPTIONS += LUA="lua"

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += system/library/libdbus-glib
