#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libvte-java
COMPONENT_VERSION=	0.12.3
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Part of Java-Gnome - Java to Gnome Terminal bindings
COMPONENT_FMRI=		library/java/java-gnome/java-libvte
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:abe3c300572decaad35f926bdeb129054dc7312a9dbf7c1cba2dcb715a53eb39
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.12/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS +=	-I/usr/java/include -I/usr/java/include/solaris

CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--with-docbasedir=/usr/share/lib/java/javadoc/java-gnome
CONFIGURE_OPTIONS+=	--with-jardir=/usr/share/lib/java
CONFIGURE_OPTIONS+=	--with-srcjar
CONFIGURE_OPTIONS+=	--with-srcjardir=/usr/share/lib/java/src/java-gnome
CONFIGURE_OPTIONS+=	--without-gcj-compile

CONFIGURE_ENV +=	JAVA_HOME=$(JAVA_HOME)

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
