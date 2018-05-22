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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= rrdtool

COMPONENT_VERSION= 1.4.7
COMPONENT_REVISION= 4
COMPONENT_SUMMARY= Data analysis tool generating graphical representations
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:956aaf431c955ba88dd7d98920ade3a8c4bad04adb1f9431377950a813a7af11
COMPONENT_ARCHIVE_URL= \
  http://oss.oetiker.ch/rrdtool/pub/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://oss.oetiker.ch/rrdtool/

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && libtoolize -fi && autoreconf -fi ) 

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV	+=  PERL=$(PERL)
CONFIGURE_ENV	+=  PERLCC=$(CC)
CONFIGURE_OPTIONS+= --with-perl-options="CC=$(CC) LD=$(CC) LIB=/usr/perl5/$(PERL_VERSION)/lib"
CONFIGURE_OPTIONS+= --disable-python
CONFIGURE_OPTIONS+= --disable-ruby
CONFIGURE_OPTIONS+= --enable-tcl
CONFIGURE_OPTIONS+= --enable-static=no

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
