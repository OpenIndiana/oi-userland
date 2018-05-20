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
# Copyright 2016-2017 Predrag Zečević.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= geany-plugins
COMPONENT_VERSION= 1.33
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_FMRI=editor/geany/plugins
COMPONENT_SUMMARY= Plugins for Geany editor
COMPONENT_DESCRIPTION= Geany-Plugins is a collection of different plugins for Geany, a lightweight IDE.
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:27ddca83d3d5b2ba7dd09574bd2bb5a23245dddc327d29e5a12f0e1dd9a80785
COMPONENT_ARCHIVE_URL= http://plugins.geany.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://plugins.geany.org/
COMPONENT_LICENSE= GPLv2

COMPONENT_PREP_ACTION += ( cd $(@D) && autoreconf -f)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS+= -std=gnu99
CFLAGS+= -D_FILE_OFFSET_BITS=64
CFLAGS+= -D_XOPEN_SOURCE=600

CONFIGURE_ENV+= CHECK_CFLAGS="-I/usr/include/check"

# cppcheck is not packaged
CONFIGURE_OPTIONS+= --disable-cppcheck

# requires libutil
CONFIGURE_OPTIONS+= --disable-debugger
CONFIGURE_OPTIONS+= --disable-scope

# requires webkit 1.x
CONFIGURE_OPTIONS+= --disable-devhelp
CONFIGURE_OPTIONS+= --disable-markdown
CONFIGURE_OPTIONS+= --disable-webhelper

# no lipsum (www.lipsum.com) in OI yet
CONFIGURE_OPTIONS+= --disable-lipsum

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += editor/geany
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtkspell
REQUIRED_PACKAGES += library/desktop/libwnck
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/vte
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgit2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/python/pygobject
REQUIRED_PACKAGES += library/python/pygtk2 
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
