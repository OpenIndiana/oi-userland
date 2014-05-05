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

COMPONENT_NAME= icu

COMPONENT_VERSION= 4.6
COMPONENT_SUMMARY= International Components for Unicode
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-$(COMPONENT_VERSION)-svn.tar.gz
COMPONENT_PROJECT_URL = http://icu-project.org
COMPONENT_ARCHIVE_URL = http://source.icu-project.org/repos/icu/icu/tags/release-4-6-1

download::
	if [ ! -f $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) ]; then \
           svn export --force $(COMPONENT_ARCHIVE_URL) $(COMPONENT_SRC) ; \
	   tar czf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE) $(COMPONENT_SRC)  ; \
	fi

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# prevent userland-fetch from overwriting icu-X.X-svn.tar.gz file
FETCH = /usr/bin/true

COMPONENT_POST_UNPACK_ACTION += ( chmod +x $(@D)/source/configure  $(@D)/source/runConfigureICU )

# Missing files in build dir for configure without this.
#COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D) && cd $(@D) && autoconf ) 

CONFIGURE_PREFIX = /usr/g++
LDFLAGS.32  +=  -L/usr/g++/lib -R/usr/g++/lib
LDFLAGS.64  +=  -L/usr/g++/lib/$(MACH64) -R/usr/g++/lib/$(MACH64)
LDFLAGS += $(LDFLAGS.$(BITS))

CONFIGURE_SCRIPT = $(SOURCE_DIR)/source/runConfigureICU
CONFIGURE_OPTIONS = Solaris/GCC
CONFIGURE_OPTIONS+= --with-data-packaging=library
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --enable-static
CONFIGURE_OPTIONS+= --disable-samples
CONFIGURE_OPTIONS+= --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS+= --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --bindir=$(CONFIGURE_BINDIR.$(BITS))

CONFIGURE_OPTIONS.32+= --disable-64bit-libs

COMPONENT_POST_CONFIGURE_ACTION =        (echo 'CPPFLAGS += -DICU_DATA_DIR=\"$(CONFIGURE_PREFIX)/share/icu/$(COMPONENT_VERSION)\"' >> $(@D)/icudefs.mk ) 

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
