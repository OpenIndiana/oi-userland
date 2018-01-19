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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xdg-user-dirs
COMPONENT_VERSION=	0.15
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/
COMPONENT_SUMMARY=	Tool to help manage user directories
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:20b4a751f41d0554bce3e0ce5e8d934be98cc62d48f0b90a894c3e1916552786
COMPONENT_ARCHIVE_URL=	http://user-dirs.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI=		library/xdg/xdg-user-dirs

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =       ( cd $(@D)  && \
					autoreconf -f -i )

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

LDFLAGS += -lglib-2.0

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)
	 $(GSED) -i -e 's:TEMPLATES=Templates:TEMPLATES=Documents/Templates:' \
                                                -e 's:MUSIC=Music:MUSIC=Documents/Music:' \
                                                -e 's:PICTURES=Pictures:PICTURES=Documents/Pictures:' \
                                                -e 's:VIDEOS=Videos:VIDEOS=Documents/Videos:' $(PROTO_DIR)/etc/xdg/user-dirs.defaults
	/usr/bin/grep '^\#' $(PROTO_DIR)/etc/xdg/user-dirs.defaults >  $(PROTO_DIR)/etc/xdg/user-dirs.defaults.tmp
	/usr/bin/grep -v "^#"  $(PROTO_DIR)/etc/xdg/user-dirs.defaults | $(ENV) LC_ALL=C /usr/bin/sort -r -t = -k 2 >>  $(PROTO_DIR)/etc/xdg/user-dirs.defaults.tmp
	$(MV)  $(PROTO_DIR)/etc/xdg/user-dirs.defaults.tmp  $(PROTO_DIR)/etc/xdg/user-dirs.defaults
	$(GSED) -i -e "s/^filename_encoding=UTF-8/filename_encoding=locale/"  $(PROTO_DIR)/etc/xdg/user-dirs.conf

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
