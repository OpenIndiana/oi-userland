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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= cairo-java
COMPONENT_VERSION= 1.0.8
COMPONENT_SUMMARY= Java to Cairo core bindings
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:9f9d2e80b4ec14cac48fb9e259adacc171f9c9e8c9252197a14ba022453b242f
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.0/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= library/java/cairo-java
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CPPFLAGS += -I$(JAVA_HOME)/include
CPPFLAGS += -I$(JAVA_HOME)/include/solaris

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-docbasedir=/usr/share/lib/java/javadoc/java-gnome
CONFIGURE_OPTIONS += --with-jardir=/usr/share/lib/java
CONFIGURE_OPTIONS += --with-srcjar
CONFIGURE_OPTIONS += --with-srcjardir=/usr/share/lib/java/src/java-gnome
CONFIGURE_OPTIONS += --without-gcj-compile               

CONFIGURE_OPTIONS += JAVA_HOME=$(JAVA_HOME)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
