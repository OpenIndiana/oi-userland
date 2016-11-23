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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =		gcc
BUILD_BITS =		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk2
COMPONENT_VERSION=	2.24.31
COMPONENT_PROJECT_URL=	http://www.gtk.org/
COMPONENT_SRC=		gtk+-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_HASH=	\
    sha256:68c1922732c7efc08df4656a5366dcc3afdc8791513400dac276009b40954658
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/gtk+/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/gtk+

TPNO=			32698

# Requires gdk-pixbuf, which we cannot build on 11.3, so do not publish.
include $(WS_MAKE_RULES)/no-evaluation.mk

ETCDIR.64="$(ETCDIR)/$(MACH64)"

include $(WS_MAKE_RULES)/gnome-component.mk

CFLAGS += $(CPP_XPG6MODE)

# Generate man pages.
CONFIGURE_OPTIONS += --enable-man
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --with-x

# Forcibly disable use of medialib since it's being removed soon in s12
CONFIGURE_ENV += ac_cv_lib_mlib_mlib_ImageSetStruct=no

# Tell g-ir-scanner which compiler to use since upstream Makefile forgot to
COMPONENT_BUILD_ENV += INTROSPECTION_SCANNER_ENV='CC=$(CC_FOR_BUILD)'

# Generate and install architecture-specific configuration files.
PROTOGTKDIR=		$(PROTO_DIR)$(USRLIB)/gtk-2.0/2.10.0
PROTOIMMCONF=		$(PROTOGTKDIR)/immodules.cache

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOGTKDIR); \
	LD_LIBRARY_PATH='$(PROTO_DIR)$(USRLIB)' \
	  $(PROTO_DIR)$(USRBIN)/gtk-query-immodules-2.0 \
	  $(PROTOGTKDIR)/immodules/*.so | \
	  $(GSED) -e 's%$(PROTO_DIR)%%' > $(PROTOIMMCONF) ;

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

# Strip pids from test output, since they're always different
COMPONENT_TEST_TRANSFORMS += '-e "s% (pid=[0-9]*)%%"'

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

REQUIRED_PACKAGES += data/docbook/docbook-dtds
REQUIRED_PACKAGES += data/docbook/docbook-style-dsssl
REQUIRED_PACKAGES += data/docbook/docbook-style-xsl
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/gnu-indent
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += print/cups
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/linker
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
# Tests run against an Xvfb server
REQUIRED_PACKAGES += x11/server/xvfb
