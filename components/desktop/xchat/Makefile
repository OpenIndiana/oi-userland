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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xchat
COMPONENT_VERSION=	2.8.8
COMPONENT_REVISION=	5
COMPONENT_PROJECT_URL=	http://xchat.org
COMPONENT_SUMMARY=	XChat IRC Client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:0d6d69437b5e1e45f3e66270fe369344943de8a1190e498fafa5296315a27db0
COMPONENT_ARCHIVE_URL=	http://www.xchat.org/files/source/2.8/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					glib-gettextize -f &&\
					libtoolize --copy --force &&\
					aclocal &&\
					$(TOUCH) NEWS &&\
					automake --add-missing -c -f && \
					autoconf )

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--enable-dbus
CONFIGURE_OPTIONS+=	--enable-ipv6

CONFIGURE_ENV+=	perlpath=$(PERL)
CONFIGURE_ENV+=	pythonpath=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libsexy
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += x11/library/libx11
