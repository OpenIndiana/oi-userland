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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=            	64_and_32
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk-vnc
COMPONENT_VERSION=	0.5.4
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_HASH= \
	sha256:488aa97a76ce6868160699cd45d4a0ee0fe6f0ad4631737c6ddd84450f6c9ce7
COMPONENT_BUGDB=	gnome/remote-desktop
COMPONENT_ANITYA_ID=	13142

TPNO=			29178	

TEST_TARGET= $(NO_TESTS)

# Needs updated glib2, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATHS.32 += $(PKG_CONFIG_PATH.32)/gnutls-3
PKG_CONFIG_PATHS.64 += $(PKG_CONFIG_PATH.64)/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L $(USRLIB.32)/gnutls-3 -R $(USRLIB.32)/gnutls-3
LD_OPTIONS.64 += -L $(USRLIB.64)/gnutls-3 -R $(USRLIB.64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

LD_OPTIONS += -z gnu-version-script-compat

CONFIGURE_OPTIONS += --without-python
CONFIGURE_OPTIONS += --with-gtk=3.0

# Assumes GNU xgettext is first in $PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
# Assumes pod2man can be found somewhere in $PATH
COMPONENT_BUILD_ENV += PATH="$(PATH):/usr/perl5/$(PERL_VERSION)/bin"

REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/library/security/libsasl2
REQUIRED_PACKAGES += x11/library/libx11
