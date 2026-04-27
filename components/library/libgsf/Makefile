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
# Copyright 2015 Alexander Pyhalov
# Copyright 2019 Jason Martin
# Copyright 2021 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libgsf
HUMAN_VERSION=		1.14.56
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= GNOME Structured File Library
COMPONENT_ARCHIVE_HASH= sha256:9d21d30df1d12feaf03e181afd6067f65e3048ab69cb6ad174a3c5b72b92d297
COMPONENT_FMRI= library/desktop/libgsf
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH= $(PATH.gnu)

# Missing files in build dir without this.
CLONEY_MODE =

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-bz2
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --enable-introspection

# Testing fails with valgrind installed
TEST_CONFLICTING_PACKAGES += developer/debug/valgrind

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
