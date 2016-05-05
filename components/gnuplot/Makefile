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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk
#libreadline.so needs libcurses.so, but -z ignore will not leave a dependency.
LD_Z_IGNORE=

COMPONENT_NAME=		gnuplot
COMPONENT_VERSION=	4.6.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://gnuplot.info/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:6e60adb5039a3541f407c2ade670004178b376754c424c13f0be24c7960c17be
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	utility/gnuplot

TPNO=			8452

CXXFLAGS += -std=c++11

# For now we will build against wxWidgets from this workspace and not
# against the system one (which is older).
# See also WX_CONFIG setting below.
WX_PROTO=$(COMPONENT_DIR)/../wxwidgets/build/prototype/$(MACH)
CXXFLAGS += -I$(WX_PROTO)$(USRLIBDIR64)/wx/include/gtk2-unicode-3.0
CXXFLAGS += -I$(WX_PROTO)$(USRINCDIR)/wx-3.0
LDFLAGS += -L$(WX_PROTO)$(USRLIBDIR64)

COMPONENT_BUILD_TARGETS = all info

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS  += --sysconfdir=$(ETCDIR)/gnu
CONFIGURE_OPTIONS  += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  += --x-libraries=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS  += WX_CONFIG="$(WX_PROTO)$(USRLIBDIR64)/wx/config/gtk2-unicode-3.0"

# Ensure that wxWidgets are built first.
../wxwidgets/build/$(MACH64)/.installed:
	(cd ../wxwidgets ; $(GMAKE) install)
$(CONFIGURE_64): ../wxwidgets/build/$(MACH64)/.installed

REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/font/truetype/liberation
REQUIRED_PACKAGES += system/font/xorg/xorg-core
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxevie
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxscrnsaver
