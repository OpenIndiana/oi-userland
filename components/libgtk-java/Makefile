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

COMPONENT_NAME= libgtk-java
COMPONENT_VERSION= 2.10.2
COMPONENT_SUMMARY= Java to GTK core bindings
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:2aba562ecd9a1def58e0021152befaaebe9df6bf5336f2fb9e940a575a27c7b2
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.10/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= library/java/libgtk-java
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CPPFLAGS += -I$(JAVA_HOME)/include
CPPFLAGS += -I$(JAVA_HOME)/include/solaris

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --with-docbasedir=/usr/share/lib/java/javadoc/java-gnome
CONFIGURE_OPTIONS += --with-macrobasedir=/usr/share/lib/java/javadoc/java-gnome
CONFIGURE_OPTIONS += --with-jardir=/usr/share/lib/java
CONFIGURE_OPTIONS += --with-srcjar
CONFIGURE_OPTIONS += --with-srcjardir=/usr/share/lib/java/src/java-gnome
CONFIGURE_OPTIONS += --without-gcj-compile

CONFIGURE_OPTIONS += JAVA_HOME=$(JAVA_HOME)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
