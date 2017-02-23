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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS=64
# While the tree currently builds with Studio, we need to make sure it also
# builds with gcc when submitting patches upstream, and having both sets of
# options in the CFLAGS below makes it easy to switch when needed.
# COMPILER=gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xscreensaver
COMPONENT_VERSION=	5.34
COMPONENT_PROJECT_URL=	https://www.jwz.org/xscreensaver/
COMPONENT_ARCHIVE_HASH=	\
    sha256:6fff7ec4be743e5c042647ea9687dd0cdf48d1dd5e8e15098e5018bbd02e5e27
COMPONENT_ARCHIVE_URL=	https://www.jwz.org/xscreensaver/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=        gnome/screensaver
COMPONENT_ANITYA_ID=	5269

TPNO=			26341

TEST_TARGET = $(NO_TESTS)

# Needs older version of libpng, no longer available in evaluation builds.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Enable additional warnings, since we've modified this code a lot
CFLAGS.studio += -v
CFLAGS.gcc    += -Wall

# Additional optimization flags, to make the hacks show off the hardware
# better and because for just a screensaver display we can get away with
# using optimizations that may change strict correctness of floating point ops.
CFLAGS.studio += -fsimple=2 -nofstore -xlibmil -xprefetch
CFLAGS.gcc    += -funsafe-math-optimizations

# Fix 64-bit linking; compiler is used for the linking.
LDFLAGS += $(CC_BITS)

# Regenerate configure after patches modify configure.in; the automake -af
# forces the update of the standard automake files that autoreconf will not
# update because Makefile.am does not exist.  This is needed to ensure we have
# a recent version of config.guess, etc. used for configure; the | true is
# because automake will exit with an error because Makefile.am does not exist,
# but it will update the required files.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv; automake -af | true)

# Need to pick up the GNU version of xgettext.
PATH=$(GNUBIN):$(USRBINDIR)

# Libraries & programs to depend on
CONFIGURE_OPTIONS += --with-gl=$(USRDIR)
CONFIGURE_OPTIONS += --with-gtk=$(USRDIR)
CONFIGURE_OPTIONS += --with-jpeg=$(USRDIR)
CONFIGURE_OPTIONS += --without-motif
CONFIGURE_OPTIONS += --with-pixbuf=$(USRDIR)
CONFIGURE_OPTIONS += --with-xft=$(USRDIR)
CONFIGURE_OPTIONS += PTHREAD_CFLAGS="-D_POSIX_PTHREAD_SEMANTICS"
CONFIGURE_OPTIONS += PTHREAD_LIBS="-lc"
CONFIGURE_OPTIONS += PERL=$(PERL)
CONFIGURE_OPTIONS += INTLTOOL_PERL=$(PERL)

# X extensions to support
CONFIGURE_OPTIONS += --with-dpms-ext
CONFIGURE_OPTIONS += --with-randr-ext
CONFIGURE_OPTIONS += --with-xinerama-ext
CONFIGURE_OPTIONS += --with-xinput-ext  # required for accessibility

# Support locking the screen by normal users and by root
CONFIGURE_OPTIONS += --enable-locking
CONFIGURE_OPTIONS += --enable-root-passwd
# and allow user switching from the lock screen with gdmflexiserver
CONFIGURE_OPTIONS += --with-login-manager

# Use only PAM, not direct /etc/shadow or kerberos access
CONFIGURE_OPTIONS += --with-pam=$(USRDIR)
CONFIGURE_OPTIONS += --without-shadow
CONFIGURE_OPTIONS += --without-kerberos

# Paths to install to
APP_DEFAULTS_DIR  = $(CONFIGURE_PREFIX)/share/X11/app-defaults
XSS_LIBDIR 	  = $(CONFIGURE_PREFIX)/lib/xscreensaver
CONFIGURE_OPTIONS += --libexecdir=$(XSS_LIBDIR)/bin
CONFIGURE_OPTIONS += --with-hackdir=$(XSS_LIBDIR)/hacks
CONFIGURE_OPTIONS += --with-configdir=$(XSS_LIBDIR)/config/control-center-2.0
CONFIGURE_OPTIONS += --with-x-app-defaults=$(APP_DEFAULTS_DIR)

# Data sources for images & text in hacks
CONFIGURE_OPTIONS += --with-image-directory=$(USRSHAREDIR)/backgrounds
CONFIGURE_OPTIONS += --with-text-file=/etc/motd

# Do not install setuid hacks
CONFIGURE_OPTIONS += --without-setuid-hacks

# The potfiles.in updates don't work unless source is cloned to build dir
COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D));

# Update potfiles.in to pick up our added sources like lock-Gtk.c
# The "-o Makefile" & touch stamp-it is needed to avoid infinite looping.
COMPONENT_POST_CONFIGURE_ACTION += ( \
    cd $(@D)/po ; \
    $(MAKE) -o Makefile generate_potfiles_in ; \
    $(MAKE) -o Makefile POTFILES ; \
    $(MAKE) -o Makefile xscreensaver.pot ; \
    touch stamp-it )

# Recognizing DESTDIR as most autotools packages do would be too easy,
# so xscreensaver makes us override install_prefix instead for the same effect.
COMPONENT_INSTALL_ARGS += install_prefix=$(PROTO_DIR)

# Remove hacks we've chosen not to ship at all for various reasons
REMOVED_HACKS="extrusion flyingtoasters ljlatest sonar webcollage"
COMPONENT_POST_INSTALL_ACTION += ( \
for h in $(REMOVED_HACKS) ; do \
    rm -f $(PROTO_DIR)$(XSS_LIBDIR)/hacks/$${h} \
          $(PROTO_DIR)$(CONFIGURE_MANDIR)/man6/$${h}.6 \
          $(PROTO_DIR)$(XSS_LIBDIR)/config/control-center-2.0/$${h}.xml ;\
done ; \
rm -f $(PROTO_DIR)$(XSS_LIBDIR)/hacks/webcollage-helper );

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS= \
	$(PROTOUSRBINDIR)/xscreensaver-getimage-file \
	$(PROTOUSRBINDIR)/xscreensaver-getimage-video \
	$(PROTOUSRBINDIR)/xscreensaver-text

REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxmu
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxxf86misc
REQUIRED_PACKAGES += x11/library/libxxf86vm
REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += x11/library/toolkit/libxt
