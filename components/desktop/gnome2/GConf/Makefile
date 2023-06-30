#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2020 Alexander Pyhalov
#

BUILD_BITS= 64_and_32
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         GConf
COMPONENT_VERSION=      2.32.4
COMPONENT_REVISION=     10
COMPONENT_SUMMARY=      GNOME Configuration Framework
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:46030c09422603dbb72f13b5dd592dcc01fbc13562b9e94dafb2b58982bc6b3a
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://projects.gnome.org/gconf/

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf --install --force)
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT =$(@D)/configure

CONFIGURE_LIBEXECDIR.32  = $(CONFIGURE_PREFIX)/lib/$(MACH32)
CONFIGURE_LIBEXECDIR.64  = $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBEXECDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-defaults-service=no
CONFIGURE_OPTIONS.32 += --enable-introspection=no

CONFIGURE_ENV+= INTLTOOL_PERL=$(PERL)

# CFLAGS are not passed to compiler when g-ir-scanner is used
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += PYTHON="$(PYTHON)"

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += text/intltool

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/lxml
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/orbit2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
