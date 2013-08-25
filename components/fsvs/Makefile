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

COMPONENT_NAME= fsvs
COMPONENT_VERSION= 1.2.5
COMPONENT_SUMMARY= FSVS backup/restore/versioning/deployment tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:0c3618963dddf6b2e58c814aa91d141e758aeedd7071320a45b8ffaedb3adf78
COMPONENT_ARCHIVE_URL= \
  http://download.fsvs-software.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://fsvs.tigris.org/

PSHAREMAN1=     $(PROTO_DIR)/usr/share/man/man1
PSHAREMAN5=     $(PROTO_DIR)/usr/share/man/man5

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS += -I/usr/include/pcre/ 
CFLAGS += -I/usr/include/svn/ 
CFLAGS += -I/usr/apr-util/include/
CPPFLAGS += -I/usr/include/pcre/
LDFLAGS += -R/usr/lib/svn -R/usr/apr-util/lib -R/usr/apr/lib

CONFIGURE_OPTIONS += --with-aprinc=/usr/apr/include
CONFIGURE_OPTIONS += --with-aprlib=/usr/apr/lib
CONFIGURE_OPTIONS += --with-aprutillib=/usr/apr-util/lib
CONFIGURE_OPTIONS += --with-svnlib=/usr/lib/svn
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"

COMPONENT_PREP_ACTION =        (cd $(@D) && autoconf)
COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D))

COMPONENT_POST_INSTALL_ACTION = ( mkdir -p $(PROTO_DIR)/usr/share/man/man1; \
	mkdir -p $(PROTO_DIR)/usr/share/man/man5; \
	cp $(SOURCE_DIR)/doc/*.1 $(PROTO_DIR)/usr/share/man/man1; \
	cp $(SOURCE_DIR)/doc/*.5 $(PROTO_DIR)/usr/share/man/man5)

install: $(INSTALL_32) 

build: $(BUILD_32)

install: $(INSTALL_32)
