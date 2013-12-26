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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= gtk-vnc

COMPONENT_VERSION= 0.3.10
COMPONENT_SUMMARY= gtk-vnc - A GTK widget for VNC client
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:3d92db46341cdd3f2f8e84c7a13d2e2d471167b333cfc838d268d2ce8513dd22
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/$(COMPONENT_NAME)/0.3/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Projects/gtk-vnc

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --enable-plugin=yes
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_ENV    += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV    += MSGFMT=/usr/gnu/bin/msgfmt
CONFIGURE_ENV    += PERL=$(PERL)
CONFIGURE_ENV    += PYTHON="$(PYTHON.$(BITS))"

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Need to move python modules to /64 dir
COMPONENT_POST_INSTALL_ACTION += \
    ( cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) ; \
        $(RM) -rf site-packages-$(BITS) ; \
        $(MV) site-packages site-packages-$(BITS) ; \
        $(MKDIR) -p site-packages ; \
        $(MKDIR) -p site-packages/64 ; \
        if test -d site-packages-64 ; then \
            $(MV) site-packages-64/* site-packages/64/ ; \
            $(MV) site-packages-32/* site-packages/ ; \
	    $(RM) -rf site-packages-64 site-packages-32 ; \
        fi ; )


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
