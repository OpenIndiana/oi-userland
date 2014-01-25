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

COMPONENT_NAME= libproxy

COMPONENT_VERSION= 0.3.1
COMPONENT_SUMMARY= Libproxy is a library that provides automatic proxy configuration management
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:82e27b1b391fbf36ae1433729b7431739212171fbffc34c55eb75b60e20998fb
COMPONENT_ARCHIVE_URL= \
  http://libproxy.googlecode.com/files/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://code.google.com/p/libproxy/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# I believe it increases cross GCC/Sun Studio compatibility
gcc_OPT=-O2

COMPONENT_PREP_ACTION= ( cd $(@D) && \
                libtoolize --force &&\
                aclocal -I . &&\
                automake -a -c -f &&\
                autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D)) 

CFLAGS+= -D__EXTENSIONS__

CONFIGURE_OPTIONS.64 += --without-mozjs

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --includedir=/usr/include/libproxy
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_OPTIONS+= --with-gnome
CONFIGURE_OPTIONS+= --without-dotnet
CONFIGURE_OPTIONS+= --with-direct
CONFIGURE_OPTIONS+= --with-envvar
CONFIGURE_OPTIONS+= --with-file
CONFIGURE_OPTIONS+= --with-wpad
CONFIGURE_OPTIONS+= --without-networkmanager
CONFIGURE_OPTIONS+= --without-webkit
CONFIGURE_OPTIONS+= $(CONFIGURE_OPTIONS.$(BITS))

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
