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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		blueprint
COMPONENT_VERSION=	0.9.20
COMPONENT_PROJECT_URL=	https://java.net/projects/solaris-desktop/pages/Home
COMPONENT_SUMMARY=	Engine for GTK2 Blue Print Theme
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:b4e6b34011a588245e96e89777aa4a22d5d7b39241eb880023a3f499c8de8c0b
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/oi/jds/downloads/sources/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		gnome/theme/blueprint
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Theming
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# Missing files in build dir for gmake install without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

$(BUILD_DIR_32)/.installed_pixmaps:	$(BUILD_32)
	$(RM) -fr $(PROTO_DIR)/usr/share/pixmaps
	$(MKDIR) -p $(PROTO_DIR)/usr/share/pixmaps
	for i in `find $(SOURCE_DIR)/icons/48x48 -name "*.png"`; do \
		echo "Installing $$i to $(PROTO_DIR)/usr/share/pixmaps with blueprint- prefix "; \
		i_base=`basename $$i`; \
		cp $$i $(PROTO_DIR)/usr/share/pixmaps/blueprint-$${i_base}; \
	done
	$(TOUCH) $(@)


$(INSTALL_32):	$(BUILD_DIR_32)/.installed_pixmaps

COMPONENT_POST_INSTALL_ACTION=$(COMPONENT_POST_INSTALL_ACTION_$(BITS))

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)
