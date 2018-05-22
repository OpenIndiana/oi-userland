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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnuplot
COMPONENT_VERSION=	5.0.6
COMPONENT_REVISION=	1
COMPONENT_FMRI=	image/gnuplot
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_SUMMARY=	gnuplot - plotting utility
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://gnuplot.info/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:5bbe4713e555c2e103b7d4ffd45fca69551fff09cf5c3f9cb17428aaacc9b460
COMPONENT_ARCHIVE_URL=  \
  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	gnuplot License

# When CONFIGURE_FIX_LIBTOOL_RPATH is integrated, we can remove local fix and enable it
CONFIGURE_FIX_LIBTOOL_RPATH = no

COMPONENT_BUILD_TARGETS = all info

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

PATH=$(USRBINDIR.64):$(PATH.gnu)

CONFIGURE_BINDIR.64= $(CONFIGURE_BINDIR.32)

CONFIGURE_OPTIONS  += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS  += --sysconfdir=/etc/gnu
CONFIGURE_OPTIONS  += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  += --x-libraries=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS  += --without-libcerf
CONFIGURE_OPTIONS  += --with-qt=no
CONFIGURE_OPTIONS  += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  += CXXFLAGS="$(CXXFLAGS)"

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Build dependencies
REQUIRED_PACKAGES += editor/gnu-emacs

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
