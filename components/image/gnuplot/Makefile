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
# Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2017, Aurelien Larcher.
# Copyright 2021, Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnuplot
COMPONENT_VERSION=	6.0.2
COMPONENT_SUMMARY=	gnuplot - plotting utility
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://www.gnuplot.info/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:f68a3b0bbb7bbbb437649674106d94522c00bf2f285cce0c19c3180b1ee7e738
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=	image/gnuplot
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=	gnuplot License

COMPONENT_BUILD_TARGETS= all info

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= (cd $(@D) && autoreconf -fi)

CPPFLAGS += -I/usr/include/gd2

# needed for SUSv3 support for iconv
CFLAGS += $(XPG6MODE)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

PATH= $(PATH.gnu):$(QT5_BINDIR)
PKG_CONFIG_PATH=$(PKG_CONFIG_PATH.$(BITS)):$(QT5_PKG_CONFIG_PATH)
LD_OPTIONS += -L$(QT5_LIBDIR) -R$(QT5_LIBDIR)

CONFIGURE_OPTIONS  += --sysconfdir=$(ETCDIR)/gnu
CONFIGURE_OPTIONS  += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  += --x-libraries=$(CONFIGURE_LIBDIR.64)
CONFIGURE_OPTIONS  += --without-libcerf
CONFIGURE_OPTIONS  += --with-qt=qt5
CONFIGURE_OPTIONS  += --enable-year2038
CONFIGURE_OPTIONS  += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  += CXXFLAGS="$(CXXFLAGS)"

# We want to deploy the demo files
DEMOSOURCES=	$(SOURCE_DIR)/demo
DEMODEST=		$(PROTO_DIR)/usr/demo/gnuplot

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(DEMODEST) && \
	$(CP) -Rp $(DEMOSOURCES)/* $(DEMODEST)/

# Manually added dependencies
REQUIRED_PACKAGES += editor/gnu-emacs

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
