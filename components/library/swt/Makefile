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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		swt
COMPONENT_VERSION=	3.8.2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=      Standard Widget Toolkit
COMPONENT_PROJECT_URL=	http://www.eclipse.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-gtk-solaris-x86
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH=	sha256:c44859428b3e82fd31353acdce3a95ed52a114b5c9b9babea09c24ccde7806ed
COMPONENT_ARCHIVE_URL=	http://archive.eclipse.org/eclipse/downloads/drops/R-3.8.2-201301310800/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

UNPACK_ARGS+=-r $(COMPONENT_SRC)
COMPONENT_POST_UNPACK_ACTION = ( cd $(SOURCE_DIR) ; /usr/bin/unzip -o src.zip)

COMPONENT_COMMON_ENV = JAVA_HOME=$(JAVA_HOME)
COMPONENT_COMMON_ENV += CC=$(CC)
COMPONENT_COMMON_ENV += CXX=$(CXX)

COMPONENT_BUILD_ENV = $(COMPONENT_COMMON_ENV)
COMPONENT_BUILD_ARGS += -f make_solaris_x86.mak
COMPONENT_BUILD_TARGETS = make_swt make_atk make_awt  make_cairo make_gnome

COMPONENT_INSTALL_ENV = $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ARGS += -f make_solaris_x86.mak

build:          $(BUILD_32)

install:	$(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libgnome
REQUIRED_PACKAGES += library/desktop/libgnomeui
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-vfs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/glu
REQUIRED_PACKAGES += x11/library/libxtst
