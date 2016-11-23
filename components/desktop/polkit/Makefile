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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

# parfait is a bit unhappy (24796481)
export PARFAIT_BUILD=no

BUILD_BITS =            64_and_32
# Also, all components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		polkit
COMPONENT_VERSION=	0.113
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/polkit/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:e1c095093c654951f78f8618d427faf91cf62abdefed98de40ff65eca6413c81
COMPONENT_ARCHIVE_URL=	http://www.freedesktop.org/software/polkit/releases/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).sign
COMPONENT_BUGDB=	gnome/security

TPNO=			27381

# Test don't work on Solaris
TEST_TARGET = $(SKIP_TEST)

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

# Regenerate configure after patches/02-duktape.patch modifies configure.ac
COMPONENT_PREP_ACTION += ( cd $(@D); autoreconf -fiv);
# Make sure we haven't broken the SMF manifest formatting
COMPONENT_PREP_ACTION += \
    ( /usr/sbin/svccfg validate $(COMPONENT_DIR)/files/polkit.xml );

# Need C99 or later to get fpclassify() & isfinite() in <math.h>
CFLAGS += -ggdb
CFLAGS.gcc += -std=gnu11
CFLAGS.studio += -std=c11 -xlang=c11

# Solaris doesn't have a defined authpriv facility in syslog, so map it to
# an unused one for now
CPPFLAGS += -DLOG_AUTHPRIV='(10<<3)'

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk-doc
CONFIGURE_OPTIONS += --enable-man-pages
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-authfw=pam
CONFIGURE_OPTIONS += --with-polkitd-user=_polkitd
CONFIGURE_OPTIONS += --with-os-type=solaris
CONFIGURE_OPTIONS += --sysconfdir="$(ETCDIR)"

# Workaround the mozjs issue described in 24935318
LD_EXEC_OPTIONS += -M $(PWD)/../../gnome/gjs/mapfile
ADIHEAP_MODE = $(ADIHEAP_DISABLE)
ADISTACK_MODE = $(ADISTACK_DISABLE)

# Largefile support breaks use of <procfs.h> when build environment is older
# than s12_84 due to Solaris bug 21833491
ifeq ($(OS_VERSION), 5.11)
  CONFIGURE_OPTIONS += --disable-largefile
endif

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

# SMF manifest & method
PKG_PROTO_DIRS += $(COMPONENT_DIR)/files

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libmozjs-24
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
