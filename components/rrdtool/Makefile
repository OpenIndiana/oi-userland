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

COMPONENT_NAME= rrdtool

COMPONENT_VERSION= 1.4.7
COMPONENT_SUMMARY= Data analysis tool generating graphical representations
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:956aaf431c955ba88dd7d98920ade3a8c4bad04adb1f9431377950a813a7af11
COMPONENT_ARCHIVE_URL= \
  http://oss.oetiker.ch/rrdtool/pub/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://oss.oetiker.ch/rrdtool/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D) && cd $(@D) && autoconf ) 

CONFIGURE_ENV	+=  PERL=$(PERL)
CONFIGURE_ENV	+=  PERLCC=$(CC)
CONFIGURE_OPTIONS+= --with-perl-options="CC=$(CC) LD=$(CC) LIB=/usr/perl5/$(PERL_VERSION)/lib"
CONFIGURE_OPTIONS+= --disable-python
CONFIGURE_OPTIONS+= --disable-ruby
CONFIGURE_OPTIONS+= --enable-tcl
CONFIGURE_OPTIONS+= --enable-static=no

build: $(BUILD_32)

install: $(INSTALL_32)
